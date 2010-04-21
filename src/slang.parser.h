
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 80 "src/slang.parser.h"

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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 142 "src/slang.parser.h"
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



