#include "slang.parser.h"

Location MakeLocation(YYLTYPE *loc) {
  return Location(loc->filename, loc->first_line, loc->first_column);
}

Location MakeLocation(YYLTYPE &loc) {
  return Location(loc.filename, loc.first_line, loc.first_column);
}

void yyerror(YYLTYPE *loc, struct ParserData *pd, const char *fmt, ...) {
  
  va_list l;
  va_start(l, fmt);
  
  if (loc->first_line) {
    
    if (loc->first_line != loc->last_line) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to line %d, column %d: ",
                      loc->filename,
                      loc->first_line,
                      loc->first_column,
                      loc->last_line,
                      loc->last_column);
      
    } else if (loc->first_column != loc->last_column) {
      fprintf(stderr, "In file \"%s\", line %d, column %d to %d: ",
                      loc->filename,
                      loc->first_line,
                      loc->first_column,
                      loc->last_column);
      
    } else {
      fprintf(stderr, "In file \"%s\", line %d, column %d: ",
                      loc->filename,
                      loc->first_line,
                      loc->first_column);
    }
  }
  
  vfprintf(stderr, fmt, l);
  va_end(l);
}

