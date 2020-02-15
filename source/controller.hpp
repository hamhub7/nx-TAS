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

    void setInputNextFrame();

    template<class T, class... Args> void runScript(Args&&... args)
    {
        auto provider = std::make_shared<T>(std::forward<Args>(args)...);
        if(!provider->isGood()) return;

        provider->populateQueue();
        std::shared_ptr<struct controlMsg> nextLine = provider->nextLine();
        provider->populateQueue();

        int currentFrame = 0;
        bool pause = false;

        while(provider->hasNextLine() || nextLine->frame >= currentFrame)
        {
            if(hidKeyboardDown(KBD_PAUSE)) pause = !pause;
            if(hidKeyboardDown(KBD_SCROLLLOCK)) break;
            if(pause) continue;
            if(nextLine->frame == currentFrame)
            {
                runMsg(nextLine);
                if(provider->hasNextLine())
                {
                    nextLine.reset();
                    nextLine = provider->nextLine();
                }
            }
            else
            {
                emptyMsg();
            }

            pushProvider(provider);

            setInputNextFrame();

            currentFrame++;

        }
        emptyMsg();
        setInputNextFrame();

        nextLine.reset();

        hidScanInput();
    }

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
    TasController* controller;

public:
    TasControllerTypeVisitor() : controller(NULL) {}
    void visitCTProController(TasScript::CTProController *p)
    {
        TasControllerColorVisitor* visitBody = new TasControllerColorVisitor();
        TasControllerColorVisitor* visitButtons = new TasControllerColorVisitor();
        TasControllerColorVisitor* visitLeftGrip = new TasControllerColorVisitor();
        TasControllerColorVisitor* visitRightGrip = new TasControllerColorVisitor();
        p->color_1->accept(visitBody);
        p->color_2->accept(visitBody);
        p->color_3->accept(visitLeftGrip);
        p->color_4->accept(visitRightGrip);
        controller = new TasController(HidDeviceType_FullKey3, visitBody->getRed(), visitBody->getGreen(), visitBody->getBlue(), visitButtons->getRed(), visitButtons->getGreen(), visitButtons->getBlue(), visitLeftGrip->getRed(), visitLeftGrip->getGreen(), visitLeftGrip->getBlue(), visitRightGrip->getRed(), visitRightGrip->getGreen(), visitRightGrip->getBlue());
    }
    TasController* get()
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
    u64 get()
    {
        return keys;
    }
};
