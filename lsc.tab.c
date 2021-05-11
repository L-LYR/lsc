/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 7 "lsc.y"

    #include <stdio.h>
    #include "ast.h"
    #include "panic.h"
    #include "text.h"
    void yyerror(const char *s);
    int yylex(void);

    const char* yytext;
    AST t;

#line 79 "lsc.tab.c"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_LSC_TAB_H_INCLUDED
# define YY_YY_LSC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "lsc.y"

    #include "ast.h"

#line 129 "lsc.tab.c"

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
#line 19 "lsc.y"

    ASTNode* node;
    // need a pointer to symbol table
    const char* str;

#line 198 "lsc.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LSC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   454

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  202

#define YYUNDEFTOK  2
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    52,    52,    55,    59,    66,    67,    71,    76,    84,
      90,    93,    96,    99,   102,   105,   114,   118,   125,   127,
     133,   140,   155,   160,   163,   166,   172,   176,   183,   187,
     194,   200,   209,   213,   220,   237,   240,   244,   248,   255,
     259,   266,   270,   277,   278,   279,   280,   281,   282,   286,
     289,   295,   299,   303,   307,   314,   319,   324,   332,   338,
     347,   351,   358,   359,   367,   368,   376,   377,   381,   385,
     389,   393,   397,   404,   405,   410,   414,   421,   424,   427,
     430,   433,   436,   441,   445,   452,   453,   461,   462,   470,
     471,   479,   480,   488,   489,   497,   498,   503,   511,   512,
     517,   522,   527,   535,   536,   541,   549,   550,   555,   563,
     564,   569,   574
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"void\"", "\"i32\"", "\"f32\"",
  "\"string\"", "\"bool\"", "\"if\"", "\"else\"", "\"for\"", "\"return\"",
  "\"break\"", "\"continue\"", "\"print\"", "\"scan\"",
  "\"Bool Constant\"", "\"Identifier\"", "\"Integer Constant\"",
  "\"Float Constant\"", "\"String Constant\"", "\"+\"", "\"-\"", "\"++\"",
  "\"--\"", "\"~\"", "\"!\"", "\"*\"", "\"/\"", "\"%\"", "\"<\"", "\">\"",
  "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\"<<\"", "\">>\"", "\"&\"",
  "\"|\"", "\"^\"", "\"&&\"", "\"||\"", "\"=\"", "\",\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\";\"", "$accept", "program",
  "global_list", "global_declaration_or_definition", "declaration",
  "identifier", "type_specifiers", "init_declarator_list",
  "init_declarator", "declarator", "array_length", "initializer",
  "initializer_list", "parameter_type_list", "function_definition",
  "parameter_declarator_list", "parameter_declarator",
  "compound_statement", "statement_list", "declaration_list", "statement",
  "expression_statement", "jump_statement", "selection_statement",
  "loop_statement", "io_statement", "expression", "assignment_expression",
  "unary_expression", "postfix_expression", "primary_expression",
  "argument_list", "logical_or_expression", "logical_and_expression",
  "bitwise_or_expression", "bitwise_xor_expression",
  "bitwise_and_expression", "equality_expression", "relational_expression",
  "shift_expression", "additive_expression", "multiplicative_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF (-141)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      49,  -141,  -141,  -141,  -141,  -141,    17,    49,  -141,  -141,
      -9,  -141,  -141,  -141,  -141,     2,   -10,   -25,  -141,     1,
    -141,   -11,    27,     8,  -141,   363,     2,  -141,    -4,    -9,
      35,    51,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
     181,   181,   181,   181,   181,   181,   181,   363,  -141,  -141,
    -141,    20,     5,    15,    39,    29,    78,    67,    96,    53,
      99,   116,    48,    43,   168,  -141,    85,    49,    94,    49,
      -4,  -141,   104,  -141,  -141,  -141,  -141,  -141,    52,  -141,
    -141,    -3,   181,   181,   397,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,  -141,   108,   112,   103,   110,   111,   124,
     132,  -141,  -141,  -141,    -9,  -141,   261,   217,  -141,  -141,
    -141,  -141,  -141,  -141,   -23,   148,  -141,    -9,  -141,  -141,
     181,  -141,   352,  -141,  -141,    30,  -141,  -141,    57,    39,
      29,    78,    67,    96,    53,    53,    99,    99,    99,    99,
     116,   116,    48,    48,  -141,  -141,  -141,   181,   316,  -141,
     -15,  -141,  -141,   181,   181,   151,  -141,  -141,  -141,  -141,
     305,  -141,  -141,  -141,  -141,  -141,   181,  -141,    58,   316,
    -141,    65,    69,    49,  -141,  -141,    -4,   408,   157,   158,
     148,   201,    -4,    70,  -141,  -141,    16,  -141,    -4,  -141,
    -141,  -141
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    10,    11,    12,    13,    14,     0,     2,     3,     5,
       0,     6,     1,     4,     9,     0,    20,     0,    16,    18,
      22,     0,     0,     0,     7,     0,     0,    15,     0,    28,
       0,     0,    32,    20,    17,    78,    77,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,    19,    23,
     109,    66,    73,    64,    85,    87,    89,    91,    93,    95,
      98,   103,   106,     0,     0,    30,    34,     0,     0,     0,
       0,    69,    66,    70,    67,    68,    71,    72,     0,    62,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
       0,    35,    49,    41,     0,    43,     0,     0,    39,    44,
      45,    46,    47,    48,     0,    29,     8,     0,    33,    31,
       0,    82,     0,    24,    65,     0,    75,    83,     0,    86,
      88,    90,    92,    94,    96,    97,    99,   100,   101,   102,
     104,   105,   107,   108,   110,   111,   112,     0,     0,    53,
       0,    52,    51,     0,     0,    20,    36,    40,    37,    42,
       0,    50,    63,    25,    27,    74,     0,    76,     0,     0,
      54,     0,     0,     0,    38,    84,     0,     0,     0,     0,
      28,    55,     0,     0,    60,    61,     0,    58,     0,    56,
      57,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,   204,   -48,    -7,   -18,  -141,   189,   -27,
     188,   -38,  -141,  -141,  -141,  -141,   146,   -28,   127,  -141,
    -109,  -140,  -141,    50,  -141,  -141,   -40,   -20,   -30,   -24,
    -141,   -22,  -141,   131,   159,   160,   161,   162,    59,    -5,
      63,    68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    33,    10,    17,    18,    19,
      21,    48,    81,    30,    11,    31,    32,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,    79,    50,    72,
      52,   138,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    51,    66,    16,    29,    49,    78,   167,    14,    80,
      71,    73,    74,    75,    76,    77,   113,    12,   179,    23,
      20,   130,    51,    51,   104,    14,    24,    49,   171,   130,
       1,     2,     3,     4,     5,    22,   180,    27,    15,   187,
      51,   132,   129,   135,    25,    64,   114,   133,    26,   125,
      84,   127,     1,     2,     3,     4,     5,    85,    51,    51,
      51,   167,   134,    82,   137,    64,   160,    83,    87,   169,
     154,   155,   156,    28,   130,   100,   101,   102,   175,    67,
      86,    68,    51,    92,    93,    94,    95,   146,   147,   148,
     149,   103,    51,    51,   174,    69,   130,    70,   131,   114,
      66,   176,   130,   177,   186,    89,    51,   165,    51,   176,
     172,   188,    49,   176,   130,   189,   198,   178,    88,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      90,    91,    26,    51,    51,    96,    97,    98,    99,    51,
      51,   181,   182,   137,   137,   126,    51,   193,    46,   144,
     145,    83,    51,   157,   159,    51,   185,   158,   191,   150,
     151,   161,   162,    51,   197,   190,   152,   153,   199,   163,
     201,     1,     2,     3,     4,     5,   104,   164,   105,   106,
     107,   108,   109,   110,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    15,   183,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   194,   195,
     196,    13,    34,    46,    63,   128,   139,    64,   111,   112,
       1,     2,     3,     4,     5,   104,    46,   105,   106,   107,
     108,   109,   110,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,   170,   140,   200,   141,     0,   142,
       0,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,     0,     0,     0,    64,   168,   112,   104,
       0,   105,   106,   107,   108,   109,   110,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,     0,     0,
      64,   166,   112,   104,     0,   105,   106,   107,   108,   109,
     110,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,     0,    64,   184,   112,     0,     0,     0,
       0,    46,     0,     0,     0,     0,     0,   112,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
       0,    47,   173,     0,     0,     0,     0,     0,    46,     0,
       0,     0,    47,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,     0,     0,     0,
       0,     0,    46,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,   192
};

static const yytype_int16 yycheck[] =
{
      28,    25,    29,    10,    22,    25,    46,   116,    17,    47,
      40,    41,    42,    43,    44,    45,    64,     0,   158,    44,
      18,    44,    46,    47,     8,    17,    51,    47,    51,    44,
       3,     4,     5,     6,     7,    45,    51,    48,    47,   179,
      64,    44,    70,    83,    43,    49,    64,    50,    47,    67,
      45,    69,     3,     4,     5,     6,     7,    42,    82,    83,
      84,   170,    82,    43,    84,    49,   106,    47,    39,   117,
     100,   101,   102,    46,    44,    27,    28,    29,    48,    44,
      41,    46,   106,    30,    31,    32,    33,    92,    93,    94,
      95,    48,   116,   117,   132,    44,    44,    46,    46,   117,
     127,    44,    44,    46,    46,    38,   130,   114,   132,    44,
     130,    46,   132,    44,    44,    46,    46,   157,    40,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      34,    35,    47,   157,   158,    36,    37,    21,    22,   163,
     164,   163,   164,   163,   164,    51,   170,   187,    45,    90,
      91,    47,   176,    45,    51,   179,   176,    45,   186,    96,
      97,    51,    51,   187,   192,   183,    98,    99,   196,    45,
     198,     3,     4,     5,     6,     7,     8,    45,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    47,    45,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    51,    51,
       9,     7,    23,    45,    26,    69,    85,    49,    50,    51,
       3,     4,     5,     6,     7,     8,    45,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   117,    86,   196,    87,    -1,    88,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    49,    50,    51,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      49,    50,    51,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    49,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    53,    54,    55,    56,
      58,    66,     0,    55,    17,    47,    57,    59,    60,    61,
      18,    62,    45,    44,    51,    43,    47,    48,    46,    58,
      65,    67,    68,    57,    60,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    45,    49,    63,    79,
      80,    81,    82,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    62,    49,    69,    61,    44,    46,    44,
      46,    80,    81,    80,    80,    80,    80,    80,    78,    79,
      63,    64,    43,    47,    45,    42,    41,    39,    40,    38,
      34,    35,    30,    31,    32,    33,    36,    37,    21,    22,
      27,    28,    29,    48,     8,    10,    11,    12,    13,    14,
      15,    50,    51,    56,    58,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    58,    51,    58,    68,    69,
      44,    46,    44,    50,    79,    78,    46,    79,    83,    85,
      86,    87,    88,    89,    90,    90,    91,    91,    91,    91,
      92,    92,    93,    93,    80,    80,    80,    45,    45,    51,
      78,    51,    51,    45,    45,    57,    50,    72,    50,    56,
      70,    51,    79,    50,    63,    48,    44,    46,    78,    73,
      51,    83,    83,    45,    50,    79,    46,    73,    46,    46,
      58,    69,    46,    78,    51,    51,     9,    69,    46,    69,
      75,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    56,    56,    57,
      58,    58,    58,    58,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    89,    90,    90,
      90,    90,    90,    91,    91,    91,    92,    92,    92,    93,
      93,    93,    93
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     6,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     1,     3,
       1,     4,     1,     1,     3,     4,     1,     3,     1,     3,
       5,     6,     1,     3,     2,     2,     3,     3,     4,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     5,     7,     7,     6,     7,
       5,     5,     1,     3,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     1,     4,     3,     4,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 52 "lsc.y"
                      {t.root = (yyval.node);}
#line 1581 "lsc.tab.c"
    break;

  case 3:
#line 55 "lsc.y"
                                       {
        (yyval.node) = NewASTNode(GlobalDeclOrDefList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1591 "lsc.tab.c"
    break;

  case 4:
#line 59 "lsc.y"
                                                    {
        (yyval.node) = NewASTNode(GlobalDeclOrDefList);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1601 "lsc.tab.c"
    break;

  case 7:
#line 71 "lsc.y"
                                                     {
        (yyval.node) = NewASTNode(Declaration);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[-1].node);
        SpecifyType((yyvsp[-1].node), (yyvsp[-2].node)->attr[0]);
    }
#line 1612 "lsc.tab.c"
    break;

  case 8:
#line 76 "lsc.y"
                                                                      {
        (yyval.node) = NewASTNode(FunctionDecl);
        (yyval.node)->attr[0] = (yyvsp[-5].node);
        (yyval.node)->attr[1] = (yyvsp[-4].node);
        (yyval.node)->attr[2] = (yyvsp[-2].node);
    }
#line 1623 "lsc.tab.c"
    break;

  case 9:
#line 84 "lsc.y"
                 {
        (yyval.node) = NewASTNode(Identifier);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 1632 "lsc.tab.c"
    break;

  case 10:
#line 90 "lsc.y"
           {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = CopyStr("void");
    }
#line 1641 "lsc.tab.c"
    break;

  case 11:
#line 93 "lsc.y"
           {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = CopyStr("i32");
    }
#line 1650 "lsc.tab.c"
    break;

  case 12:
#line 96 "lsc.y"
           {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = CopyStr("f32");
    }
#line 1659 "lsc.tab.c"
    break;

  case 13:
#line 99 "lsc.y"
              {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = CopyStr("string");
    }
#line 1668 "lsc.tab.c"
    break;

  case 14:
#line 102 "lsc.y"
            {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = CopyStr("bool");
    }
#line 1677 "lsc.tab.c"
    break;

  case 15:
#line 105 "lsc.y"
                                            {
        (yyval.node) = NewASTNode(TypeSpecifier);
        (yyval.node)->attr[0] = ConcatenateStr((yyvsp[-3].node)->attr[0], "[", (yyvsp[-1].str), "]", NULL);
        free((void*)((yyvsp[-3].node)->attr[0]));
        free((yyvsp[-3].node));
        free((void*)(yyvsp[-1].str));
    }
#line 1689 "lsc.tab.c"
    break;

  case 16:
#line 114 "lsc.y"
                      {
        (yyval.node) = NewASTNode(DeclaratorList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1699 "lsc.tab.c"
    break;

  case 17:
#line 118 "lsc.y"
                                                  {
        (yyval.node) = NewASTNode(DeclaratorList);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1709 "lsc.tab.c"
    break;

  case 18:
#line 125 "lsc.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1717 "lsc.tab.c"
    break;

  case 19:
#line 127 "lsc.y"
                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 1726 "lsc.tab.c"
    break;

  case 20:
#line 133 "lsc.y"
                 {
        (yyval.node) = NewASTNode(Declarator);
        ASTNode* ts = NewASTNode(TypeSpecifier);
        ts->attr[0] = NULL;
        (yyval.node)->attr[0] = ts;
        (yyval.node)->attr[1] = (yyvsp[0].node);
        (yyval.node)->attr[2] = NULL;
    }
#line 1739 "lsc.tab.c"
    break;

  case 21:
#line 140 "lsc.y"
                                       {
        (yyval.node) = (yyvsp[-3].node);
        ASTNode* ts = (ASTNode*)((yyval.node)->attr[0]);
        if (ts->attr[0] == NULL) {
            ts->attr[0] = ConcatenateStr("[", (yyvsp[-1].str), "]", NULL);
            free((void*)(yyvsp[-1].str));
        } else {
            const char* t = (const char*)(ts->attr[0]);
            ts->attr[0] = ConcatenateStr(t, "[", (yyvsp[-1].str), "]", NULL);
            free((void*)t);
            free((void*)(yyvsp[-1].str));
        }
    }
#line 1757 "lsc.tab.c"
    break;

  case 22:
#line 155 "lsc.y"
                {
        (yyval.str) = CopyStr(yytext);
    }
#line 1765 "lsc.tab.c"
    break;

  case 23:
#line 160 "lsc.y"
                            {
        (yyval.node) = NewASTNode(Initializer);
        (yyval.node)->attr[0] = (yyvsp[0].node);
    }
#line 1774 "lsc.tab.c"
    break;

  case 24:
#line 163 "lsc.y"
                                {
        (yyval.node) = NewASTNode(ArrayInitializer);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
    }
#line 1783 "lsc.tab.c"
    break;

  case 25:
#line 166 "lsc.y"
                                      {
        (yyval.node) = NewASTNode(ArrayInitializer);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
    }
#line 1792 "lsc.tab.c"
    break;

  case 26:
#line 172 "lsc.y"
                  {
        (yyval.node) = NewASTNode(InitializerList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1802 "lsc.tab.c"
    break;

  case 27:
#line 176 "lsc.y"
                                          {
        (yyval.node) = NewASTNode(InitializerList);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1812 "lsc.tab.c"
    break;

  case 28:
#line 183 "lsc.y"
                      {
        (yyval.node) = NewASTNode(ParameterTypeList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1822 "lsc.tab.c"
    break;

  case 29:
#line 187 "lsc.y"
                                                 {
        (yyval.node) = NewASTNode(ParameterTypeList);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1832 "lsc.tab.c"
    break;

  case 30:
#line 194 "lsc.y"
                                                          {
        (yyval.node) = NewASTNode(FunctionDef);
        (yyval.node)->attr[0] = (yyvsp[-4].node);
        (yyval.node)->attr[1] = (yyvsp[-3].node);
        (yyval.node)->attr[2] = NULL;
        (yyval.node)->attr[3] = (yyvsp[0].node);
    }
#line 1844 "lsc.tab.c"
    break;

  case 31:
#line 200 "lsc.y"
                                                                                     {
        (yyval.node) = NewASTNode(FunctionDef);
        (yyval.node)->attr[0] = (yyvsp[-5].node);
        (yyval.node)->attr[1] = (yyvsp[-4].node);
        (yyval.node)->attr[2] = (yyvsp[-2].node);
        (yyval.node)->attr[3] = (yyvsp[0].node);
    }
#line 1856 "lsc.tab.c"
    break;

  case 32:
#line 209 "lsc.y"
                           {
        (yyval.node) = NewASTNode(ParameterDeclList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1866 "lsc.tab.c"
    break;

  case 33:
#line 213 "lsc.y"
                                                            {
        (yyval.node) = NewASTNode(ParameterDeclList);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1876 "lsc.tab.c"
    break;

  case 34:
#line 220 "lsc.y"
                                {
        (yyval.node) = NewASTNode(ParameterDecl);
        ASTNode* ts = (ASTNode*)((yyvsp[0].node)->attr[0]);
        const char* p = (const char*)(ts->attr[0]);
        if (p != NULL) {
            const char* t = (yyvsp[-1].node)->attr[0];
            (yyvsp[-1].node)->attr[0] = ConcatenateStr(t, p, NULL);
            free((void*)t);
            free((void*)p);
        }
        (yyval.node)->attr[0] = (yyvsp[-1].node);
        (yyval.node)->attr[1] = (yyvsp[0].node)->attr[1];
        free(ts);
        free((yyvsp[0].node));
    }
#line 1896 "lsc.tab.c"
    break;

  case 35:
#line 237 "lsc.y"
              {
        (yyval.node) = NewASTNode(CompoundStm);
        (yyval.node)->attr[0] = (yyval.node)->attr[1] = NULL;
    }
#line 1905 "lsc.tab.c"
    break;

  case 36:
#line 240 "lsc.y"
                              {
        (yyval.node) = NewASTNode(CompoundStm);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[-1].node);
    }
#line 1915 "lsc.tab.c"
    break;

  case 37:
#line 244 "lsc.y"
                                {
        (yyval.node) = NewASTNode(CompoundStm);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
        (yyval.node)->attr[1] = NULL;
    }
#line 1925 "lsc.tab.c"
    break;

  case 38:
#line 248 "lsc.y"
                                               {
        (yyval.node) = NewASTNode(CompoundStm);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[-1].node);
    }
#line 1935 "lsc.tab.c"
    break;

  case 39:
#line 255 "lsc.y"
                {
        (yyval.node) = NewASTNode(StatementList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1945 "lsc.tab.c"
    break;

  case 40:
#line 259 "lsc.y"
                                {
        (yyval.node) = NewASTNode(StatementList);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1955 "lsc.tab.c"
    break;

  case 41:
#line 266 "lsc.y"
                  {
        (yyval.node) = NewASTNode(DeclarationList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1965 "lsc.tab.c"
    break;

  case 42:
#line 270 "lsc.y"
                                    {
        (yyval.node) = NewASTNode(DeclarationList);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 1975 "lsc.tab.c"
    break;

  case 49:
#line 286 "lsc.y"
                {
        (yyval.node) = NewASTNode(ExpressionStm);
        (yyval.node)->attr[0] = NULL;
    }
#line 1984 "lsc.tab.c"
    break;

  case 50:
#line 289 "lsc.y"
                            {
        (yyval.node) = NewASTNode(ExpressionStm);
        (yyval.node)->attr[0] = (yyvsp[-1].node);
    }
#line 1993 "lsc.tab.c"
    break;

  case 51:
#line 295 "lsc.y"
                         {
        (yyval.node) = NewASTNode(JumpStm);
        (yyval.node)->attr[0] = "continue";
        (yyval.node)->attr[1] = NULL;
    }
#line 2003 "lsc.tab.c"
    break;

  case 52:
#line 299 "lsc.y"
                       {
        (yyval.node) = NewASTNode(JumpStm);
        (yyval.node)->attr[0] = "break";
        (yyval.node)->attr[1] = NULL;
    }
#line 2013 "lsc.tab.c"
    break;

  case 53:
#line 303 "lsc.y"
                        {
        (yyval.node) = NewASTNode(JumpStm);
        (yyval.node)->attr[0] = "return";
        (yyval.node)->attr[1] = NULL;
    }
#line 2023 "lsc.tab.c"
    break;

  case 54:
#line 307 "lsc.y"
                                   {
        (yyval.node) = NewASTNode(JumpStm);
        (yyval.node)->attr[0] = "return";
        (yyval.node)->attr[1] = (yyvsp[-1].node);
    }
#line 2033 "lsc.tab.c"
    break;

  case 55:
#line 314 "lsc.y"
                                             {
        (yyval.node) = NewASTNode(SelectionStm);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
        (yyval.node)->attr[2] = NULL;
    }
#line 2044 "lsc.tab.c"
    break;

  case 56:
#line 319 "lsc.y"
                                                                      {
        (yyval.node) = NewASTNode(SelectionStm);
        (yyval.node)->attr[0] = (yyvsp[-4].node);
        (yyval.node)->attr[1] = (yyvsp[-2].node);
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2055 "lsc.tab.c"
    break;

  case 57:
#line 324 "lsc.y"
                                                                       {
        (yyval.node) = NewASTNode(SelectionStm);
        (yyval.node)->attr[0] = (yyvsp[-4].node);
        (yyval.node)->attr[1] = (yyvsp[-2].node);
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2066 "lsc.tab.c"
    break;

  case 58:
#line 332 "lsc.y"
                                                                             {
        (yyval.node) = NewASTNode(LoopStm);
        (yyval.node)->attr[0] = (yyvsp[-3].node);
        (yyval.node)->attr[1] = (yyvsp[-2].node);
        (yyval.node)->attr[2] = NULL;
        (yyval.node)->attr[3] = (yyvsp[0].node);
    }
#line 2078 "lsc.tab.c"
    break;

  case 59:
#line 338 "lsc.y"
                                                                                         {
        (yyval.node) = NewASTNode(LoopStm);
        (yyval.node)->attr[0] = (yyvsp[-4].node);
        (yyval.node)->attr[1] = (yyvsp[-3].node);
        (yyval.node)->attr[2] = (yyvsp[-2].node);
        (yyval.node)->attr[3] = (yyvsp[0].node);
    }
#line 2090 "lsc.tab.c"
    break;

  case 60:
#line 347 "lsc.y"
                                          {
        (yyval.node) = NewASTNode(IOStm);
        (yyval.node)->attr[0] = "print";
        (yyval.node)->attr[1] = (yyvsp[-2].node);
    }
#line 2100 "lsc.tab.c"
    break;

  case 61:
#line 351 "lsc.y"
                                          {
        (yyval.node) = NewASTNode(IOStm);
        (yyval.node)->attr[0] = "scan";
        (yyval.node)->attr[1] = (yyvsp[-2].node);
    }
#line 2110 "lsc.tab.c"
    break;

  case 63:
#line 359 "lsc.y"
                                             {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = ",";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2121 "lsc.tab.c"
    break;

  case 65:
#line 368 "lsc.y"
                                                      {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "=";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2132 "lsc.tab.c"
    break;

  case 67:
#line 377 "lsc.y"
                           {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "++";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2142 "lsc.tab.c"
    break;

  case 68:
#line 381 "lsc.y"
                            {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "--";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2152 "lsc.tab.c"
    break;

  case 69:
#line 385 "lsc.y"
                             {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "+";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2162 "lsc.tab.c"
    break;

  case 70:
#line 389 "lsc.y"
                              {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "-";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2172 "lsc.tab.c"
    break;

  case 71:
#line 393 "lsc.y"
                             {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "~";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2182 "lsc.tab.c"
    break;

  case 72:
#line 397 "lsc.y"
                            {
        (yyval.node) = NewASTNode(UnaryExpr);
        (yyval.node)->attr[0] = "!";
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2192 "lsc.tab.c"
    break;

  case 74:
#line 405 "lsc.y"
                                            {
        (yyval.node) = NewASTNode(PostfixExpr);
        (yyval.node)->attr[0] = (yyvsp[-3].node);
        (yyval.node)->attr[1] = "[]";
        (yyval.node)->attr[2] = (yyvsp[-1].node);
    }
#line 2203 "lsc.tab.c"
    break;

  case 75:
#line 410 "lsc.y"
                                {
        (yyval.node) = NewASTNode(FunctionCall);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = NULL;
    }
#line 2213 "lsc.tab.c"
    break;

  case 76:
#line 414 "lsc.y"
                                              {
        (yyval.node) = NewASTNode(FunctionCall);
        (yyval.node)->attr[0] = (yyvsp[-3].node);
        (yyval.node)->attr[1] = (yyvsp[-1].node);
    }
#line 2223 "lsc.tab.c"
    break;

  case 77:
#line 421 "lsc.y"
                 {
        (yyval.node) = NewASTNode(Identifier);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 2232 "lsc.tab.c"
    break;

  case 78:
#line 424 "lsc.y"
                 {
        (yyval.node) = NewASTNode(BoolConst);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 2241 "lsc.tab.c"
    break;

  case 79:
#line 427 "lsc.y"
                 {
        (yyval.node) = NewASTNode(IntConst);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 2250 "lsc.tab.c"
    break;

  case 80:
#line 430 "lsc.y"
                 {
        (yyval.node) = NewASTNode(FloatConst);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 2259 "lsc.tab.c"
    break;

  case 81:
#line 433 "lsc.y"
                 {
        (yyval.node) = NewASTNode(StrConst);
        (yyval.node)->attr[0] = CopyStr(yytext);
    }
#line 2268 "lsc.tab.c"
    break;

  case 82:
#line 436 "lsc.y"
                        {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2276 "lsc.tab.c"
    break;

  case 83:
#line 441 "lsc.y"
                            {
        (yyval.node) = NewASTNode(ArguementList);
        (yyval.node)->attr[0] = NULL;
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2286 "lsc.tab.c"
    break;

  case 84:
#line 445 "lsc.y"
                                                 {
        (yyval.node) = NewASTNode(ArguementList);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = (yyvsp[0].node);
    }
#line 2296 "lsc.tab.c"
    break;

  case 86:
#line 453 "lsc.y"
                                                      {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "||";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2307 "lsc.tab.c"
    break;

  case 88:
#line 462 "lsc.y"
                                                       {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "&&";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2318 "lsc.tab.c"
    break;

  case 90:
#line 471 "lsc.y"
                                                       {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "|";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2329 "lsc.tab.c"
    break;

  case 92:
#line 480 "lsc.y"
                                                         {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "^";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2340 "lsc.tab.c"
    break;

  case 94:
#line 489 "lsc.y"
                                                      {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "&";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2351 "lsc.tab.c"
    break;

  case 96:
#line 498 "lsc.y"
                                                   {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "==";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2362 "lsc.tab.c"
    break;

  case 97:
#line 503 "lsc.y"
                                                    {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "!=";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2373 "lsc.tab.c"
    break;

  case 99:
#line 512 "lsc.y"
                                                {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "<";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2384 "lsc.tab.c"
    break;

  case 100:
#line 517 "lsc.y"
                                                 {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = ">";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2395 "lsc.tab.c"
    break;

  case 101:
#line 522 "lsc.y"
                                                 {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "<=";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2406 "lsc.tab.c"
    break;

  case 102:
#line 527 "lsc.y"
                                                 {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = ">=";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2417 "lsc.tab.c"
    break;

  case 104:
#line 536 "lsc.y"
                                              {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "<<";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2428 "lsc.tab.c"
    break;

  case 105:
#line 541 "lsc.y"
                                               {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = ">>";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2439 "lsc.tab.c"
    break;

  case 107:
#line 550 "lsc.y"
                                                         {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "+";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2450 "lsc.tab.c"
    break;

  case 108:
#line 555 "lsc.y"
                                                           {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "-";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2461 "lsc.tab.c"
    break;

  case 110:
#line 564 "lsc.y"
                                                     {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "*";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2472 "lsc.tab.c"
    break;

  case 111:
#line 569 "lsc.y"
                                                      {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "/";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2483 "lsc.tab.c"
    break;

  case 112:
#line 574 "lsc.y"
                                                      {
        (yyval.node) = NewASTNode(BinaryExpr);
        (yyval.node)->attr[0] = (yyvsp[-2].node);
        (yyval.node)->attr[1] = "%";
        (yyval.node)->attr[2] = (yyvsp[0].node);
    }
#line 2494 "lsc.tab.c"
    break;


#line 2498 "lsc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 580 "lsc.y"


extern int yylineno;
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}
