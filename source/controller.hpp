#pragma once
#include <switch.h>
#include <cstring>
#include <string>
#include "script_provider.hpp"
#include "script_init.hpp"

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

    template<class T, class... Args> void runScript(Args&&... args)
    {
        auto provider = std::make_shared<T>(std::forward<Args>(args)...);

        provider->populateQueue();
        struct controlMsg nextLine = provider->nextLine();
        provider->populateQueue();

        int currentFrame = 0;

        while(provider->hasNextLine() || nextLine.frame <= currentFrame)
        {
            if(nextLine.frame == currentFrame)
            {
                runMsg(nextLine);
                if(provider->hasNextLine()) nextLine = provider->nextLine();
            }
            else
            {
                runMsg(emptyMsg);
            }

            pushProvider(provider);

            Result rc = eventWait(&vsync_event, U64_MAX);
            if(R_FAILED(rc))
                fatalSimple(rc);

            rc = hiddbgSetHdlsState(HdlsHandle, &state);
            if(R_FAILED(rc))
                fatalSimple(rc);

            currentFrame++;

        }
    }
    void runMsg(struct controlMsg msg)
    {
        state.buttons = msg.keys;
        state.joysticks[JOYSTICK_LEFT].dx = msg.joy_l_x;
        state.joysticks[JOYSTICK_LEFT].dy = msg.joy_r_x;
        state.joysticks[JOYSTICK_RIGHT].dx = msg.joy_l_y;
        state.joysticks[JOYSTICK_RIGHT].dy = msg.joy_r_y;
    }
};
