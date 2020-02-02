#ifndef TASSCRIPT_PRINTER_HEADER
#define TASSCRIPT_PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace TasScript
{
/* Certain applications may improve performance by changing the buffer size */
#define TASSCRIPT_BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define TASSCRIPT__L_PAREN '('
#define TASSCRIPT__R_PAREN ')'

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
void render(char* s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char* print(Visitable* v);

  void visitProg(Prog *p); /* abstract class */
  void visitP(P *p);
  void visitListLine(ListLine* p);
  void visitLine(Line *p); /* abstract class */
  void visitLEmpty(LEmpty *p);
  void visitLCommand(LCommand *p);
  void visitCommand(Command *p); /* abstract class */
  void visitCAddController(CAddController *p);
  void visitCRemoveController(CRemoveController *p);
  void visitCSetButton(CSetButton *p);
  void visitCUnsetButton(CUnsetButton *p);
  void visitCWait(CWait *p);
  void visitControllerType(ControllerType *p); /* abstract class */
  void visitCTProController(CTProController *p);
  void visitColor(Color *p); /* abstract class */
  void visitCOLRgb(COLRgb *p);
  void visitButton(Button *p); /* abstract class */
  void visitBButtonA(BButtonA *p);
  void visitBButtonB(BButtonB *p);
  void visitBButtonX(BButtonX *p);
  void visitBButtonY(BButtonY *p);
  void visitBBumperL(BBumperL *p);
  void visitBBumperR(BBumperR *p);
  void visitBBumperSL(BBumperSL *p);
  void visitBBumperSR(BBumperSR *p);
  void visitBTriggerZL(BTriggerZL *p);
  void visitBTriggerZR(BTriggerZR *p);
  void visitBDpadUp(BDpadUp *p);
  void visitBDpadDown(BDpadDown *p);
  void visitBDpadLeft(BDpadLeft *p);
  void visitBDpadRight(BDpadRight *p);
  void visitBStickLeft(BStickLeft *p);
  void visitBStickRight(BStickRight *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = TASSCRIPT_BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char* show(Visitable* v);

  void visitProg(Prog *p); /* abstract class */
  void visitP(P *p);
  void visitListLine(ListLine* p);
  void visitLine(Line *p); /* abstract class */
  void visitLEmpty(LEmpty *p);
  void visitLCommand(LCommand *p);
  void visitCommand(Command *p); /* abstract class */
  void visitCAddController(CAddController *p);
  void visitCRemoveController(CRemoveController *p);
  void visitCSetButton(CSetButton *p);
  void visitCUnsetButton(CUnsetButton *p);
  void visitCWait(CWait *p);
  void visitControllerType(ControllerType *p); /* abstract class */
  void visitCTProController(CTProController *p);
  void visitColor(Color *p); /* abstract class */
  void visitCOLRgb(COLRgb *p);
  void visitButton(Button *p); /* abstract class */
  void visitBButtonA(BButtonA *p);
  void visitBButtonB(BButtonB *p);
  void visitBButtonX(BButtonX *p);
  void visitBButtonY(BButtonY *p);
  void visitBBumperL(BBumperL *p);
  void visitBBumperR(BBumperR *p);
  void visitBBumperSL(BBumperSL *p);
  void visitBBumperSR(BBumperSR *p);
  void visitBTriggerZL(BTriggerZL *p);
  void visitBTriggerZR(BTriggerZR *p);
  void visitBDpadUp(BDpadUp *p);
  void visitBDpadDown(BDpadDown *p);
  void visitBDpadLeft(BDpadLeft *p);
  void visitBDpadRight(BDpadRight *p);
  void visitBStickLeft(BStickLeft *p);
  void visitBStickRight(BStickRight *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = TASSCRIPT_BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};


}

#endif

