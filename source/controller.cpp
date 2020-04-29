#include "controller.hpp"
#include "script_util.hpp"

TasController::TasController(uint8_t deviceType, uint8_t bodyR, uint8_t bodyG, uint8_t bodyB, uint8_t buttonR, uint8_t buttonG, uint8_t buttonB, uint8_t leftgripR, uint8_t leftgripG, uint8_t leftgripB, uint8_t rightgripR, uint8_t rightgripG, uint8_t rightgripB)
{
    device.deviceType = deviceType;

    // Set the interface type
    device.npadInterfaceType = NpadInterfaceType_Bluetooth;

    // Colors
    device.singleColorBody = RGBA8_MAXALPHA(bodyR, bodyG, bodyB);
    device.singleColorButtons = RGBA8_MAXALPHA(buttonR, buttonG, buttonB);
    device.colorLeftGrip = RGBA8_MAXALPHA(leftgripR, leftgripG, leftgripB);
    device.colorRightGrip = RGBA8_MAXALPHA(rightgripR, rightgripG, rightgripB);

    // Charge is max
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
        fatalThrow(rc);

    // Update the state
    rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalThrow(rc);
}

TasController::~TasController()
{
    // Detatch Controller
    Result rc = hiddbgDetachHdlsVirtualDevice(HdlsHandle);
    if (R_FAILED(rc))
        fatalThrow(rc);
}
void TasController::setInput()
{
    Result rc = hiddbgSetHdlsState(HdlsHandle, &state);
    if(R_FAILED(rc))
        fatalThrow(rc);
}

void TasController::setKeys(u64 keys)
{
    state.buttons |= keys;
}
void TasController::unsetKeys(u64 keys)
{
    state.buttons &= ~keys;
}
