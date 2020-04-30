#include "script_runner.hpp"
#include "controller.hpp"

std::function<void ()> wait_for_vsync(Event& vsync)
{
    return [&]()
    {
        eventWait(&vsync, UINT64_MAX);
    };
}

TasController make_controller()
{
    TasController newCtrl(HidDeviceType_FullKey3,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
        0x00, 0x00, 0x00
    );

    return newCtrl;
}

void runScript(Event& vsync, std::string fileName)
{
    chaiscript::ChaiScript chai;

    chai.add(chaiscript::fun(wait_for_vsync(vsync)), "wait_for_vsync");
    chai.add(chaiscript::fun(&make_controller), "make_controller");

    chai.eval_file(fileName);

    return;
}
