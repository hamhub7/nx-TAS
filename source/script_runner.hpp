#pragma once
#include <switch.h>
#include <memory>
#include <map>
#include "controller.hpp"
#include "script_populator.hpp"
#include "Absyn.H"
#include "Printer.H"
#include "Skeleton.H"

class ScriptWorld : public TasScript::Skeleton
{
private:
    int framesToWait;
    Event& vsync;
    std::map<std::string, std::shared_ptr<TasController>> controllers;

public:
    ScriptWorld(Event& mv) : vsync(mv) {
        framesToWait = 0;
    }
    ~ScriptWorld() {
        for_each(controllers.begin(), controllers.end(), [](std::pair<std::string, std::shared_ptr<TasController>> pair) {
            pair.second.reset();
        });
    }
    void visitCAddController(TasScript::CAddController* p) {
        TasControllerTypeVisitor tctVis;
        p->controllertype_->accept(&tctVis);
        controllers[p->ident_] = tctVis.get();
    }
    void visitCRemoveController(TasScript::CRemoveController* p) {
        controllers[p->ident_].reset();
        controllers.erase(p->ident_);
    }
    void visitCSetButton(TasScript::CSetButton* p) {
        std::map<std::string, std::shared_ptr<TasController>>::iterator ctl = controllers.find(p->ident_);
        if(ctl != controllers.end()) {
            std::shared_ptr<TasController> ctlp = ctl->second;
            TasControllerKeysVisitor tckVis;
            p->listbutton_->accept(&tckVis);
            ctlp->setKeys(tckVis.get());
        }
    }
    void visitCUnsetButton(TasScript::CUnsetButton* p) {
        std::map<std::string, std::shared_ptr<TasController>>::iterator ctl = controllers.find(p->ident_);
        if(ctl != controllers.end()) {
            std::shared_ptr<TasController> ctlp = ctl->second;
            TasControllerKeysVisitor tckVis;
            p->listbutton_->accept(&tckVis);
            ctlp->unsetKeys(tckVis.get());
        }
    }
    void visitCWait(TasScript::CWait* p) {
        framesToWait = p->integer_;
    }
    void waitOutFrames() {
        if(framesToWait > 0) {
            for_each(controllers.begin(), controllers.end(), [](std::pair<std::string, std::shared_ptr<TasController>> pair) {
                pair.second->setInput();
            });
            while(framesToWait > 0) {
                Result rc = eventWait(&vsync, U64_MAX);
                if(R_FAILED(rc))
                    fatalThrow(rc);
                framesToWait--;
            }
        }
    }
};

template<class T, class... Args> void runScript(Event& vsync, Args&&... args)
{
    auto provider = std::make_shared<T>(std::forward<Args>(args)...);
    if(!provider->isGood()) return;

    ScriptWorld world(vsync);

    TasScript::ShowAbsyn shower;

    provider->populateQueue();
    std::shared_ptr<TasScript::Command> nextCommand = provider->nextCommand();
    provider->populateQueue();

    while(provider->hasNextCommand()) {
        log_to_sd_out("Queue size: %d\n", provider->queueSize());
        if(nextCommand) {
            log_to_sd_out("Running command %s\n", shower.show(nextCommand.get()));
        } else {
            log_to_sd_out("Uh oh! Couldn't get command. Should crash.\n");
        }
        nextCommand->accept(&world);
        pushProvider(provider);
        world.waitOutFrames();
        nextCommand.reset();
        nextCommand = provider->nextCommand();
    }
    nextCommand->accept(&world);
    world.waitOutFrames();
    nextCommand.reset();
    provider.reset();

    return;
}
