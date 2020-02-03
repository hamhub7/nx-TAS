#pragma once
#include <switch.h>
#include <memory>
#include <map>
#include "controller.hpp"
#include "Absyn.H"

class ScriptWorld: public EmptyVisitor
{
private:
    int framesToWait;
    std::map<std::string, TasController*> controllers;

public:
    ScriptWorld() : EmptyVisitor() {}
    void visitCAddController(TasScript::CAddController* p) {
        TasControllerTypeVisitor* tctVis = new TasControllerTypeVisitor();
        p->controllertype_->accept(tctVis);
        controllers[p->ident_] = tctVis->get();
    }
};

template<class T, class... Args> void runScript(Args&&... args)
{
    auto provider = std::make_shared<T>(std::forward<Args>(args)...);
    if(!provider->isGood()) return;

    ScriptWorld* world = new ScriptWorld();

    provider->populateQueue();
    std::shared_ptr<TasScript::Command> nextCommand = provider->nextCommand();
    provider->populateQueue();

    nextCommand->accept(world);
}
