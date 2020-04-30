#include "script_runner.hpp"

void runScript(Event& vsync, std::string fileName)
{
    chaiscript::ChaiScript chai;

    chai.eval_file(fileName);

    return;
}
