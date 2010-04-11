%option noyywrap nodefault yylineno
%option reentrant bison-bridge bison-locations
%option extra-type="struct ParserData*"
  // %option header-file="src/calc.lexer.h"

%x MULTILINE_COMMENT

%{
#include "slang.parser.h"

#define YY_USER_ACTION \
  yylloc->first_line = yylloc->last_line = yylineno; \
  yylloc->first_column = yycolumn; \
  yylloc->last_column = yycolumn + yyleng - 1; \
  yylloc->filename = pd->filename; \
  yycolumn += yyleng;

%}

DIGIT     ([0-9])
EXP       ([eE][-+]?[0-9]+)
ALPHA     ([a-zA-Z])
ALPHANUM  ([a-zA-Z0-9])
WORD      ([a-zA-Z0-9_])

%%

%{
struct ParserData *pd = yyextra;
%}

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
"."                             { return yytext[0]; }

  /* Comparison */
"=="                            { return EQ; }
"!="                            { return NEQ; }
"<"                             { return LT; }
">"                             { return GT; }
"<="                            { return LTE; }
">="                            { return GTE; }

  /* Keywords */
"if"                            { return IF; }
"then"                          { return THEN; }
"else"                          { return ELSE; }
"while"                         { return WHILE; }
"do"                            { return DO; }
"function"                      { return FUNC; }
"end"                           { return END; }
"true"                          {
                                  yylval->b = new Boolean(true);
                                  return TRUE;
                                }
"false"                         {
                                  yylval->b = new Boolean(false);
                                  return FALSE;
                                }
"return"                        {
                                  yylval->inst = new Return(MakeLocation(yylloc));
                                  return RETURN;
                                }
"break"                         {
                                  yylval->inst = new Break(MakeLocation(yylloc));
                                  return BREAK;
                                }
"continue"                      {
                                  yylval->inst = new Continue(MakeLocation(yylloc));
                                  return CONTINUE;
                                }
"or"                            { return OR; }
"and"                           { return AND; }
"not"                           { return NOT; }

  /* Literals */
{DIGIT}+                        {
                                  LongInteger v;
                                  sscanf(yytext, "%lld", &v);
                                  yylval->i = new Integer(v);
                                  return INTEGER;
                                }
{DIGIT}+\.{DIGIT}+{EXP}?        {
                                  double v;
                                  sscanf(yytext, "%lf", &v);
                                  yylval->d = new Double(v);
                                  return REAL;
                                }
{ALPHA}{WORD}*                  {
                                  #ifdef _SYMTBL
                                   yylval->sym = SymbolTable::GetSymbol(yytext).id();
                                  #else
                                   yylval->s = new String(yytext);
                                  #endif
                                  return SYMBOL;
                                }
\"(\\.|[^"])*\"                 {
                                  static std::string escChars = "\\\"nrtv";
                                  static std::string repChars = "\\\"\n\r\t\v";
                                  
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
                                  
                                  yylval->s = new String(es);
                                  
                                  return STRING;
                                }

  /* Comments */
"//".*$                         { /* do nothing */ }
"/*"                            { BEGIN MULTILINE_COMMENT; }
<MULTILINE_COMMENT>"*/"         { BEGIN INITIAL; }
<MULTILINE_COMMENT>\n           { /* yycolumn = 1; */ }
<MULTILINE_COMMENT>.            { /* do nothing */ }
<MULTILINE_COMMENT><<EOF>>      { yyerror("unclosed comment"); }

  /* Whitespaces */
"\n"                            {
                                  // yycolumn = 1;
                                  return EOL;
                                }
[ \t]                           { /* ignore whitespace */ }
.                               {
                                  fprintf(stderr, "Mystery character: %c\n", yytext[0]);
                                  exit(0);
                                }

%%
