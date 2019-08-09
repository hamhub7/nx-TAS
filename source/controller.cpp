#include "controller.hpp"
#include "script_init.hpp"

TasController::TasController()
{
    // Device is a procon
    device.type = BIT(0);

    // Colors
    device.singleColorBody = RGBA8_MAXALPHA(61,82,242);
    device.singleColorButtons = RGBA8_MAXALPHA(80,217,203);

    // Charge is max (not working?)
    state.batteryCharge = 4;

    // Set Buttons and Joysticks
    state.buttons = 0;
    state.joysticks[JOYSTICK_LEFT].dx = 0;
    state.joysticks[JOYSTICK_LEFT].dy = 0;
    state.joysticks[JOYSTICK_RIGHT].dx = 0;
    state.joysticks[JOYSTICK_RIGHT].dy = 0;

    // Attach the controller
    Result rc = hiddbgAttachHdlsVirtualDevice(&HdlsHandle, &device);
    if (R_FAILED(rc))
        fatalSimple(rc);

    // Update the state
    rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalSimple(rc);
}

TasController::~TasController()
{
    // Detatch Controller
    Result rc = hiddbgDetachHdlsVirtualDevice(HdlsHandle);
    if (R_FAILED(rc))
        fatalSimple(rc);
}

//This also resets the state of the controller after pressing so only to be used when pairing and not running a script. checker to come soon probably once scripts get implemented.
void TasController::pressA()
{
    frameCount = 0;

    state.buttons = KEY_A;

    Result rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalSimple(rc);

    bool loopFlag = true;

    while(loopFlag)
    {
        if(frameCount >= 2)
        {
            state.buttons = 0;

            Result rc = hiddbgSetHdlsState(HdlsHandle, &state);
            if(R_FAILED(rc))
                fatalSimple(rc);

            loopFlag = false;
        }

        svcSleepThread(6250000);
    }
}

void TasController::runScript(std::string filename)
{
    std::vector<struct controlMsg> script = getScriptLines(filename);
    int frames = 0;

    while(!script.empty())
    {
        if(script.front().frame == frames)
        {
            state.buttons = script.front().keys;
            state.joysticks[JOYSTICK_LEFT].dx = script.front().joy_l_x;
            state.joysticks[JOYSTICK_LEFT].dy = script.front().joy_r_x;
            state.joysticks[JOYSTICK_RIGHT].dx = script.front().joy_l_y;
            state.joysticks[JOYSTICK_RIGHT].dy = script.front().joy_r_y;

            script.erase(script.begin());
        }
        else
        {
            state.buttons = 0;
            state.joysticks[JOYSTICK_LEFT].dx = 0;
            state.joysticks[JOYSTICK_LEFT].dy = 0;
            state.joysticks[JOYSTICK_RIGHT].dx = 0;
            state.joysticks[JOYSTICK_RIGHT].dy = 0;
        }

        Result rc = eventWait(&vsync_event, U64_MAX);
        if(R_FAILED(rc))
            fatalSimple(rc);

        rc = hiddbgSetHdlsState(HdlsHandle, &state);
        if(R_FAILED(rc))
            fatalSimple(rc); 

        frames++;
        
    }
}