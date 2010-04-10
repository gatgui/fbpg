#include "slang.parser.h"

Location MakeLocation(YYLTYPE &) {
  return Location(loc.filename, loc.first_line, loc.first_column);
}

void echoToken(const char *s) {
  if (gEchoTokens) {
    fprintf(stdout, "<Token: \"%s\">\n", (s != 0 ? s : yytext));
  }
}

void yyerror(char *fmt, ...) {
  va_list l;
  va_start(l, fmt);
  
  if (yylloc.first_line) {
    
    if (yylloc.first_line != yylloc.last_line) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to line %d, column %d: ",
                      yylloc.filename,
                      yylloc.first_line,
                      yylloc.first_column,
                      yylloc.last_line,
                      yylloc.last_column);
      
    } else if (yylloc.first_column != yylloc.last_column) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to %d: ",
                      yylloc.filename,
                      yylloc.first_line,
                      yylloc.first_column,
                      yylloc.last_column);
      
    } else {
      fprintf(stderr, "In file \"%s\", line %d, column %d: ",
                      yylloc.filename,
                      yylloc.first_line,
                      yylloc.first_column);
    }
  }
  
  vfprintf(stderr, fmt, l);
  va_end(l);
}

