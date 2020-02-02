/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2

namespace TasScript
{
//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char* s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
void PrintAbsyn::visitProg(Prog*p) {} //abstract class

void PrintAbsyn::visitP(P* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  if(p->listline_) {_i_ = 0; p->listline_->accept(this);}
  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListLine(ListLine *listline)
{
  for (ListLine::const_iterator i = listline->begin() ; i != listline->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listline->end() - 1) render('\n');
  }
}void PrintAbsyn::visitLine(Line*p) {} //abstract class

void PrintAbsyn::visitLEmpty(LEmpty* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLCommand(LCommand* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  _i_ = 0; p->command_->accept(this);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCommand(Command*p) {} //abstract class

void PrintAbsyn::visitCAddController(CAddController* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("+ ");
  visitIdent(p->ident_);
  render(' ');
  _i_ = 0; p->controllertype_->accept(this);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCRemoveController(CRemoveController* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("- ");
  visitIdent(p->ident_);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCSetButton(CSetButton* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("] ");
  visitIdent(p->ident_);
  render(' ');
  _i_ = 0; p->button_->accept(this);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCUnsetButton(CUnsetButton* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("[ ");
  visitIdent(p->ident_);
  render(' ');
  _i_ = 0; p->button_->accept(this);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitControllerType(ControllerType*p) {} //abstract class

void PrintAbsyn::visitCTProController(CTProController* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("pro_controller ");
  _i_ = 0; p->color_1->accept(this);
  render(' ');
  _i_ = 0; p->color_2->accept(this);
  render(' ');
  _i_ = 0; p->color_3->accept(this);
  render(' ');
  _i_ = 0; p->color_4->accept(this);

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitColor(Color*p) {} //abstract class

void PrintAbsyn::visitCOLRgb(COLRgb* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("rgb(");
  visitInteger(p->integer_1);
  render(',');
  visitInteger(p->integer_2);
  render(',');
  visitInteger(p->integer_3);
  render(')');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitButton(Button*p) {} //abstract class

void PrintAbsyn::visitBButtonA(BButtonA* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('A');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBButtonB(BButtonB* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('B');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBButtonX(BButtonX* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('X');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBButtonY(BButtonY* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('Y');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBBumperL(BBumperL* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('L');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBBumperR(BBumperR* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render('R');

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBBumperSL(BBumperSL* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("SL");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBBumperSR(BBumperSR* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("SR");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBTriggerZL(BTriggerZL* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("ZL");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBTriggerZR(BTriggerZR* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("ZR");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBDpadUp(BDpadUp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("DU");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBDpadDown(BDpadDown* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("DD");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBDpadLeft(BDpadLeft* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("DL");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBDpadRight(BDpadRight* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("DR");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBStickLeft(BStickLeft* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("LS");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitBStickRight(BStickRight* p)
{
  int oldi = _i_;
  if (oldi > 0) render(TASSCRIPT__L_PAREN);

  render("RS");

  if (oldi > 0) render(TASSCRIPT__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
void ShowAbsyn::visitProg(Prog* p) {} //abstract class

void ShowAbsyn::visitP(P* p)
{
  bufAppend('(');
  bufAppend("P");
  bufAppend(' ');
  bufAppend('[');
  if (p->listline_)  p->listline_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListLine(ListLine *listline)
{
  for (ListLine::const_iterator i = listline->begin() ; i != listline->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listline->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitLine(Line* p) {} //abstract class

void ShowAbsyn::visitLEmpty(LEmpty* p)
{
  bufAppend("LEmpty");
}
void ShowAbsyn::visitLCommand(LCommand* p)
{
  bufAppend('(');
  bufAppend("LCommand");
  bufAppend(' ');
  bufAppend('[');
  if (p->command_)  p->command_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCommand(Command* p) {} //abstract class

void ShowAbsyn::visitCAddController(CAddController* p)
{
  bufAppend('(');
  bufAppend("CAddController");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->controllertype_)  p->controllertype_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCRemoveController(CRemoveController* p)
{
  bufAppend('(');
  bufAppend("CRemoveController");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitCSetButton(CSetButton* p)
{
  bufAppend('(');
  bufAppend("CSetButton");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->button_)  p->button_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCUnsetButton(CUnsetButton* p)
{
  bufAppend('(');
  bufAppend("CUnsetButton");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->button_)  p->button_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitControllerType(ControllerType* p) {} //abstract class

void ShowAbsyn::visitCTProController(CTProController* p)
{
  bufAppend('(');
  bufAppend("CTProController");
  bufAppend(' ');
  p->color_1->accept(this);
  bufAppend(' ');
  p->color_2->accept(this);
  bufAppend(' ');
  p->color_3->accept(this);
  bufAppend(' ');
  p->color_4->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitColor(Color* p) {} //abstract class

void ShowAbsyn::visitCOLRgb(COLRgb* p)
{
  bufAppend('(');
  bufAppend("COLRgb");
  bufAppend(' ');
  visitInteger(p->integer_1);
  bufAppend(' ');
  visitInteger(p->integer_2);
  bufAppend(' ');
  visitInteger(p->integer_3);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitButton(Button* p) {} //abstract class

void ShowAbsyn::visitBButtonA(BButtonA* p)
{
  bufAppend("BButtonA");
}
void ShowAbsyn::visitBButtonB(BButtonB* p)
{
  bufAppend("BButtonB");
}
void ShowAbsyn::visitBButtonX(BButtonX* p)
{
  bufAppend("BButtonX");
}
void ShowAbsyn::visitBButtonY(BButtonY* p)
{
  bufAppend("BButtonY");
}
void ShowAbsyn::visitBBumperL(BBumperL* p)
{
  bufAppend("BBumperL");
}
void ShowAbsyn::visitBBumperR(BBumperR* p)
{
  bufAppend("BBumperR");
}
void ShowAbsyn::visitBBumperSL(BBumperSL* p)
{
  bufAppend("BBumperSL");
}
void ShowAbsyn::visitBBumperSR(BBumperSR* p)
{
  bufAppend("BBumperSR");
}
void ShowAbsyn::visitBTriggerZL(BTriggerZL* p)
{
  bufAppend("BTriggerZL");
}
void ShowAbsyn::visitBTriggerZR(BTriggerZR* p)
{
  bufAppend("BTriggerZR");
}
void ShowAbsyn::visitBDpadUp(BDpadUp* p)
{
  bufAppend("BDpadUp");
}
void ShowAbsyn::visitBDpadDown(BDpadDown* p)
{
  bufAppend("BDpadDown");
}
void ShowAbsyn::visitBDpadLeft(BDpadLeft* p)
{
  bufAppend("BDpadLeft");
}
void ShowAbsyn::visitBDpadRight(BDpadRight* p)
{
  bufAppend("BDpadRight");
}
void ShowAbsyn::visitBStickLeft(BStickLeft* p)
{
  bufAppend("BStickLeft");
}
void ShowAbsyn::visitBStickRight(BStickRight* p)
{
  bufAppend("BStickRight");
}
void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

}
