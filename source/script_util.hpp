#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <switch.h>
#include "Absyn.H"

struct controlMsg
{
    // Joys between -32768 to 32767
    int frame;
    u64 keys;
    s32 joy_l_x;
    s32 joy_l_y;
    s32 joy_r_x;
    s32 joy_r_y;
};

std::vector<struct controlMsg> getScriptLines(std::string fileName);

struct controlMsg lineAsControlMsg(int frame, std::string keyStr, std::string lStickStr, std::string rStickStr);

class EmptyVisitor: public TasScript::Visitor
{
public:
    EmptyVisitor() {}
    ~EmptyVisitor() {}
    void visitLine(TasScript::Line *p) {}
    void visitCommand(TasScript::Command *p) {}
    void visitControllerType(TasScript::ControllerType *p) {}
    void visitColor(TasScript::Color *p) {}
    void visitButton(TasScript::Button *p) {}
    void visitL(TasScript::L *p) {}
    void visitCAddController(TasScript::CAddController *p) {}
    void visitCRemoveController(TasScript::CRemoveController *p) {}
    void visitCSetButton(TasScript::CSetButton *p) {}
    void visitCUnsetButton(TasScript::CUnsetButton *p) {}
    void visitCWait(TasScript::CWait *p) {}
    void visitCImport(TasScript::CImport *p) {}
    void visitCTProController(TasScript::CTProController *p) {}
    void visitCOLRgb(TasScript::COLRgb *p) {}
    void visitBButtonA(TasScript::BButtonA *p) {}
    void visitBButtonB(TasScript::BButtonB *p) {}
    void visitBButtonX(TasScript::BButtonX *p) {}
    void visitBButtonY(TasScript::BButtonY *p) {}
    void visitBBumperL(TasScript::BBumperL *p) {}
    void visitBBumperR(TasScript::BBumperR *p) {}
    void visitBBumperSL(TasScript::BBumperSL *p) {}
    void visitBBumperSR(TasScript::BBumperSR *p) {}
    void visitBTriggerZL(TasScript::BTriggerZL *p) {}
    void visitBTriggerZR(TasScript::BTriggerZR *p) {}
    void visitBDpadUp(TasScript::BDpadUp *p) {}
    void visitBDpadDown(TasScript::BDpadDown *p) {}
    void visitBDpadLeft(TasScript::BDpadLeft *p) {}
    void visitBDpadRight(TasScript::BDpadRight *p) {}
    void visitBStickLeft(TasScript::BStickLeft *p) {}
    void visitBStickRight(TasScript::BStickRight *p) {}
    void visitListCommand(TasScript::ListCommand *p) {}

    void visitInteger(TasScript::Integer x) {}
    void visitChar(TasScript::Char x) {}
    void visitDouble(TasScript::Double x) {}
    void visitString(TasScript::String x) {}
    void visitIdent(TasScript::Ident x) {}
};