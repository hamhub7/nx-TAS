#pragma once
#include <switch.h>
#include <memory>
#include <map>
#include "controller.hpp"
#include "Absyn.H"
#include "Skeleton.H"

class ScriptWorld : public TasScript::Skeleton
{
private:
    int framesToWait;
    Event& vsync;
    std::map<std::string, TasController*> controllers;

public:
    ScriptWorld(Event& mv) : vsync(mv) {
        framesToWait = 0;
    }
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
            Result rc = eventWait(&vsync, U64_MAX);
            if(R_FAILED(rc))
                fatalThrow(rc);
            framesToWait--;
        }
    }
};

template<class T, class... Args> void runScript(Event& vsync, Args&&... args)
{
    auto provider = std::make_shared<T>(std::forward<Args>(args)...);
    if(!provider->isGood()) return;

    ScriptWorld* world = new ScriptWorld(vsync);

    provider->populateQueue();
    std::shared_ptr<TasScript::Command> nextCommand = provider->nextCommand();
    provider->populateQueue();

    while(provider->hasNextCommand()) {
        nextCommand->accept(world);
        pushProvider(provider);
        world->waitOutFrames();
        nextCommand.reset();
        nextCommand = provider->nextCommand();
    }
    nextCommand->accept(world);
    world->waitOutFrames();
    nextCommand.reset();
    delete world;
}
