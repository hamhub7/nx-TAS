#include <string>
#include <cstdlib>
#include "script_util.hpp"

#include "script_provider.hpp"
#include "scripting/Absyn.H"
#include "scripting/Parser.H"

std::shared_ptr<TasScript::Command> ScriptProvider::nextLine()
{
    return pullFromQueue();
}
bool ScriptProvider::hasNextLine()
{
    return !queueIsEmpty();
}
void ScriptProvider::populateQueue()
{}

bool LineStreamScriptProvider::hasNextLine()
{
    return !(stream.eof() && queueIsEmpty());
}
void LineStreamScriptProvider::populateQueue()
{
    if(shouldPopulate())
    {
        std::string line = "";
        while(queueSize() < 30 && !stream.eof())
        {
            std::getline(stream, line);
            TasScript::ListCommand lineCmds = TasScript::pListCommand(line.c_str());
            std::for_each(lineCmds.begin(), lineCmds.end(), makeSharedAndPush);
        }
        if(stream.eof())
        {
            afterEOF();
        }
    }
}
