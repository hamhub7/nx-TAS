#pragma once
#include <switch.h>
#include <memory>
#include <map>
#include "controller.hpp"
#include "Absyn.H"
#include "Skeleton.H"

extern Event vsync_event;

class ScriptWorld : public TasScript::Skeleton
{
private:
    int framesToWait;
    std::map<std::string, TasController*> controllers;

public:
    ScriptWorld() {}
    void visitCAddController(TasScript::CAddController* p) {
        TasControllerTypeVisitor* tctVis = new TasControllerTypeVisitor();
        p->controllertype_->accept(tctVis);
        controllers[p->ident_] = tctVis->get();
    }
    void visitCRemoveController(TasScript::CRemoveController* p) {
        delete controllers[p->ident_];
        controllers.erase(p->ident_);
    }
    void visitCSetButton(TasScript::CSetButton* p) {
        std::map<std::string, TasController*>::iterator ctl = controllers.find(p->ident_);
        if(ctl != controllers.end()) {
            TasController* ctlp = ctl->second;
            TasControllerKeysVisitor* tckVis = new TasControllerKeysVisitor();
            p->listbutton_->accept(tckVis);
            ctlp->setKeys(tckVis->get());
        }
    }
    void visitCUnsetButton(TasScript::CUnsetButton* p) {
        std::map<std::string, TasController*>::iterator ctl = controllers.find(p->ident_);
        if(ctl != controllers.end()) {
            TasController* ctlp = ctl->second;
            TasControllerKeysVisitor* tckVis = new TasControllerKeysVisitor();
            p->listbutton_->accept(tckVis);
            ctlp->unsetKeys(tckVis->get());
        }
    }
    void visitCWait(TasScript::CWait* p) {
        framesToWait = p->integer_;
    }
    void waitOutFrames() {
        while(framesToWait > 0) {
            Result rc = eventWait(&vsync_event, U64_MAX);
            if (R_FAILED(rc))
                fatalThrow(rc);
            framesToWait--;
        }
    }
};

template<class T, class... Args> void runScript(Args&&... args)
{
    auto provider = std::make_shared<T>(std::forward<Args>(args)...);
    if(!provider->isGood()) return;

    ScriptWorld* world = new ScriptWorld();

    provider->populateQueue();
    std::shared_ptr<TasScript::Command> nextCommand;

    while(provider->hasNextCommand()) {
        world->waitOutFrames();
        nextCommand = provider->nextCommand();
        nextCommand->accept(world);
    }
}
