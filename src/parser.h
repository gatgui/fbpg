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

/*
// IN PARSER
// from lexer
extern bool gEchoTokens;
extern int yylex();
extern FILE *yyin;

// parser globals
CodeSegment *gTopCode = 0;
char *gFilename = 0;

// IN LEXER
// from parser
extern char *gFilename;
extern void yyerror(char *fmt, ...);
extern Location MakeLocation(YYLTYPE &);

// lexer globals
int yycolumn = 1;
bool gEchoTokens = false;
*/

struct ParserData {
  char *filename;
  int yycolumn;
  bool echoTokens;
  yyscan_t scanner; // void*
  CodeSegment *code;
};

Location MakeLocation(YYLTYPE &);
void echoToken(const char *s = 0);
void yyerror(char *fmt, ...);

#endif
