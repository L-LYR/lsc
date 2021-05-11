/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_LSC_ST_TAB_H_INCLUDED
# define YY_YY_LSC_ST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "lsc-st.y"

    #include "st.h"

#line 52 "lsc-st.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    I32 = 259,
    F32 = 260,
    STRING = 261,
    BOOL = 262,
    IF = 263,
    ELSE = 264,
    FOR = 265,
    RETURN = 266,
    BREAK = 267,
    CONTINUE = 268,
    PRINT = 269,
    SCAN = 270,
    BCONSTANT = 271,
    IDENTIFIER = 272,
    ICONSTANT = 273,
    FCONSTANT = 274,
    SCONSTANT = 275,
    PLUS = 276,
    MINUS = 277,
    INC = 278,
    DEC = 279,
    BNOT = 280,
    NOT = 281,
    MUL = 282,
    DIV = 283,
    MOD = 284,
    LT = 285,
    GT = 286,
    LE = 287,
    GE = 288,
    EQ = 289,
    NE = 290,
    SL = 291,
    SR = 292,
    BAND = 293,
    BOR = 294,
    BXOR = 295,
    AND = 296,
    OR = 297,
    ASSIGN = 298,
    COMMA = 299,
    LB = 300,
    RB = 301,
    LSB = 302,
    RSB = 303,
    LCB = 304,
    RCB = 305,
    SEMICOLON = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "lsc-st.y"

    STNode* node;
    // need a pointer to symbol table
    const char* str;

#line 121 "lsc-st.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LSC_ST_TAB_H_INCLUDED  */
