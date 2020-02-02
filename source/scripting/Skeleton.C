/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"


namespace TasScript
{
void Skeleton::visitLine(Line* t) {} //abstract class
void Skeleton::visitCommand(Command* t) {} //abstract class
void Skeleton::visitControllerType(ControllerType* t) {} //abstract class
void Skeleton::visitColor(Color* t) {} //abstract class
void Skeleton::visitButton(Button* t) {} //abstract class

void Skeleton::visitL(L *l)
{
  /* Code For L Goes Here */

  l->listcommand_->accept(this);

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

void Skeleton::visitCSetButton(CSetButton *csetbutton)
{
  /* Code For CSetButton Goes Here */

  visitIdent(csetbutton->ident_);
  csetbutton->button_->accept(this);

}

void Skeleton::visitCUnsetButton(CUnsetButton *cunsetbutton)
{
  /* Code For CUnsetButton Goes Here */

  visitIdent(cunsetbutton->ident_);
  cunsetbutton->button_->accept(this);

}

void Skeleton::visitCWait(CWait *cwait)
{
  /* Code For CWait Goes Here */

  visitInteger(cwait->integer_);

}

void Skeleton::visitCTProController(CTProController *ctprocontroller)
{
  /* Code For CTProController Goes Here */

  ctprocontroller->color_1->accept(this);
  ctprocontroller->color_2->accept(this);
  ctprocontroller->color_3->accept(this);
  ctprocontroller->color_4->accept(this);

}

void Skeleton::visitCOLRgb(COLRgb *colrgb)
{
  /* Code For COLRgb Goes Here */

  visitInteger(colrgb->integer_1);
  visitInteger(colrgb->integer_2);
  visitInteger(colrgb->integer_3);

}

void Skeleton::visitBButtonA(BButtonA *bbuttona)
{
  /* Code For BButtonA Goes Here */


}

void Skeleton::visitBButtonB(BButtonB *bbuttonb)
{
  /* Code For BButtonB Goes Here */


}

void Skeleton::visitBButtonX(BButtonX *bbuttonx)
{
  /* Code For BButtonX Goes Here */


}

void Skeleton::visitBButtonY(BButtonY *bbuttony)
{
  /* Code For BButtonY Goes Here */


}

void Skeleton::visitBBumperL(BBumperL *bbumperl)
{
  /* Code For BBumperL Goes Here */


}

void Skeleton::visitBBumperR(BBumperR *bbumperr)
{
  /* Code For BBumperR Goes Here */


}

void Skeleton::visitBBumperSL(BBumperSL *bbumpersl)
{
  /* Code For BBumperSL Goes Here */


}

void Skeleton::visitBBumperSR(BBumperSR *bbumpersr)
{
  /* Code For BBumperSR Goes Here */


}

void Skeleton::visitBTriggerZL(BTriggerZL *btriggerzl)
{
  /* Code For BTriggerZL Goes Here */


}

void Skeleton::visitBTriggerZR(BTriggerZR *btriggerzr)
{
  /* Code For BTriggerZR Goes Here */


}

void Skeleton::visitBDpadUp(BDpadUp *bdpadup)
{
  /* Code For BDpadUp Goes Here */


}

void Skeleton::visitBDpadDown(BDpadDown *bdpaddown)
{
  /* Code For BDpadDown Goes Here */


}

void Skeleton::visitBDpadLeft(BDpadLeft *bdpadleft)
{
  /* Code For BDpadLeft Goes Here */


}

void Skeleton::visitBDpadRight(BDpadRight *bdpadright)
{
  /* Code For BDpadRight Goes Here */


}

void Skeleton::visitBStickLeft(BStickLeft *bstickleft)
{
  /* Code For BStickLeft Goes Here */


}

void Skeleton::visitBStickRight(BStickRight *bstickright)
{
  /* Code For BStickRight Goes Here */


}


void Skeleton::visitListCommand(ListCommand* listcommand)
{
  for (ListCommand::iterator i = listcommand->begin() ; i != listcommand->end() ; ++i)
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
