#pragma once
#include <switch.h>

class TasController
{
    private:

    u64 HdlsHandle = 0;
    HiddbgHdlsDeviceInfo device = {0};
    HiddbgHdlsState state = {0};
    static int controllerCount = 0;

    public:

    TasController();
    ~TasController();
};