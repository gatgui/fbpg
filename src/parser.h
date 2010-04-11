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

Location MakeLocation(YYLTYPE *);
Location MakeLocation(YYLTYPE &);
void yyerror(const char *fmt, ...);

#endif
