
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */


/* Line 189 of yacc.c  */
#line 73 "src/slang.parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 5 "src/slang.y"

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



/* Line 209 of yacc.c  */
#line 137 "src/slang.parser.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     REAL = 259,
     STRING = 260,
     TRUE = 261,
     FALSE = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     NEQ = 266,
     EQ = 267,
     LT = 268,
     GT = 269,
     LTE = 270,
     GTE = 271,
     AND = 272,
     OR = 273,
     NOT = 274,
     END = 275,
     EOL = 276,
     FUNC = 277,
     IF = 278,
     THEN = 279,
     ELSE = 280,
     DO = 281,
     WHILE = 282,
     SYMBOL = 283,
     CONCAT = 284,
     UMINUS = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 62 "src/slang.y"

  String *s;
  Double *d;
  Integer *i;
  Boolean *b;
  Object *o;
  Block *blk;
  size_t sym;
  Instruction *inst;
  std::vector<size_t> *syml;
  CodeSegment *cs;



/* Line 214 of yacc.c  */
#line 199 "src/slang.parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 224 "src/slang.parser.c"
/* Unqualified %code blocks.  */

/* Line 265 of yacc.c  */
#line 43 "src/slang.y"


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




/* Line 265 of yacc.c  */
#line 250 "src/slang.parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   216

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNRULES -- Number of states.  */
#define YYNSTATES  89

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    35,     2,     2,
      38,    39,    33,    31,    37,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,    10,    14,    18,    22,    26,
      30,    34,    38,    42,    46,    50,    54,    58,    62,    65,
      67,    69,    71,    73,    75,    77,    81,    84,    89,    90,
      92,    96,   102,   110,   116,   118,   121,   123,   125,   133,
     137,   142,   144,   148,   149,   152,   155,   156,   158
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    -1,    28,    -1,    42,    37,    28,    -1,
      43,    31,    43,    -1,    43,    32,    43,    -1,    43,    33,
      43,    -1,    43,    34,    43,    -1,    43,    35,    43,    -1,
      43,    12,    43,    -1,    43,    11,    43,    -1,    43,    13,
      43,    -1,    43,    14,    43,    -1,    43,    15,    43,    -1,
      43,    16,    43,    -1,    43,    17,    43,    -1,    43,    18,
      43,    -1,    19,    43,    -1,     3,    -1,     4,    -1,     5,
      -1,     6,    -1,     7,    -1,    28,    -1,    38,    43,    39,
      -1,    32,    43,    -1,    28,    38,    44,    39,    -1,    -1,
      43,    -1,    44,    37,    43,    -1,    23,    43,    24,    47,
      20,    -1,    23,    43,    24,    47,    25,    47,    20,    -1,
      27,    43,    26,    47,    20,    -1,     8,    -1,     8,    43,
      -1,     9,    -1,    10,    -1,    22,    28,    38,    42,    39,
      47,    20,    -1,    28,    29,    43,    -1,    28,    38,    44,
      39,    -1,    45,    -1,    46,    40,    45,    -1,    -1,    47,
      21,    -1,    47,    46,    -1,    -1,    21,    -1,    46,    21,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   108,   108,   111,   115,   121,   127,   133,   139,   145,
     151,   157,   163,   169,   175,   181,   187,   193,   199,   203,
     207,   211,   215,   219,   223,   227,   230,   234,   245,   246,
     247,   254,   262,   272,   280,   284,   288,   292,   297,   311,
     315,   326,   329,   336,   339,   342,   353,   357,   361
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING", "TRUE",
  "FALSE", "RETURN", "BREAK", "CONTINUE", "NEQ", "EQ", "LT", "GT", "LTE",
  "GTE", "AND", "OR", "NOT", "END", "EOL", "FUNC", "IF", "THEN", "ELSE",
  "DO", "WHILE", "SYMBOL", "'='", "CONCAT", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UMINUS", "','", "'('", "')'", "';'", "$accept", "paramlist",
  "expr", "exprlist", "stmt", "stmtlist", "body", "block", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
     284,    43,    45,    42,    47,    37,   285,    44,    40,    41,
      59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    44,    44,
      44,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    46,    46,    47,    47,    47,    48,    48,    48
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     2,     4,     0,     1,
       3,     5,     7,     5,     1,     2,     1,     1,     7,     3,
       4,     1,     3,     0,     2,     2,     0,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      46,    34,    36,    37,    47,     0,     0,     0,     0,    41,
       0,     0,    19,    20,    21,    22,    23,     0,    24,     0,
       0,    35,     0,     0,     0,     0,    28,    48,     0,     1,
      18,    28,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,    43,    43,
      39,    29,     0,    42,     0,    25,    11,    10,    12,    13,
      14,    15,    16,    17,     5,     6,     7,     8,     9,     3,
       0,     0,     0,     0,    40,    27,     0,    43,    31,    44,
      43,    45,    33,    30,     4,     0,     0,    38,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    70,    51,    52,     9,    81,    71,    11
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int16 yypact[] =
{
     188,    43,   -49,   -49,   -49,   -25,    43,    43,   -27,   -49,
     -14,     4,   -49,   -49,   -49,   -49,   -49,    43,    -8,    43,
      43,   131,    -7,    81,   106,    43,    43,   -49,   179,   -49,
      45,    43,   -49,    52,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    27,   -49,   -49,
     131,   131,   -22,   -49,    14,   -49,    95,    95,    95,    95,
      95,    95,    45,    45,   -21,   -21,   -49,   -49,   -49,   -49,
      15,     0,   147,    43,   -49,   -49,    46,   -49,   -49,   -49,
     -49,    33,   -49,   131,   -49,   163,   172,   -49,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,    -1,    51,    60,    89,   -48,   -49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int8 yytable[] =
{
      21,    72,    25,    22,    29,    23,    24,    27,     1,     2,
       3,    26,    44,    45,    46,    73,    30,    74,    32,    33,
      78,    79,     5,     6,    50,    80,    28,     7,     8,    85,
      31,    47,    86,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    12,    13,    14,    15,
      16,    73,    76,    75,    77,    69,    34,    35,    36,    37,
      38,    39,    17,    34,    35,    36,    37,    38,    39,    40,
      41,    18,    83,    28,    84,    19,    42,    43,    44,    45,
      46,    20,    54,    42,    43,    44,    45,    46,    53,    10,
       0,    55,    34,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,     0,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,    44,    45,
      46,     0,    49,     0,     0,     0,     0,    42,    43,    44,
      45,    46,    34,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,     0,     1,     2,     3,     0,     0,
       0,     0,    42,    43,    44,    45,    46,    82,    79,     5,
       6,     1,     2,     3,     7,     8,     0,     0,     0,     0,
       1,     2,     3,    87,    79,     5,     6,     1,     2,     3,
       7,     8,    88,    79,     5,     6,     1,     2,     3,     7,
       8,     5,     6,     0,     0,     0,     7,     8,     0,     4,
       5,     6,     0,     0,     0,     7,     8
};

static const yytype_int8 yycheck[] =
{
       1,    49,    29,    28,     0,     6,     7,    21,     8,     9,
      10,    38,    33,    34,    35,    37,    17,    39,    19,    20,
      20,    21,    22,    23,    25,    25,    40,    27,    28,    77,
      38,    38,    80,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,     3,     4,     5,     6,
       7,    37,    37,    39,    39,    28,    11,    12,    13,    14,
      15,    16,    19,    11,    12,    13,    14,    15,    16,    17,
      18,    28,    73,    40,    28,    32,    31,    32,    33,    34,
      35,    38,    31,    31,    32,    33,    34,    35,    28,     0,
      -1,    39,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    24,    11,    12,    13,    14,
      15,    16,    31,    32,    33,    34,    35,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    31,    32,    33,    34,
      35,    -1,    26,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    20,    21,    22,
      23,     8,     9,    10,    27,    28,    -1,    -1,    -1,    -1,
       8,     9,    10,    20,    21,    22,    23,     8,     9,    10,
      27,    28,    20,    21,    22,    23,     8,     9,    10,    27,
      28,    22,    23,    -1,    -1,    -1,    27,    28,    -1,    21,
      22,    23,    -1,    -1,    -1,    27,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    21,    22,    23,    27,    28,    45,
      46,    48,     3,     4,     5,     6,     7,    19,    28,    32,
      38,    43,    28,    43,    43,    29,    38,    21,    40,     0,
      43,    38,    43,    43,    11,    12,    13,    14,    15,    16,
      17,    18,    31,    32,    33,    34,    35,    38,    24,    26,
      43,    43,    44,    45,    44,    39,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    28,
      42,    47,    47,    37,    39,    39,    37,    39,    20,    21,
      25,    46,    20,    43,    28,    47,    47,    20,    20
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, pd, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, pd); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct ParserData *pd)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, pd)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct ParserData *pd;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (pd);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct ParserData *pd)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, pd)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct ParserData *pd;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, pd);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct ParserData *pd)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, pd)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    struct ParserData *pd;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , pd);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, pd); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct ParserData *pd)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, pd)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    struct ParserData *pd;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (pd);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "INTEGER" */

/* Line 1000 of yacc.c  */
#line 87 "src/slang.y"
	{ delete (yyvaluep->i); };

/* Line 1000 of yacc.c  */
#line 1256 "src/slang.parser.c"
	break;
      case 4: /* "REAL" */

/* Line 1000 of yacc.c  */
#line 86 "src/slang.y"
	{ delete (yyvaluep->d); };

/* Line 1000 of yacc.c  */
#line 1265 "src/slang.parser.c"
	break;
      case 5: /* "STRING" */

/* Line 1000 of yacc.c  */
#line 85 "src/slang.y"
	{ delete (yyvaluep->s); };

/* Line 1000 of yacc.c  */
#line 1274 "src/slang.parser.c"
	break;
      case 6: /* "TRUE" */

/* Line 1000 of yacc.c  */
#line 88 "src/slang.y"
	{ delete (yyvaluep->b); };

/* Line 1000 of yacc.c  */
#line 1283 "src/slang.parser.c"
	break;
      case 7: /* "FALSE" */

/* Line 1000 of yacc.c  */
#line 88 "src/slang.y"
	{ delete (yyvaluep->b); };

/* Line 1000 of yacc.c  */
#line 1292 "src/slang.parser.c"
	break;
      case 8: /* "RETURN" */

/* Line 1000 of yacc.c  */
#line 91 "src/slang.y"
	{ delete (yyvaluep->inst); };

/* Line 1000 of yacc.c  */
#line 1301 "src/slang.parser.c"
	break;
      case 9: /* "BREAK" */

/* Line 1000 of yacc.c  */
#line 91 "src/slang.y"
	{ delete (yyvaluep->inst); };

/* Line 1000 of yacc.c  */
#line 1310 "src/slang.parser.c"
	break;
      case 10: /* "CONTINUE" */

/* Line 1000 of yacc.c  */
#line 91 "src/slang.y"
	{ delete (yyvaluep->inst); };

/* Line 1000 of yacc.c  */
#line 1319 "src/slang.parser.c"
	break;
      case 42: /* "paramlist" */

/* Line 1000 of yacc.c  */
#line 92 "src/slang.y"
	{ delete (yyvaluep->syml); };

/* Line 1000 of yacc.c  */
#line 1328 "src/slang.parser.c"
	break;
      case 43: /* "expr" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1337 "src/slang.parser.c"
	break;
      case 44: /* "exprlist" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1346 "src/slang.parser.c"
	break;
      case 45: /* "stmt" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1355 "src/slang.parser.c"
	break;
      case 46: /* "stmtlist" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1364 "src/slang.parser.c"
	break;
      case 47: /* "body" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1373 "src/slang.parser.c"
	break;
      case 48: /* "block" */

/* Line 1000 of yacc.c  */
#line 93 "src/slang.y"
	{ delete (yyvaluep->cs); };

/* Line 1000 of yacc.c  */
#line 1382 "src/slang.parser.c"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct ParserData *pd);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct ParserData *pd)
#else
int
yyparse (pd)
    struct ParserData *pd;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 108 "src/slang.y"
    {
                                    (yyval.syml) = NULL;
                                  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 111 "src/slang.y"
    {
                                    (yyval.syml) = new std::vector<size_t>();
                                    (yyval.syml)->push_back((yyvsp[(1) - (1)].sym));
                                  ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 115 "src/slang.y"
    {
                                    (yyvsp[(1) - (3)].syml)->push_back((yyvsp[(3) - (3)].sym));
                                    (yyval.syml) = (yyvsp[(1) - (3)].syml);
                                  ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 121 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("+")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 127 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("-")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 133 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("*")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 139 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("/")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 145 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("%")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 151 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("==")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 157 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("!=")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 163 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("<")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 169 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol(">")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 175 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("<=")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 181 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol(">=")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 187 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("and")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 193 "src/slang.y"
    {
                          (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                          delete (yyvsp[(3) - (3)].cs);
                          (yyvsp[(1) - (3)].cs)->push_back(new Call(MakeLocation((yyloc)), Symbol("or")));
                          (yyval.cs) = (yyvsp[(1) - (3)].cs);
                        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 199 "src/slang.y"
    {
                          (yyvsp[(2) - (2)].cs)->append(new Call(MakeLocation((yyloc)), Symbol("not")));
                          (yyval.cs) = (yyvsp[(2) - (2)].cs);
                        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 203 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Push(MakeLocation((yyloc)), (yyvsp[(1) - (1)].i)));
                        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 207 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Push(MakeLocation((yyloc)), (yyvsp[(1) - (1)].d)));
                        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 211 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Push(MakeLocation((yyloc)), (yyvsp[(1) - (1)].s)));
                        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 215 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Push(MakeLocation((yyloc)), (yyvsp[(1) - (1)].b)));
                        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 219 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Push(MakeLocation((yyloc)), (yyvsp[(1) - (1)].b)));
                        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 223 "src/slang.y"
    {
                          (yyval.cs) = new CodeSegment();
                          (yyval.cs)->push_back(new Get(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (1)].sym))));
                        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 227 "src/slang.y"
    {
                          (yyval.cs) = (yyvsp[(2) - (3)].cs);
                        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 230 "src/slang.y"
    {
                                  (yyvsp[(2) - (2)].cs)->append(new Call(MakeLocation((yyloc)), Symbol("__uminus__")));
                                  (yyval.cs) = (yyvsp[(2) - (2)].cs);
                                ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 234 "src/slang.y"
    {
                                  if ((yyvsp[(3) - (4)].cs) != NULL) {
                                    (yyvsp[(3) - (4)].cs)->append(new Call(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (4)].sym))));
                                    (yyval.cs) = (yyvsp[(3) - (4)].cs);
                                  } else {
                                    (yyval.cs) = new CodeSegment();
                                    (yyval.cs)->append(new Call(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (4)].sym))));
                                  }
                                ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 245 "src/slang.y"
    { (yyval.cs) = NULL; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 246 "src/slang.y"
    { (yyval.cs) = (yyvsp[(1) - (1)].cs); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 247 "src/slang.y"
    {
                                (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                                delete (yyvsp[(3) - (3)].cs);
                                (yyval.cs) = (yyvsp[(1) - (3)].cs);
                              ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 254 "src/slang.y"
    {
                                                      Block *cond = new Block();
                                                      Block *body = new Block();
                                                      cond->setCode((yyvsp[(2) - (5)].cs));
                                                      body->setCode((yyvsp[(4) - (5)].cs));
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->append(new If(MakeLocation((yyloc)), cond, body));
                                                    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 262 "src/slang.y"
    {
                                                      Block *cond = new Block();
                                                      Block *body1 = new Block();
                                                      Block *body2 = new Block();
                                                      cond->setCode((yyvsp[(2) - (7)].cs));
                                                      body1->setCode((yyvsp[(4) - (7)].cs));
                                                      body2->setCode((yyvsp[(6) - (7)].cs));
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->append(new IfElse(MakeLocation((yyloc)), cond, body1, body2));
                                                    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 272 "src/slang.y"
    {
                                                      Block *cond = new Block();
                                                      Block *body = new Block();
                                                      cond->setCode((yyvsp[(2) - (5)].cs));
                                                      body->setCode((yyvsp[(4) - (5)].cs));
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->append(new While(MakeLocation((yyloc)), cond, body));
                                                    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 280 "src/slang.y"
    {
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->push_back((yyvsp[(1) - (1)].inst));
                                                    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 284 "src/slang.y"
    {
                                                      (yyval.cs) = (yyvsp[(2) - (2)].cs);
                                                      (yyvsp[(2) - (2)].cs)->push_back((yyvsp[(1) - (2)].inst));
                                                    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 288 "src/slang.y"
    {
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->push_back((yyvsp[(1) - (1)].inst));
                                                    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 292 "src/slang.y"
    {
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->push_back((yyvsp[(1) - (1)].inst));
                                                    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 297 "src/slang.y"
    {
                                                      // DefFunc
                                                      Block *fn = new Block();
                                                      if ((yyvsp[(4) - (7)].syml) != NULL) {
                                                        for (size_t i=0; i<(yyvsp[(4) - (7)].syml)->size(); ++i) {
                                                          Symbol s((*((yyvsp[(4) - (7)].syml)))[i]);
                                                          fn->addArgument(s);
                                                        }
                                                        delete (yyvsp[(4) - (7)].syml);
                                                      }
                                                      fn->setCode((yyvsp[(6) - (7)].cs));
                                                      (yyval.cs) = new CodeSegment();
                                                      (yyval.cs)->append(new DefFunc(MakeLocation((yyloc)), Symbol((yyvsp[(2) - (7)].sym)), fn));
                                                    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 311 "src/slang.y"
    {
                                                      (yyvsp[(3) - (3)].cs)->append(new Set(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (3)].sym))));
                                                      (yyval.cs) = (yyvsp[(3) - (3)].cs);
                                                    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 315 "src/slang.y"
    {
                                                      if ((yyvsp[(3) - (4)].cs) != NULL) {
                                                        (yyvsp[(3) - (4)].cs)->append(new Call(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (4)].sym))));
                                                        (yyval.cs) = (yyvsp[(3) - (4)].cs);
                                                      } else {
                                                        (yyval.cs) = new CodeSegment();
                                                        (yyval.cs)->append(new Call(MakeLocation((yyloc)), Symbol((yyvsp[(1) - (4)].sym))));
                                                      }
                                                    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 326 "src/slang.y"
    {
                                (yyval.cs) = (yyvsp[(1) - (1)].cs);
                              ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 329 "src/slang.y"
    {
                                (yyvsp[(1) - (3)].cs)->merge((yyvsp[(3) - (3)].cs));
                                delete (yyvsp[(3) - (3)].cs);
                                (yyval.cs) = (yyvsp[(1) - (3)].cs);
                              ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 336 "src/slang.y"
    {
                        (yyval.cs) = NULL;
                      ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 339 "src/slang.y"
    {
                        (yyval.cs) = (yyvsp[(1) - (2)].cs);
                      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 342 "src/slang.y"
    {
                        if ((yyvsp[(1) - (2)].cs) != NULL) {
                          (yyvsp[(1) - (2)].cs)->merge((yyvsp[(2) - (2)].cs));
                          delete (yyvsp[(2) - (2)].cs);
                          (yyval.cs) = (yyvsp[(1) - (2)].cs);
                        } else {
                          (yyval.cs) = (yyvsp[(2) - (2)].cs);
                        }
                      ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 353 "src/slang.y"
    {
                        (yyval.cs) = pd->code;
                        YYABORT;
                      ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 357 "src/slang.y"
    {
                        (yyval.cs) = pd->code;
                        YYACCEPT;
                      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 361 "src/slang.y"
    {
                        pd->code->merge((yyvsp[(1) - (2)].cs));
                        delete (yyvsp[(1) - (2)].cs);
                        (yyval.cs) = pd->code;
                        YYACCEPT;
                      ;}
    break;



/* Line 1455 of yacc.c  */
#line 2241 "src/slang.parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, pd, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, pd, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, pd, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, pd);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, pd);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, pd, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, pd);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, pd);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 369 "src/slang.y"


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
    SymbolTable::Clear();
    
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


