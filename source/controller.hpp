#pragma once
#include <switch.h>
#include <algorithm>
#include <cstring>
#include <string>
#include "script_provider.hpp"
#include "script_util.hpp"
#include "Skeleton.H"

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

    void runMsg(std::shared_ptr<struct controlMsg> msg);
    void setKeys(u64 keys);
    void unsetKeys(u64 keys);
    void emptyMsg();
};

class TasControllerColorVisitor : public TasScript::Skeleton
{
private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

public:
    TasControllerColorVisitor() : red(0), green(0), blue(0) {}
    void visitCOLRgb(TasScript::COLRgb *color)
    {
        red = color->integer_1;
        green = color->integer_2;
        blue = color->integer_3;
    }
    uint8_t getRed()
    {
        return red;
    }
    uint8_t getGreen()
    {
        return green;
    }
    uint8_t getBlue()
    {
        return blue;
    }
};


class TasControllerTypeVisitor : public TasScript::Skeleton
{
private:
    std::shared_ptr<TasController> controller;

public:
    TasControllerTypeVisitor() : controller(NULL) {}
    void visitCTProController(TasScript::CTProController *p)
    {
        TasControllerColorVisitor visitBody;
        TasControllerColorVisitor visitButtons;
        TasControllerColorVisitor visitLeftGrip;
        TasControllerColorVisitor visitRightGrip;
        p->color_1->accept(&visitBody);
        p->color_2->accept(&visitButtons);
        p->color_3->accept(&visitLeftGrip);
        p->color_4->accept(&visitRightGrip);
        controller = std::make_shared<TasController>(
                HidDeviceType_FullKey3,
                visitBody.getRed(), visitBody.getGreen(), visitBody.getBlue(),
                visitButtons.getRed(), visitButtons.getGreen(), visitButtons.getBlue(),
                visitLeftGrip.getRed(), visitLeftGrip.getGreen(), visitLeftGrip.getBlue(),
                visitRightGrip.getRed(), visitRightGrip.getGreen(), visitRightGrip.getBlue()
        );
    }
    std::shared_ptr<TasController> get()
    {
        return controller;
    }
};

class TasControllerKeysVisitor : public TasScript::Skeleton
{
private:
    u64 keys;

public:
    TasControllerKeysVisitor() : keys(0) {}
    void visitListButton(TasScript::ListButton* p)
    {
        for_each(p->begin(), p->end(), [this](TasScript::Button* p) {
            p->accept(this);
        });
    }
    void visitBButtonA(TasScript::BButtonA* p)
    {
        keys |= HidControllerKeys::KEY_A;
    }
    void visitBButtonB(TasScript::BButtonB* p)
    {
        keys |= HidControllerKeys::KEY_B;
    }
    void visitBButtonX(TasScript::BButtonX* p)
    {
        keys |= HidControllerKeys::KEY_X;
    }
    void visitBButtonY(TasScript::BButtonY* p)
    {
        keys |= HidControllerKeys::KEY_Y;
    }
    void visitBStickLeft(TasScript::BStickLeft* p)
    {
        keys |= HidControllerKeys::KEY_LSTICK;
    }
    void visitBStickRight(TasScript::BStickRight* p)
    {
        keys |= HidControllerKeys::KEY_RSTICK;
    }
    void visitBBumperL(TasScript::BBumperL* p)
    {
        keys |= HidControllerKeys::KEY_L;
    }
    void visitBBumperR(TasScript::BBumperR* p)
    {
        keys |= HidControllerKeys::KEY_R;
    }
    void visitBTriggerZL(TasScript::BTriggerZL* p) {
        keys |= HidControllerKeys::KEY_ZL;
    }
    void visitBTriggerZR(TasScript::BTriggerZR* p) {
        keys |= HidControllerKeys::KEY_ZR;
    }
    void visitBPlus(TasScript::BPlus* p) {
        keys |= HidControllerKeys::KEY_PLUS;
    }
    void visitBMinus(TasScript::BMinus* p) {
        keys |= HidControllerKeys::KEY_MINUS;
    }
    void visitBDpadLeft(TasScript::BDpadLeft* p) {
        keys |= HidControllerKeys::KEY_DLEFT;
    }
    void visitBDpadUp(TasScript::BDpadUp* p) {
        keys |= HidControllerKeys::KEY_DUP;
    }
    void visitBDpadRight(TasScript::BDpadRight* p) {
        keys |= HidControllerKeys::KEY_DRIGHT;
    }
    void visitBDpadDown(TasScript::BDpadDown* p) {
        keys |= HidControllerKeys::KEY_DDOWN;
    }
    u64 get()
    {
        return keys;
    }
};
