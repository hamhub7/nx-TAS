#include "controller.hpp"

u64 HdlsHandle = 0;
HiddbgHdlsDeviceInfo device = {0};
HiddbgHdlsState state = {0};

void initController()
{
    // Device is a procon
    device.type = BIT(0);

    // Colors
    device.singleColorBody = RGBA8_MAXALPHA(255,0,0);
    device.singleColorButtons = RGBA8_MAXALPHA(0,0,255);

    // Charge is max
    state.batteryCharge = 4;

    // Set Buttons and Joysticks
    state.buttons = 0;
    state.joysticks[JOYSTICK_LEFT].dx = 0;
    state.joysticks[JOYSTICK_LEFT].dy = 0;
    state.joysticks[JOYSTICK_RIGHT].dx = 0;
    state.joysticks[JOYSTICK_RIGHT].dy = 0;

    // Attach Work Buffer
    Result rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalSimple(rc);

    // Attach the controller
    rc = hiddbgAttachHdlsVirtualDevice(&HdlsHandle, &device);
    if (R_FAILED(rc))
        fatalSimple(rc);
}