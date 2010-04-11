#ifndef __parser_h_
#define __parser_h_

#include "context.h"
#include "stack.h"
#include "object.h"
#include "instruction.h"
#include "builtins.h"
#include "callstack.h"
#include "exception.h"
#include <cstdarg>

struct ParserData {
  char *filename;
  void *scanner;
  CodeSegment *code;
};

extern Location MakeLocation(YYLTYPE *);
extern Location MakeLocation(YYLTYPE &);
extern void yyerror(YYLTYPE *loc, struct ParserData *pd, const char *fmt, ...);

#endif
