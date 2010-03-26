%{
#include "context.h"
#include "stack.h"
#include "object.h"
#include "instruction.h"
#include "builtins.h"
#include <cstdarg>

extern int yylex();
extern FILE *yyin;

void yyerror(char *fmt, ...) {
  va_list l;
  va_start(l, fmt);
  vfprintf(stderr, fmt, l);
  va_end(l);
}

CodeSegment *gTopCode = 0;

%}

%union {
  String  *s;
  Double  *d;
  Integer *i;
  Boolean *b;
  Object  *o;
  Block   *blk;
  Instruction *inst;
  std::vector<String*> *sl;
  CodeSegment *cs;
}

%token <i> INTEGER
%token <d> REAL
%token <s> STRING SYMBOL
%token <b> TRUE FALSE
%token <blk> FUNC IF THEN ELSE DO WHILE
%token <inst> RETURN BREAK CONTINUE
%token NEQ EQ LT GT LTE GTE AND OR NOT END EOL

%type <cs> expr exprlist stmt stmtlist block body
%type <sl> paramlist

%right '='
%nonassoc NEQ EQ LT GT LTE GTE
%left AND OR
%left '+' '-' CONCAT
%left '*' '/'
%nonassoc NOT UMINUS

%start block

%%

paramlist : /* empty */           {
                                    $$ = NULL;
                                  }
          | SYMBOL                {
                                    $$ = new std::vector<String*>();
                                    $$->push_back($1);
                                  }
          | paramlist ',' SYMBOL  {
                                    $1->push_back($3);
                                    $$ = $1;
                                  }
          ;

expr  : expr '+' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("+"));
                          $$ = $1;
                        }
      | expr '-' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("-"));
                          $$ = $1;
                        }
      | expr '*' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("*"));
                          $$ = $1;
                        }
      | expr '/' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("-"));
                          $$ = $1;
                        }
      | expr CONCAT expr  {
                            $1->merge($3);
                            delete $3;
                            $1->push_back(new Call(".."));
                            $$ = $1;
                          }
      | expr EQ expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("=="));
                          $$ = $1;
                        }
      | expr NEQ expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("!="));
                          $$ = $1;
                        }
      | expr LT expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("<"));
                          $$ = $1;
                        }
      | expr GT expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(">"));
                          $$ = $1;
                        }
      | expr LTE expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call("<="));
                          $$ = $1;
                        }
      | expr GTE expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(">="));
                          $$ = $1;
                        }
      | INTEGER         {
                          $$ = new CodeSegment();
                          $$->push_back(new Push($1));
                        }
      | REAL            {
                          $$ = new CodeSegment();
                          $$->push_back(new Push($1));
                        }
      | STRING          {
                          $$ = new CodeSegment();
                          $$->push_back(new Push($1));
                        }
      | TRUE            {
                          $$ = new CodeSegment();
                          $$->push_back(new Push($1));
                        }
      | FALSE           {
                          $$ = new CodeSegment();
                          $$->push_back(new Push($1));
                        }
      | SYMBOL          {
                          $$ = new CodeSegment();
                          $$->push_back(new Get($1->getValue()));
                          delete $1;
                        }
      | '(' expr ')'    {
                          $$ = $2;
                        }
      | '-' expr %prec UMINUS   {
                                  $2->append(new Call("__uminus__"));
                                  $$ = $2;
                                }
      | SYMBOL '(' exprlist ')' {
                                  if ($3 != NULL) {
                                    $3->append(new Call($1->getValue()));
                                    $$ = $3;
                                  } else {
                                    $$ = new CodeSegment();
                                    $$->append(new Call($1->getValue()));
                                  }
                                  delete $1;
                                }
      ;

exprlist  : /* empty */       { $$ = NULL; }
          | expr              { $$ = $1; }
          | exprlist ',' expr {
                                $1->merge($3);
                                delete $3;
                                $$ = $1;
                              }
          ;

  //stmt  : expr                                        {
  //                                                      $$ = $1;
  //                                                    }
  //      | IF expr THEN body END                       {
stmt  : IF expr THEN body END                       {
                                                      $1->setCode($2);
                                                      $3->setCode($4);
                                                      $$ = new CodeSegment();
                                                      $$->append(new If($1, $3));
                                                    }
      | IF expr THEN body ELSE body END             {
                                                      $1->setCode($2);
                                                      $3->setCode($4);
                                                      $5->setCode($6);
                                                      $$ = new CodeSegment();
                                                      $$->append(new IfElse($1, $3, $5));
                                                    }
      | WHILE expr DO body END                      {
                                                      $1->setCode($2);
                                                      $3->setCode($4);
                                                      $$ = new CodeSegment();
                                                      $$->append(new While($1, $3));
                                                    }
      | RETURN                                      {
                                                      $$ = new CodeSegment();
                                                      $$->push_back($1);
                                                    }
      | RETURN expr                                 {
                                                      $$ = $2;
                                                      $2->push_back($1);
                                                    }
      | BREAK                                       {
                                                      $$ = new CodeSegment();
                                                      $$->push_back($1);
                                                    }
      | CONTINUE                                    {
                                                      $$ = new CodeSegment();
                                                      $$->push_back($1);
                                                    }
      | SYMBOL '=' FUNC '(' paramlist ')' body END  {
                                                      if ($5 != NULL) {
                                                        for (size_t i=0; i<$5->size(); ++i) {
                                                          String *s = (*($5))[i];
                                                          $3->addArgument(s->getValue());
                                                          delete s;
                                                        }
                                                        delete $5;
                                                      }
                                                      $3->setCode($7);
                                                      $$ = new CodeSegment();
                                                      $$->append(new Push($3));
                                                      $$->append(new Set($1->getValue()));
                                                      delete $1;
                                                    }
      | SYMBOL '=' expr                             {
                                                      $3->append(new Set($1->getValue()));
                                                      delete $1;
                                                      $$ = $3;
                                                    }
      | SYMBOL '(' exprlist ')'                     {
                                                      if ($3 != NULL) {
                                                        $3->append(new Call($1->getValue()));
                                                        $$ = $3;
                                                      } else {
                                                        $$ = new CodeSegment();
                                                        $$->append(new Call($1->getValue()));
                                                      }
                                                      delete $1;
                                                    }
      ;

stmtlist  : stmt              {
                                $$ = $1;
                              }
          | stmtlist ';' stmt {
                                $1->merge($3);
                                delete $3;
                                $$ = $1;
                              }
          ;

body  : /* empty */   {
                        $$ = NULL;
                      }
      | body EOL      {
                        $$ = $1;
                      }
      | body stmtlist {
                        if ($1 != NULL) {
                          $1->merge($2);
                          delete $2;
                          $$ = $1;
                        } else {
                          $$ = $2;
                        }
                      }
      ;

block : /* empty */   {
                        $$ = gTopCode;
                        YYABORT;
                      }
      | EOL           {
                        $$ = gTopCode;
                        YYACCEPT;
                      }
      | stmtlist EOL  {
                        gTopCode->merge($1);
                        delete $1;
                        YYACCEPT;
                      }
      ;

%%

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: calc <filename>\n");
    return 1;
  }
  
  FILE *f = fopen(argv[1], "r");

  if (!f) {
    fprintf(stderr, "Could not read file \"%s\"\n", argv[1]);
    return 1;
  }

  yyin = f;
  
  bool lexonly = false;
  if (argc >= 3) {
    if (!strcmp(argv[2], "-lo") || !strcmp(argv[2], "--lex-only")) {
      lexonly = true;
    }
  }
  
  int rv = 0;
  
  extern bool gEchoTokens;
  
  if (lexonly) {
    gEchoTokens = true;
    int token = yylex();
    while (token != 0) {
      token = yylex();
    }
  } else {
    
    gTopCode = new CodeSegment();
    
    while (rv == 0) {
      rv = yyparse();
    }
    
    std::cout << std::endl << "Returned code segment:" << std::endl;
    
    gTopCode->toStream(std::cout, "  ");
    
    std::cout << std::endl;
    
    std::cout << std::endl << "Evaluate code..." << std::endl;
    
    try {
    
      Context ctx;
      Stack stack;
      
      RegisterBuiltins(ctx);
      
      gTopCode->eval(stack, ctx);
      
      delete gTopCode;
      
    } catch (std::exception &e) {
      std::cerr << "*** Error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
    
  }

  fclose(f);
  
  return rv;
}

