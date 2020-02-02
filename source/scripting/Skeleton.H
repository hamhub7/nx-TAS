#ifndef TASSCRIPT_SKELETON_HEADER
#define TASSCRIPT_SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"

namespace TasScript
{
class Skeleton : public Visitor
{
public:
  void visitProg(Prog* p);
  void visitLine(Line* p);
  void visitCommand(Command* p);
  void visitControllerType(ControllerType* p);
  void visitColor(Color* p);
  void visitButton(Button* p);
  void visitP(P* p);
  void visitLEmpty(LEmpty* p);
  void visitLCommand(LCommand* p);
  void visitCAddController(CAddController* p);
  void visitCRemoveController(CRemoveController* p);
  void visitCSetButton(CSetButton* p);
  void visitCUnsetButton(CUnsetButton* p);
  void visitCTProController(CTProController* p);
  void visitCOLRgb(COLRgb* p);
  void visitBButtonA(BButtonA* p);
  void visitBButtonB(BButtonB* p);
  void visitBButtonX(BButtonX* p);
  void visitBButtonY(BButtonY* p);
  void visitBBumperL(BBumperL* p);
  void visitBBumperR(BBumperR* p);
  void visitBBumperSL(BBumperSL* p);
  void visitBBumperSR(BBumperSR* p);
  void visitBTriggerZL(BTriggerZL* p);
  void visitBTriggerZR(BTriggerZR* p);
  void visitBDpadUp(BDpadUp* p);
  void visitBDpadDown(BDpadDown* p);
  void visitBDpadLeft(BDpadLeft* p);
  void visitBDpadRight(BDpadRight* p);
  void visitBStickLeft(BStickLeft* p);
  void visitBStickRight(BStickRight* p);
  void visitListLine(ListLine* p);

  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};
}

#endif
