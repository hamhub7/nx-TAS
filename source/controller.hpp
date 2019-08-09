#pragma once
#include <switch.h>
#include <cstring>
#include <string>

extern int frameCount;
extern Event vsync_event;

class TasController
{
    private:

    u64 HdlsHandle = 0;
    HiddbgHdlsDeviceInfo device = {0};
    HiddbgHdlsState state = {0};
    static char controllerCount;

    public:

    TasController();
    ~TasController();
    void pressA();
    void runScript(std::string file);
};