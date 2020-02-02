#ifndef TASSCRIPT_PARSER_HEADER_FILE
#define TASSCRIPT_PARSER_HEADER_FILE

#include<vector>
#include<string>

namespace TasScript
{
class Prog;
class ListLine;
class Line;
class Command;
class ControllerType;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Prog* prog_;
  ListLine* listline_;
  Line* line_;
  Command* command_;
  ControllerType* controllertype_;
} YYSTYPE;

Prog* pProg(FILE *inp);
Prog* pProg(const char *str);
ListLine* pListLine(FILE *inp);
ListLine* pListLine(const char *str);
Line* pLine(FILE *inp);
Line* pLine(const char *str);
Command* pCommand(FILE *inp);
Command* pCommand(const char *str);
ControllerType* pControllerType(FILE *inp);
ControllerType* pControllerType(const char *str);

}

#define TASSCRIPT__ERROR_ 258
#define TASSCRIPT__SYMB_0 259
#define TASSCRIPT__SYMB_1 260
#define TASSCRIPT__SYMB_2 261
#define TASSCRIPT__SYMB_3 262
#define TASSCRIPT__SYMB_4 263
#define TASSCRIPT__IDENT_ 264

extern TasScript::YYSTYPE TasScriptyylval;

#endif
