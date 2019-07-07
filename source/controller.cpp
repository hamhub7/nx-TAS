#include "controller.hpp"

TasController::TasController()
{
    // Device is a procon
    device.type = BIT(0);

    // Colors
    device.singleColorBody = RGBA8_MAXALPHA(61,82,242);
    device.singleColorButtons = RGBA8_MAXALPHA(80,217,203);

    // Charge is max (not working?)
    state.batteryCharge = 0;

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
}

TasController::~TasController()
{
    // Detatch Controller
    Result rc = hiddbgDetachHdlsVirtualDevice(HdlsHandle);
    if (R_FAILED(rc))
        fatalSimple(rc);
}