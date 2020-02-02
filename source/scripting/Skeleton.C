/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"


namespace TasScript
{
void Skeleton::visitProg(Prog* t) {} //abstract class
void Skeleton::visitLine(Line* t) {} //abstract class
void Skeleton::visitCommand(Command* t) {} //abstract class
void Skeleton::visitControllerType(ControllerType* t) {} //abstract class

void Skeleton::visitP(P *p)
{
  /* Code For P Goes Here */

  p->listline_->accept(this);

}

void Skeleton::visitLEmpty(LEmpty *lempty)
{
  /* Code For LEmpty Goes Here */


}

void Skeleton::visitLCommand(LCommand *lcommand)
{
  /* Code For LCommand Goes Here */

  lcommand->command_->accept(this);

}

void Skeleton::visitCAddController(CAddController *caddcontroller)
{
  /* Code For CAddController Goes Here */

  visitIdent(caddcontroller->ident_);
  caddcontroller->controllertype_->accept(this);

}

void Skeleton::visitCRemoveController(CRemoveController *cremovecontroller)
{
  /* Code For CRemoveController Goes Here */

  visitIdent(cremovecontroller->ident_);

}

void Skeleton::visitCTProController(CTProController *ctprocontroller)
{
  /* Code For CTProController Goes Here */


}


void Skeleton::visitListLine(ListLine* listline)
{
  for (ListLine::iterator i = listline->begin() ; i != listline->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}


}
