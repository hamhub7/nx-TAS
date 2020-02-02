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
class Color;
class Button;

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
  Color* color_;
  Button* button_;
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
Color* pColor(FILE *inp);
Color* pColor(const char *str);
Button* pButton(FILE *inp);
Button* pButton(const char *str);

}

#define TASSCRIPT__ERROR_ 258
#define TASSCRIPT__SYMB_0 259
#define TASSCRIPT__SYMB_1 260
#define TASSCRIPT__SYMB_2 261
#define TASSCRIPT__SYMB_3 262
#define TASSCRIPT__SYMB_4 263
#define TASSCRIPT__SYMB_5 264
#define TASSCRIPT__SYMB_6 265
#define TASSCRIPT__SYMB_7 266
#define TASSCRIPT__SYMB_8 267
#define TASSCRIPT__SYMB_9 268
#define TASSCRIPT__SYMB_10 269
#define TASSCRIPT__SYMB_11 270
#define TASSCRIPT__SYMB_12 271
#define TASSCRIPT__SYMB_13 272
#define TASSCRIPT__SYMB_14 273
#define TASSCRIPT__SYMB_15 274
#define TASSCRIPT__SYMB_16 275
#define TASSCRIPT__SYMB_17 276
#define TASSCRIPT__SYMB_18 277
#define TASSCRIPT__SYMB_19 278
#define TASSCRIPT__SYMB_20 279
#define TASSCRIPT__SYMB_21 280
#define TASSCRIPT__SYMB_22 281
#define TASSCRIPT__SYMB_23 282
#define TASSCRIPT__SYMB_24 283
#define TASSCRIPT__SYMB_25 284
#define TASSCRIPT__INTEGER_ 285
#define TASSCRIPT__IDENT_ 286

extern TasScript::YYSTYPE TasScriptyylval;

#endif
