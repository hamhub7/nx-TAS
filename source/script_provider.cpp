#include <string>
#include <cstdlib>
#include <algorithm>
#include "script_util.hpp"

#include "script_provider.hpp"
#include "Absyn.H"
#include "Parser.H"
#include "Printer.H"

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
        TasScript::ShowAbsyn shower;

        ProgramCmdsExtractor extractor;
        std::string line;
        while(queueSize() < 30 && !stream.eof())
        {
            std::getline(stream, line);
            const char* lineCStr = line.c_str();
            TasScript::Program* pProgram = TasScript::pProgram(lineCStr);
            pProgram->accept(&extractor);
            for_each(extractor.getCmds()->begin(), extractor.getCmds()->end(), [this, shower](TasScript::Command* cmd) {
                // log_to_sd_out("Parsed command %s\n", shower->show(cmd));
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
}
