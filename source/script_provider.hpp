#pragma once
#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <istream>
#include "script_init.hpp"

class ScriptProvider
{
private:
    mutable std::mutex mutex;
    std::queue<struct controlMsg> internalQueue;

protected:
    void pushToQueue(struct controlMsg msg)
    {
        std::lock_guard<std::mutex> guard(mutex);
        return internalQueue.push(msg);
    }

    struct controlMsg pullFromQueue()
    {
        std::lock_guard<std::mutex> guard(mutex);
        struct controlMsg msg = internalQueue.front();
        internalQueue.pop();
        return msg;
    }

public:
    bool queueIsEmpty()
    {
        std::lock_guard<std::mutex> guard(mutex);
        return internalQueue.empty();
    }

    struct controlMsg nextLine()
    {
        return pullFromQueue();
    }
    bool hasNextLine()
    {
        return queueIsEmpty();
    }

    virtual void populateQueue() {};

};

class LineStreamScriptProvider: public ScriptProvider
{
private:
    std::istream& stream;

public:
    LineStreamScriptProvider(std::istream& mStream)
    : stream(mStream)
    {}

    bool hasNextLine()
    {
        return !(stream.eof() && queueIsEmpty());
    }
    void populateQueue()
    {
        int frame;
        std::string keyStr, lStickStr, rStickStr;
        stream >> frame >> keyStr >> lStickStr >> rStickStr;
        struct controlMsg msg = lineAsControlMsg(frame, keyStr, lStickStr, rStickStr);
        pushToQueue(msg);
    }

};

class LineFileScriptProvider: public LineStreamScriptProvider
{
    std::ifstream stream;

public:
    LineFileScriptProvider(std::string fileName)
    : LineStreamScriptProvider(stream), stream(fileName)
    {}

};
