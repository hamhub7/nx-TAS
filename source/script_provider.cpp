#include <string>
#include <cstdlib>
#include <algorithm>
#include "script_util.hpp"

#include "script_provider.hpp"
#include "Absyn.H"
#include "Parser.H"

std::shared_ptr<TasScript::Command> ScriptProvider::nextCommand()
{
    return pullFromQueue();
}
bool ScriptProvider::hasNextCommand()
{
    return !queueIsEmpty();
}
void ScriptProvider::populateQueue()
{}

bool LineStreamScriptProvider::hasNextCommand()
{
    return !(stream.eof() && queueIsEmpty());
}
void LineStreamScriptProvider::populateQueue()
{
    if(shouldPopulate())
    {
        std::string line;
        while(queueSize() < 30 && std::getline(stream, line))
        {
            const char* lineCStr = line.c_str();
            TasScript::Program* lineCmds = TasScript::pProgram(lineCStr);
            TasScript::P* asLeaf = static_cast<TasScript::P*>(lineCmds);
            TasScript::ListCommand* cList = asLeaf->listcommand_;
            for_each(cList->begin(), cList->end(), [this](TasScript::Command* cmd) {
                std::shared_ptr<TasScript::Command> cmdShared(cmd);
                pushToQueue(cmdShared);
            });
        }
        if(stream.eof())
        {
            afterEOF();
        }
    }
}
