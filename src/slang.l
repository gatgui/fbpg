%option noyywrap
%option nodefault
%option yylineno
  // %option header-file="src/calc.lexer.h"

%x MULTILINE_COMMENT

%{
#include "context.h"
#include "stack.h"
#include "object.h"
#include "instruction.h"
#include "builtins.h"
#include "callstack.h"
#include "slang.parser.h"

// from parser
extern char *gFilename;
extern void yyerror(char *fmt, ...);
extern Location MakeLocation(YYLTYPE &);

// lexer globals
int yycolumn = 1;
bool gEchoTokens = false;

static void echoToken(const char *s = 0) {
  if (gEchoTokens) {
    fprintf(stdout, "<Token: \"%s\">\n", (s != 0 ? s : yytext));
  }
}

#define YY_USER_ACTION \
  yylloc.first_line = yylloc.last_line = yylineno; \
  yylloc.first_column = yycolumn; \
  yylloc.last_column = yycolumn + yyleng - 1; \
  yylloc.filename = gFilename; \
  yycolumn += yyleng;

%}

DIGIT     ([0-9])
EXP       ([eE][-+]?[0-9]+)
ALPHA     ([a-zA-Z])
ALPHANUM  ([a-zA-Z0-9])
WORD      ([a-zA-Z0-9_])

%%

  /* Punctuation */
"(" |
")" |
"{" |
"}" |
"[" |
"]" |
";" |
"," |
"=" |
"+" |
"-" |
"*" |
"/" |
"%" |
"."                             { echoToken(); return yytext[0]; }

  /* Comparison */
"=="                            { echoToken(); return EQ; }
"!="                            { echoToken(); return NEQ; }
"<"                             { echoToken(); return LT; }
">"                             { echoToken(); return GT; }
"<="                            { echoToken(); return LTE; }
">="                            { echoToken(); return GTE; }

  /* Keywords */
"if"                            { echoToken(); return IF; }
"then"                          { echoToken(); return THEN; }
"else"                          { echoToken(); return ELSE; }
"while"                         { echoToken(); return WHILE; }
"do"                            { echoToken(); return DO; }
"function"                      { echoToken(); return FUNC; }
"end"                           { echoToken(); return END; }
"true"                          {
                                  echoToken();
                                  yylval.b = new Boolean(true);
                                  return TRUE;
                                }
"false"                         {
                                  echoToken();
                                  yylval.b = new Boolean(false);
                                  return FALSE;
                                }
"return"                        {
                                  echoToken();
                                  yylval.inst = new Return(MakeLocation(yylloc));
                                  return RETURN;
                                }
"break"                         {
                                  echoToken();
                                  yylval.inst = new Break(MakeLocation(yylloc));
                                  return BREAK;
                                }
"continue"                      {
                                  echoToken();
                                  yylval.inst = new Continue(MakeLocation(yylloc));
                                  return CONTINUE;
                                }
"or"                            { echoToken(); return OR; }
"and"                           { echoToken(); return AND; }
"not"                           { echoToken(); return NOT; }

  /* Literals */
{DIGIT}+                        {
                                  long v;
                                  echoToken();
                                  sscanf(yytext, "%ld", &v);
                                  yylval.i = new Integer(v);
                                  return INTEGER;
                                }
{DIGIT}+\.{DIGIT}+{EXP}?        {
                                  double v;
                                  echoToken();
                                  sscanf(yytext, "%lf", &v);
                                  yylval.d = new Double(v);
                                  return REAL;
                                }
{ALPHA}{WORD}*                  {
                                  echoToken();
                                  yylval.s = new String(yytext);
                                  return SYMBOL;
                                }
\"(\\.|[^"])*\"                 {
                                  static std::string escChars = "\\\"nrtv";
                                  static std::string repChars = "\\\"\n\r\t\v";
                                  
                                  echoToken();
                                  
                                  std::string s = yytext;
                                  
                                  // remove double quotes
                                  s = s.substr(1, s.length()-2);
                                  
                                  // replace escape sequences
                                  std::string es = "";
                                  size_t p0 = 0;
                                  size_t p1 = s.find('\\');
                                  size_t p2;
                                  while (p1 != std::string::npos) {
                                    es += s.substr(p0, p1-p0);
                                    p2 = escChars.find(s[p1+1]);
                                    if (p2 != std::string::npos) {
                                      es.append(1, repChars[p2]);
                                      p0 = p1 + 2;
                                    } else {
                                      es.append(1, '\\');
                                      p0 = p1 + 1;
                                    }
                                    p1 = s.find('\\', p0);
                                  }
                                  es += s.substr(p0);
                                  
                                  yylval.s = new String(es);
                                  
                                  return STRING;
                                }

  /* Comments */
"//".*$                         { /* do nothing */ }
"/*"                            { BEGIN MULTILINE_COMMENT; }
<MULTILINE_COMMENT>"*/"         { BEGIN INITIAL; }
<MULTILINE_COMMENT>\n           { yycolumn = 1; }
<MULTILINE_COMMENT>.            { /* do nothing */ }
<MULTILINE_COMMENT><<EOF>>      { yyerror("unclosed comment"); }

  /* Whitespaces */
"\n"                            {
                                  echoToken("eol");
                                  yycolumn = 1;
                                  return EOL;
                                }
[ \t]                           { /* ignore whitespace */ }
.                               {
                                  fprintf(stderr, "Mystery character: %c\n", yytext[0]);
                                  exit(0);
                                }

%%
