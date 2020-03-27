#pragma once
#include <algorithm>
#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <fstream>
#include <istream>
#include "script_util.hpp"
#include "Absyn.H"
#include "Skeleton.H"
#include "Parser.H"

class ProgramCmdsExtractor: public TasScript::Skeleton
{
private:
    TasScript::ListCommand* cmds;

public:
    ProgramCmdsExtractor(): cmds(NULL) {}

    void visitP(TasScript::P* p)
    {
        cmds = p->listcommand_;
    }
    TasScript::ListCommand* getCmds()
    {
        return cmds;
    }
};

class ScriptProvider
{
private:
    mutable std::mutex queueLockMutex;
    std::queue<std::shared_ptr<TasScript::Command>> internalQueue;

protected:
    void pushToQueue(std::shared_ptr<TasScript::Command> msg)
    {
        std::lock_guard<std::mutex> guard(queueLockMutex);
        return internalQueue.push(msg);
    }

    std::shared_ptr<TasScript::Command> pullFromQueue()
    {
        std::lock_guard<std::mutex> guard(queueLockMutex);
        std::shared_ptr<TasScript::Command> msg = internalQueue.front();
        internalQueue.pop();
        return msg;
    }
    virtual bool shouldPopulate()
    {
        return queueSize() < 15;
    }

public:
    bool queueIsEmpty()
    {
        std::lock_guard<std::mutex> guard(queueLockMutex);
        return internalQueue.empty();
    }
    int queueSize()
    {
        std::lock_guard<std::mutex> guard(queueLockMutex);
        return internalQueue.size();
    }
    virtual bool isConcrete() { return false; };
    virtual bool isPopulatable() { return false; };
    virtual int recommendedQueueSize() { return 0; };

    std::shared_ptr<TasScript::Command> nextCommand()
    {
        return pullFromQueue();
    }
    bool isNextCommand()
    {
        return !queueIsEmpty() || isPopulatable();
    }
    virtual void populateQueue() {}

    virtual ~ScriptProvider() = default;

};

class LineStreamScriptProvider: public ScriptProvider
{
private:
    std::istream& stream;

protected:
    virtual void afterEOF()
    {}

public:
    LineStreamScriptProvider(std::istream& mStream)
    : stream(mStream)
    {}

    bool isConcrete()
    {
        return stream.good();
    }
    bool isPopulatable()
    {
        return !stream.eof();
    }

    void populateQueue()
    {
        std::string line;
        ProgramCmdsExtractor extractor;
        while(queueSize() < (2 * recommendedQueueSize()) && !stream.eof())
        {
            std::getline(stream, line);
            const char* lineCStr = line.c_str();
            TasScript::Program* pProgram = TasScript::pProgram(lineCStr);
            pProgram->accept(&extractor);
            std::for_each(extractor.getCmds()->begin(), extractor.getCmds()->end(), [this](TasScript::Command* cmd) {
                std::shared_ptr<TasScript::Command> cmdShared(cmd);
                pushToQueue(cmdShared);
            });
            delete pProgram;
        }
        if(stream.eof())
        {
            afterEOF();
        }
    }

};

class LineFileScriptProvider: public LineStreamScriptProvider
{
    std::ifstream stream;

protected:
    void afterEOF()
    {
        stream.close();
    }

public:
    LineFileScriptProvider(std::string fileName)
    : LineStreamScriptProvider(stream), stream(fileName)
    {}

    int recommendedQueueSize()
    {
        return 15;
    }

};
