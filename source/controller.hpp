#pragma once
#include <switch.h>
#include <algorithm>
#include <cstring>
#include <string>

class TasController
{
    private:

    u64 HdlsHandle = 0;
    HiddbgHdlsDeviceInfo device = {0};
    HiddbgHdlsState state = {0};
    static char controllerCount;

    public:

    TasController(uint8_t deviceType, uint8_t bodyR, uint8_t bodyG, uint8_t bodyB, uint8_t buttonR, uint8_t buttonG, uint8_t buttonB, uint8_t leftgripR, uint8_t leftgripG, uint8_t leftgripB, uint8_t rightgripR, uint8_t rightgripG, uint8_t rightgripB);
    TasController();
    ~TasController();
    void pressA();
    void pressLR();

    void setInput();

    void setKeys(u64 keys);
    void unsetKeys(u64 keys);
};
