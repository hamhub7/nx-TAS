#include "script_runner.hpp"

void runScript(Event& vsync, std::string fileName)
{
    chaiscript::ChaiScript chai;

    return chai.eval_file<void>(fileName);
}
