%locations
%define api.pure
%parse-param { struct ParserData *pd }

%code requires {
// this code goes in the generated header
// overrides location informations

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *filename;
} YYLTYPE;

#define YYLTYPE_IS_DECLARED 1

#define YYLLOC_DEFAULT(Current, Rhs, N) \
  do { \
    if (YYID (N)) { \
      (Current).first_line   = YYRHSLOC (Rhs, 1).first_line; \
      (Current).first_column = YYRHSLOC (Rhs, 1).first_column; \
      (Current).last_line    = YYRHSLOC (Rhs, N).last_line; \
      (Current).last_column  = YYRHSLOC (Rhs, N).last_column; \
      (Current).filename     = YYRHSLOC (Rhs, 1).filename; \
    } else { \
      (Current).first_line   = (Current).last_line = YYRHSLOC (Rhs, 0).last_line; \
      (Current).first_column = (Current).last_column = YYRHSLOC (Rhs, 0).last_column; \
      (Current).filename     = NULL; \
    } \
  } while (YYID (0))

#define YY_LOCATION_PRINT(File, Loc) \
  fprintf(File, "%s: %d.%d-%d.%d", \
                ((Loc).filename ? (Loc).filename : ""), \
                (Loc).first_line, (Loc).first_column, \
                (Loc).last_line,  (Loc).last_column)

#include "parser.h"
}

%code {

#ifdef _WIN32
// flex on windows doesn't have the option to generate the lexer header
// version is TOO fucking old, doesn't recognize reentrant
// => Sorry you will have to generate lexer and parser file on a decent platform
//typedef void* yyscan_t;
//extern int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner);
//extern int yylex_init_extra(struct ParserData*, yyscan_t*);
//extern int yyset_in(FILE*, yyscan_t);
#include "slang.lexer.h"
#else
#include "slang.lexer.h"
#endif

#define YYLEX_PARAM pd->scanner

}

%union {
  String  *s;
  Double  *d;
  Integer *i;
  Boolean *b;
  Object  *o;
  Block   *blk;
  size_t   sym;
  Instruction *inst;
  std::vector<String*> *sl;
  std::vector<size_t> *syml;
  CodeSegment *cs;
}

%token <i> INTEGER
%token <d> REAL
%token <s> STRING
%token <b> TRUE FALSE
%token <inst> RETURN BREAK CONTINUE
%token NEQ EQ LT GT LTE GTE AND OR NOT END EOL FUNC IF THEN ELSE DO WHILE

%type <cs> expr exprlist stmt stmtlist block body

  //%token <s> SYMBOL
  //%type <sl> paramlist
%token <sym> SYMBOL
%type <syml> paramlist

%destructor { delete $$; } <s>
%destructor { delete $$; } <d>
%destructor { delete $$; } <i>
%destructor { delete $$; } <b>
%destructor { delete $$; } <o>
%destructor { delete $$; } <blk>
%destructor { delete $$; } <inst>
%destructor { for (size_t i=0; i<$$->size(); ++i) {delete (*$$)[i];}; delete $$; } <sl>
%destructor { delete $$; } <syml>
%destructor { delete $$; } <cs>

%right '='
%left CONCAT
%left AND OR
%nonassoc NOT
%nonassoc NEQ EQ LT GT LTE GTE
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%start block

%%

paramlist : /* empty */           {
                                    $$ = NULL;
                                  }
          | SYMBOL                {
                                    #ifdef _SYMTBL
                                     $$ = new std::vector<size_t>();
                                    #else
                                     $$ = new std::vector<String*>();
                                    #endif
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
                          $1->push_back(new Call(MakeLocation(@$), Symbol("+")));
                          $$ = $1;
                        }
      | expr '-' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("-")));
                          $$ = $1;
                        }
      | expr '*' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("*")));
                          $$ = $1;
                        }
      | expr '/' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("/")));
                          $$ = $1;
                        }
      | expr '%' expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("%")));
                          $$ = $1;
                        }
      | expr EQ expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("==")));
                          $$ = $1;
                        }
      | expr NEQ expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("!=")));
                          $$ = $1;
                        }
      | expr LT expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("<")));
                          $$ = $1;
                        }
      | expr GT expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol(">")));
                          $$ = $1;
                        }
      | expr LTE expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("<=")));
                          $$ = $1;
                        }
      | expr GTE expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol(">=")));
                          $$ = $1;
                        }
      | expr AND expr   {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("and")));
                          $$ = $1;
                        }
      | expr OR expr    {
                          $1->merge($3);
                          delete $3;
                          $1->push_back(new Call(MakeLocation(@$), Symbol("or")));
                          $$ = $1;
                        }
      | NOT expr        {
                          $2->append(new Call(MakeLocation(@$), Symbol("not")));
                          $$ = $2;
                        }
      | INTEGER         {
                          $$ = new CodeSegment();
                          $$->push_back(new Push(MakeLocation(@$), $1));
                        }
      | REAL            {
                          $$ = new CodeSegment();
                          $$->push_back(new Push(MakeLocation(@$), $1));
                        }
      | STRING          {
                          $$ = new CodeSegment();
                          $$->push_back(new Push(MakeLocation(@$), $1));
                        }
      | TRUE            {
                          $$ = new CodeSegment();
                          $$->push_back(new Push(MakeLocation(@$), $1));
                        }
      | FALSE           {
                          $$ = new CodeSegment();
                          $$->push_back(new Push(MakeLocation(@$), $1));
                        }
      | SYMBOL          {
                          $$ = new CodeSegment();
                          #ifdef _SYMTBL
                           $$->push_back(new Get(MakeLocation(@$), Symbol($1)));
                          #else
                           $$->push_back(new Get(MakeLocation(@$), $1->getValue()));
                           delete $1;
                          #endif
                        }
      | '(' expr ')'    {
                          $$ = $2;
                        }
      | '-' expr %prec UMINUS   {
                                  $2->append(new Call(MakeLocation(@$), Symbol("__uminus__")));
                                  $$ = $2;
                                }
      | SYMBOL '(' exprlist ')' {
                                  if ($3 != NULL) {
                                    #ifdef _SYMTBL
                                     $3->append(new Call(MakeLocation(@$), Symbol($1)));
                                    #else
                                     $3->append(new Call(MakeLocation(@$), $1->getValue()));
                                    #endif
                                    $$ = $3;
                                  } else {
                                    $$ = new CodeSegment();
                                    #ifdef _SYMTBL
                                     $$->append(new Call(MakeLocation(@$), Symbol($1)));
                                    #else
                                     $$->append(new Call(MakeLocation(@$), $1->getValue()));
                                    #endif
                                  }
                                  #ifndef _SYMTBL
                                   delete $1;
                                  #endif
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

stmt  : IF expr THEN body END                       {
                                                      Block *cond = new Block();
                                                      Block *body = new Block();
                                                      cond->setCode($2);
                                                      body->setCode($4);
                                                      $$ = new CodeSegment();
                                                      $$->append(new If(MakeLocation(@$), cond, body));
                                                    }
      | IF expr THEN body ELSE body END             {
                                                      Block *cond = new Block();
                                                      Block *body1 = new Block();
                                                      Block *body2 = new Block();
                                                      cond->setCode($2);
                                                      body1->setCode($4);
                                                      body2->setCode($6);
                                                      $$ = new CodeSegment();
                                                      $$->append(new IfElse(MakeLocation(@$), cond, body1, body2));
                                                    }
      | WHILE expr DO body END                      {
                                                      Block *cond = new Block();
                                                      Block *body = new Block();
                                                      cond->setCode($2);
                                                      body->setCode($4);
                                                      $$ = new CodeSegment();
                                                      $$->append(new While(MakeLocation(@$), cond, body));
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
      // | SYMBOL '=' FUNC '(' paramlist ')' body END  {
      | FUNC SYMBOL '(' paramlist ')' body END      {
                                                      // DefFunc
                                                      Block *fn = new Block();
                                                      if ($4 != NULL) {
                                                        for (size_t i=0; i<$4->size(); ++i) {
                                                          #ifdef _SYMTBL
                                                           Symbol s((*($4))[i]);
                                                           fn->addArgument(s);
                                                          #else
                                                           String *s = (*($4))[i];
                                                           fn->addArgument(s->getValue());
                                                           delete s;
                                                          #endif
                                                        }
                                                        delete $4;
                                                      }
                                                      fn->setCode($6);
                                                      $$ = new CodeSegment();
                                                      #ifdef _SYMTBL
                                                       $$->append(new DefFunc(MakeLocation(@$), Symbol($2), fn));
                                                      #else
                                                       $$->append(new DefFunc(MakeLocation(@$), $2->getValue(), fn));
                                                       delete $2;
                                                      #endif
                                                    }
      | SYMBOL '=' expr                             {
                                                      #ifdef _SYMTBL
                                                       $3->append(new Set(MakeLocation(@$), Symbol($1)));
                                                      #else
                                                       $3->append(new Set(MakeLocation(@$), $1->getValue()));
                                                       delete $1;
                                                      #endif
                                                      $$ = $3;
                                                    }
      | SYMBOL '(' exprlist ')'                     {
                                                      if ($3 != NULL) {
                                                        #ifdef _SYMTBL
                                                         $3->append(new Call(MakeLocation(@$), Symbol($1)));
                                                        #else
                                                         $3->append(new Call(MakeLocation(@$), $1->getValue()));
                                                        #endif
                                                        $$ = $3;
                                                      } else {
                                                        $$ = new CodeSegment();
                                                        #ifdef _SYMTBL
                                                         $$->append(new Call(MakeLocation(@$), Symbol($1)));
                                                        #else
                                                         $$->append(new Call(MakeLocation(@$), $1->getValue()));
                                                        #endif
                                                      }
                                                      #ifndef _SYMTBL
                                                       delete $1;
                                                      #endif
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
                        $$ = pd->code;
                        YYABORT;
                      }
      | EOL           {
                        $$ = pd->code;
                        YYACCEPT;
                      }
      | stmtlist EOL  {
                        pd->code->merge($1);
                        delete $1;
                        YYACCEPT;
                      }
      ;

%%

int main(int argc, char **argv) {
#ifdef _MEMMGR
  HeapManager hm;
#endif

  if (argc < 2) {
    fprintf(stderr, "Usage: calc <filename>\n");
    return 1;
  }
  
  ParserData pd;
  
  pd.filename = argv[1];
  
  FILE *f = fopen(argv[1], "r");

  if (!f) {
    fprintf(stderr, "Could not read file \"%s\"\n", argv[1]);
    return 1;
  }
  
  yylex_init_extra(&pd, &(pd.scanner));
  yyset_in(f, pd.scanner);
  
  bool printCode = false;
  
  for (int i=2; i<argc; ++i) {
    if (!strcmp(argv[i], "-pc") || !strcmp(argv[i], "--print-code")) {
      printCode = true;
    }
    
  }
  
  int rv = 0;
  
  pd.code = new CodeSegment();
  
  while (rv == 0) {
    rv = yyparse(&pd);
  }
  
  if (printCode) {
    std::cout << std::endl << "Returned code segment:" << std::endl;
    pd.code->toStream(std::cout, "  ");
    std::cout << std::endl;
  }
  
  //std::cout << std::endl << "Evaluate code..." << std::endl;
  
  try {
    Context *ctx = new Context();
    Stack *stack = new Stack();
    
    RegisterBuiltins(ctx);
    
    pd.code->eval(stack, ctx);
    
    delete pd.code;
    
    // cleanup
    stack->clear();
    ctx->cleanup();
    ctx->decRef();
    delete stack;
#ifdef _SYMTBL
    SymbolTable::Clear();
#endif
    
  } catch (Exception &e) {
    std::cerr << "*** Caught exception ***" << std::endl;
    std::cerr << "  " << e.what() << std::endl;
    const CallStack *cs = e.getCallStack();
    if (cs) {
      std::cerr << cs->toString("    ") << std::endl;
    }
  }
  
  std::cout << std::endl;
  
  fclose(f);
  
#if defined(_MEMMGR) && defined(_DEBUG)
  hm.status();
#endif
  
#if defined(_CTXI)
  extern void PrintContextTime();
  PrintContextTime();
#endif
  return rv;
}

