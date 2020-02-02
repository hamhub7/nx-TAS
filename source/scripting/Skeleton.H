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
  void visitP(P* p);
  void visitLEmpty(LEmpty* p);
  void visitLCommand(LCommand* p);
  void visitCAddController(CAddController* p);
  void visitCRemoveController(CRemoveController* p);
  void visitCTProController(CTProController* p);
  void visitListLine(ListLine* p);

  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};
}

#endif
