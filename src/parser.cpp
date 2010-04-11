#include "slang.parser.h"

Location MakeLocation(YYLTYPE *loc) {
  return Location(loc->filename, loc->first_line, loc->first_column);
}

Location MakeLocation(YYLTYPE &loc) {
  return Location(loc.filename, loc.first_line, loc.first_column);
}

void yyerror(const char *fmt, ...) {
  
  extern YYLTYPE* yylloc;
  
  va_list l;
  va_start(l, fmt);
  
  if (yylloc->first_line) {
    
    if (yylloc->first_line != yylloc->last_line) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to line %d, column %d: ",
                      yylloc->filename,
                      yylloc->first_line,
                      yylloc->first_column,
                      yylloc->last_line,
                      yylloc->last_column);
      
    } else if (yylloc->first_column != yylloc->last_column) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to %d: ",
                      yylloc->filename,
                      yylloc->first_line,
                      yylloc->first_column,
                      yylloc->last_column);
      
    } else {
      fprintf(stderr, "In file \"%s\", line %d, column %d: ",
                      yylloc->filename,
                      yylloc->first_line,
                      yylloc->first_column);
    }
  }
  
  vfprintf(stderr, fmt, l);
  va_end(l);
}

