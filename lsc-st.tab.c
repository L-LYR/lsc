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
#line 7 "lsc-st.y"

    #include <stdio.h>
    #include "st.h"
    #include "panic.h"
    #include "text.h"
    void yyerror(const char *s);
    int yylex(void);
    int yylex_destroy(void);

    const char* yytext;
    ST t;
    Fmt fmt;

#line 81 "lsc-st.tab.c"




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

#line 131 "lsc-st.tab.c"

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

#line 200 "lsc-st.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LSC_ST_TAB_H_INCLUDED  */



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
#define YYLAST   486

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
       0,    54,    54,    57,    60,    66,    69,    75,    78,    84,
      90,    93,    96,    99,   102,   105,   111,   114,   120,   123,
     129,   132,   138,   144,   147,   150,   156,   159,   165,   168,
     174,   177,   183,   186,   192,   198,   201,   204,   207,   213,
     216,   222,   225,   231,   234,   237,   240,   243,   246,   252,
     255,   261,   264,   267,   270,   276,   279,   282,   288,   291,
     297,   300,   306,   308,   314,   316,   322,   324,   327,   330,
     333,   336,   339,   345,   347,   350,   353,   359,   362,   365,
     368,   371,   374,   380,   383,   389,   391,   397,   399,   405,
     407,   413,   415,   421,   423,   429,   431,   434,   440,   442,
     445,   448,   451,   457,   459,   462,   468,   470,   473,   479,
     481,   484,   487
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

#define YYPACT_NINF (-139)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      65,  -139,  -139,  -139,  -139,  -139,    11,    65,  -139,  -139,
      -9,  -139,  -139,  -139,  -139,     6,    18,   -16,  -139,     5,
    -139,   -21,    27,    28,  -139,   398,     6,  -139,    17,    -9,
      -7,    44,  -139,  -139,  -139,  -139,  -139,  -139,  -139,   181,
     181,   181,   181,   181,   181,   181,   398,  -139,  -139,  -139,
    -139,    10,    42,    49,    68,    59,    76,    82,    21,    53,
      86,   103,    51,    78,   168,  -139,    85,    65,    87,    65,
      17,  -139,    90,  -139,  -139,  -139,  -139,  -139,    57,  -139,
    -139,   -25,   181,   181,   409,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,  -139,   100,   102,   316,    98,    99,   106,
     108,  -139,  -139,  -139,    -9,  -139,   261,   217,  -139,  -139,
    -139,  -139,  -139,  -139,    -8,   107,  -139,    -9,  -139,  -139,
     181,  -139,   363,  -139,  -139,    33,  -139,  -139,    58,    68,
      59,    76,    82,    21,    53,    53,    86,    86,    86,    86,
     103,   103,    51,    51,  -139,  -139,  -139,   181,   352,  -139,
       3,  -139,  -139,   181,   181,   112,  -139,  -139,  -139,  -139,
     305,  -139,  -139,  -139,  -139,  -139,   181,  -139,    61,   352,
    -139,    67,    71,    65,  -139,  -139,    17,   440,   109,   110,
     107,   150,    17,    75,  -139,  -139,     1,  -139,    17,  -139,
    -139,  -139
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    10,    11,    12,    13,    14,     0,     2,     3,     5,
       0,     6,     1,     4,     9,     0,    20,     0,    16,    18,
      22,     0,     0,     0,     7,     0,     0,    15,     0,    28,
       0,     0,    32,    20,    17,    78,    79,    80,    81,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    19,    23,
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
    -139,  -139,  -139,   155,   -52,     0,   -18,  -139,   143,   -27,
     141,   -43,  -139,  -139,  -139,  -139,   126,   -28,    52,  -139,
    -109,  -138,  -139,   -19,  -139,  -139,   -39,   -20,   -26,   -24,
    -139,   -35,  -139,   111,   122,   123,   121,   125,    40,     2,
      39,    43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    47,    10,    17,    18,    19,
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
      65,    51,    66,    80,    29,    49,    78,   167,    14,   104,
      16,    12,   113,    71,    73,    74,    75,    76,    77,   132,
     179,    51,    51,    33,    20,   133,    49,    27,    23,    33,
       1,     2,     3,     4,     5,    24,   130,    67,    15,    68,
      51,   187,   129,   171,   135,    14,   114,   130,    25,   125,
      64,   127,    26,    82,   180,    90,    91,    83,    51,    51,
      51,   167,   134,    22,   137,   169,    64,   160,     1,     2,
       3,     4,     5,    28,   154,   155,   156,   130,   100,   101,
     102,   175,    51,    92,    93,    94,    95,    84,    69,   174,
      70,    85,    51,    51,   146,   147,   148,   149,    87,   114,
      66,   130,   176,   131,   177,   130,    51,   186,    51,    86,
     172,   176,    49,   188,   165,   176,    88,   189,   178,   130,
      89,   198,    96,    97,    98,    99,   103,    33,   181,   182,
     144,   145,    26,    51,    51,   150,   151,    83,   126,    51,
      51,   152,   153,   137,   137,   157,    51,   158,   193,   161,
     162,   163,    51,   164,    15,    51,   185,   183,   191,   196,
     194,   195,    13,    51,   197,   190,    34,    63,   199,   170,
     201,     1,     2,     3,     4,     5,   104,   200,   105,   106,
     107,   108,   109,   110,    35,    14,    36,    37,    38,    39,
      40,    41,    42,    43,    44,   128,   139,    35,    14,    36,
      37,    38,    39,    40,    41,    42,    43,    44,   140,   142,
     141,     0,     0,    45,   143,     0,     0,    64,   111,   112,
       1,     2,     3,     4,     5,   104,    45,   105,   106,   107,
     108,   109,   110,    35,    14,    36,    37,    38,    39,    40,
      41,    42,    43,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,    64,   168,   112,   104,
       0,   105,   106,   107,   108,   109,   110,    35,    14,    36,
      37,    38,    39,    40,    41,    42,    43,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,     0,     0,
      64,   166,   112,   104,     0,   105,   106,   107,   108,   109,
     110,    35,    14,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    35,    14,    36,    37,    38,    39,    40,    41,
      42,    43,    44,     0,     0,     0,     0,     0,     0,     0,
      45,     0,     0,     0,    64,   184,   112,     0,     0,     0,
       0,    45,     0,     0,     0,     0,     0,   159,    35,    14,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    35,
      14,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       0,     0,     0,     0,     0,     0,     0,    45,     0,     0,
       0,     0,     0,   112,     0,     0,     0,     0,    45,     0,
       0,     0,    46,   173,    35,    14,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    35,    14,    36,    37,    38,
      39,    40,    41,    42,    43,    44,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,    46,     0,     0,
       0,     0,     0,     0,    45,   136,    35,    14,    36,    37,
      38,    39,    40,    41,    42,    43,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,   192
};

static const yytype_int16 yycheck[] =
{
      28,    25,    29,    46,    22,    25,    45,   116,    17,     8,
      10,     0,    64,    39,    40,    41,    42,    43,    44,    44,
     158,    45,    46,    23,    18,    50,    46,    48,    44,    29,
       3,     4,     5,     6,     7,    51,    44,    44,    47,    46,
      64,   179,    70,    51,    83,    17,    64,    44,    43,    67,
      49,    69,    47,    43,    51,    34,    35,    47,    82,    83,
      84,   170,    82,    45,    84,   117,    49,   106,     3,     4,
       5,     6,     7,    46,   100,   101,   102,    44,    27,    28,
      29,    48,   106,    30,    31,    32,    33,    45,    44,   132,
      46,    42,   116,   117,    92,    93,    94,    95,    39,   117,
     127,    44,    44,    46,    46,    44,   130,    46,   132,    41,
     130,    44,   132,    46,   114,    44,    40,    46,   157,    44,
      38,    46,    36,    37,    21,    22,    48,   127,   163,   164,
      90,    91,    47,   157,   158,    96,    97,    47,    51,   163,
     164,    98,    99,   163,   164,    45,   170,    45,   187,    51,
      51,    45,   176,    45,    47,   179,   176,    45,   186,     9,
      51,    51,     7,   187,   192,   183,    23,    26,   196,   117,
     198,     3,     4,     5,     6,     7,     8,   196,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    69,    85,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    86,    88,
      87,    -1,    -1,    45,    89,    -1,    -1,    49,    50,    51,
       3,     4,     5,     6,     7,     8,    45,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    49,    50,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    53,    54,    55,    56,
      58,    66,     0,    55,    17,    47,    57,    59,    60,    61,
      18,    62,    45,    44,    51,    43,    47,    48,    46,    58,
      65,    67,    68,    57,    60,    16,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    45,    49,    57,    63,    79,
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
#line 54 "lsc-st.y"
                      {t.root = (yyval.node);}
#line 1589 "lsc-st.tab.c"
    break;

  case 3:
#line 57 "lsc-st.y"
                                       {
        (yyval.node) = NewSTNode(GLOBAL_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1598 "lsc-st.tab.c"
    break;

  case 4:
#line 60 "lsc-st.y"
                                                    {
        (yyval.node) = NewSTNode(GLOBAL_LIST, 2);
        AddAttrs((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1607 "lsc-st.tab.c"
    break;

  case 5:
#line 66 "lsc-st.y"
                  {
        (yyval.node) = NewSTNode(GLOBAL_DECLARATION_OR_DEFINITION, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1616 "lsc-st.tab.c"
    break;

  case 6:
#line 69 "lsc-st.y"
                           {
        (yyval.node) = NewSTNode(GLOBAL_DECLARATION_OR_DEFINITION, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1625 "lsc-st.tab.c"
    break;

  case 7:
#line 75 "lsc-st.y"
                                                     {
        (yyval.node) = NewSTNode(DECLARATION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), CopyStr("delimiter ;"));
    }
#line 1634 "lsc-st.tab.c"
    break;

  case 8:
#line 78 "lsc-st.y"
                                                                      {
        (yyval.node) = NewSTNode(DECLARATION, 6);
        AddAttrs((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), CopyStr("delimiter ("), (yyvsp[-2].node), CopyStr("delimiter )"), CopyStr("delimiter ;"));
    }
#line 1643 "lsc-st.tab.c"
    break;

  case 9:
#line 84 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(ID, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 1652 "lsc-st.tab.c"
    break;

  case 10:
#line 90 "lsc-st.y"
           {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), CopyStr("void"));
    }
#line 1661 "lsc-st.tab.c"
    break;

  case 11:
#line 93 "lsc-st.y"
           {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), CopyStr("i32"));
    }
#line 1670 "lsc-st.tab.c"
    break;

  case 12:
#line 96 "lsc-st.y"
           {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), CopyStr("f32"));
    }
#line 1679 "lsc-st.tab.c"
    break;

  case 13:
#line 99 "lsc-st.y"
              {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), CopyStr("string"));
    }
#line 1688 "lsc-st.tab.c"
    break;

  case 14:
#line 102 "lsc-st.y"
            {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), CopyStr("bool"));
    }
#line 1697 "lsc-st.tab.c"
    break;

  case 15:
#line 105 "lsc-st.y"
                                            {
        (yyval.node) = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs((yyval.node), (yyvsp[-3].node), CopyStr("delimiter ["), (yyvsp[-1].node), CopyStr("delimiter ]"));
    }
#line 1706 "lsc-st.tab.c"
    break;

  case 16:
#line 111 "lsc-st.y"
                      {
        (yyval.node) = NewSTNode(INIT_DECLARATOR_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1715 "lsc-st.tab.c"
    break;

  case 17:
#line 114 "lsc-st.y"
                                                  {
        (yyval.node) = NewSTNode(INIT_DECLARATOR_LIST, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ,"), (yyvsp[0].node));
    }
#line 1724 "lsc-st.tab.c"
    break;

  case 18:
#line 120 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(INIT_DECLARATOR, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1733 "lsc-st.tab.c"
    break;

  case 19:
#line 123 "lsc-st.y"
                                     {
        (yyval.node) = NewSTNode(INIT_DECLARATOR, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator ="), (yyvsp[0].node));
    }
#line 1742 "lsc-st.tab.c"
    break;

  case 20:
#line 129 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(DECLARATOR, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1751 "lsc-st.tab.c"
    break;

  case 21:
#line 132 "lsc-st.y"
                                       {
        (yyval.node) = NewSTNode(DECLARATOR, 4);
        AddAttrs((yyval.node), (yyvsp[-3].node), CopyStr("delimiter ["), (yyvsp[-1].node), CopyStr("delimiter ]"));
    }
#line 1760 "lsc-st.tab.c"
    break;

  case 22:
#line 138 "lsc-st.y"
                {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 1769 "lsc-st.tab.c"
    break;

  case 23:
#line 144 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(INITIALIZER, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1778 "lsc-st.tab.c"
    break;

  case 24:
#line 147 "lsc-st.y"
                                {
        (yyval.node) = NewSTNode(INITIALIZER, 3);
        AddAttrs((yyval.node), CopyStr("delimiter ["), (yyvsp[-1].node), CopyStr("delimiter ]"));
    }
#line 1787 "lsc-st.tab.c"
    break;

  case 25:
#line 150 "lsc-st.y"
                                      {
        (yyval.node) = NewSTNode(INITIALIZER, 4);
        AddAttrs((yyval.node), CopyStr("delimiter ["), (yyvsp[-2].node), CopyStr("delimiter ,"), CopyStr("delimiter delimiter ]"));
    }
#line 1796 "lsc-st.tab.c"
    break;

  case 26:
#line 156 "lsc-st.y"
                  {
        (yyval.node) = NewSTNode(INITIALIZER_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1805 "lsc-st.tab.c"
    break;

  case 27:
#line 159 "lsc-st.y"
                                          {
        (yyval.node) = NewSTNode(INITIALIZER_LIST, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ,"), (yyvsp[0].node));
    }
#line 1814 "lsc-st.tab.c"
    break;

  case 28:
#line 165 "lsc-st.y"
                      {
        (yyval.node) = NewSTNode(PARAMETER_TYPE_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1823 "lsc-st.tab.c"
    break;

  case 29:
#line 168 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(PARAMETER_TYPE_LIST, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ,"), (yyvsp[0].node));
    }
#line 1832 "lsc-st.tab.c"
    break;

  case 30:
#line 174 "lsc-st.y"
                                                          {
        (yyval.node) = NewSTNode(FUNCTION_DEFINITION, 5);
        AddAttrs((yyval.node), (yyvsp[-4].node), (yyvsp[-3].node), CopyStr("delimiter ("), CopyStr("delimiter )"), (yyvsp[0].node));
    }
#line 1841 "lsc-st.tab.c"
    break;

  case 31:
#line 177 "lsc-st.y"
                                                                                     {
        (yyval.node) = NewSTNode(FUNCTION_DEFINITION, 6);
        AddAttrs((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), CopyStr("delimiter ("), (yyvsp[-2].node), CopyStr("delimiter )"), (yyvsp[0].node));
    }
#line 1850 "lsc-st.tab.c"
    break;

  case 32:
#line 183 "lsc-st.y"
                           {
        (yyval.node) = NewSTNode(PARAMETER_DECLARATOR_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1859 "lsc-st.tab.c"
    break;

  case 33:
#line 186 "lsc-st.y"
                                                            {
        (yyval.node) = NewSTNode(PARAMETER_DECLARATOR_LIST, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ,"), (yyvsp[0].node));
    }
#line 1868 "lsc-st.tab.c"
    break;

  case 34:
#line 192 "lsc-st.y"
                                {
        (yyval.node) = NewSTNode(PARAMETER_DECLARATOR, 2);
        AddAttrs((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1877 "lsc-st.tab.c"
    break;

  case 35:
#line 198 "lsc-st.y"
              {
        (yyval.node) = NewSTNode(COMPOUND_STATEMENT, 2);
        AddAttrs((yyval.node), CopyStr("delimiter {"), CopyStr("delimiter }"));
    }
#line 1886 "lsc-st.tab.c"
    break;

  case 36:
#line 201 "lsc-st.y"
                              {
        (yyval.node) = NewSTNode(COMPOUND_STATEMENT, 3);
        AddAttrs((yyval.node), CopyStr("delimiter {"), (yyvsp[-1].node), CopyStr("delimiter }"));
    }
#line 1895 "lsc-st.tab.c"
    break;

  case 37:
#line 204 "lsc-st.y"
                                {
        (yyval.node) = NewSTNode(COMPOUND_STATEMENT, 3);
        AddAttrs((yyval.node), CopyStr("delimiter {"), (yyvsp[-1].node), CopyStr("delimiter }"));
    }
#line 1904 "lsc-st.tab.c"
    break;

  case 38:
#line 207 "lsc-st.y"
                                               {
        (yyval.node) = NewSTNode(COMPOUND_STATEMENT, 4);
        AddAttrs((yyval.node), CopyStr("delimiter {"), (yyvsp[-2].node), (yyvsp[-1].node), CopyStr("delimiter }"));
    }
#line 1913 "lsc-st.tab.c"
    break;

  case 39:
#line 213 "lsc-st.y"
                {
        (yyval.node) = NewSTNode(STATEMENT_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1922 "lsc-st.tab.c"
    break;

  case 40:
#line 216 "lsc-st.y"
                                {
        (yyval.node) = NewSTNode(STATEMENT_LIST, 2);
        AddAttrs((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1931 "lsc-st.tab.c"
    break;

  case 41:
#line 222 "lsc-st.y"
                  {
        (yyval.node) = NewSTNode(DECLARATION_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1940 "lsc-st.tab.c"
    break;

  case 42:
#line 225 "lsc-st.y"
                                    {
        (yyval.node) = NewSTNode(DECLARATION_LIST, 2);
        AddAttrs((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1949 "lsc-st.tab.c"
    break;

  case 43:
#line 231 "lsc-st.y"
                         {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1958 "lsc-st.tab.c"
    break;

  case 44:
#line 234 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1967 "lsc-st.tab.c"
    break;

  case 45:
#line 237 "lsc-st.y"
                      {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1976 "lsc-st.tab.c"
    break;

  case 46:
#line 240 "lsc-st.y"
                           {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1985 "lsc-st.tab.c"
    break;

  case 47:
#line 243 "lsc-st.y"
                      {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 1994 "lsc-st.tab.c"
    break;

  case 48:
#line 246 "lsc-st.y"
                    {
        (yyval.node) = NewSTNode(STATEMENT, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 2003 "lsc-st.tab.c"
    break;

  case 49:
#line 252 "lsc-st.y"
                {
        (yyval.node) = NewSTNode(EXPRESSION_STATEMENT, 1);
        AddAttrs((yyval.node), CopyStr("delimiter ;"));
    }
#line 2012 "lsc-st.tab.c"
    break;

  case 50:
#line 255 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(EXPRESSION_STATEMENT, 2);
        AddAttrs((yyval.node), (yyvsp[-1].node), CopyStr("delimiter ;"));
    }
#line 2021 "lsc-st.tab.c"
    break;

  case 51:
#line 261 "lsc-st.y"
                         {
        (yyval.node) = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs((yyval.node), CopyStr("continue"), CopyStr("delimiter ;"));
    }
#line 2030 "lsc-st.tab.c"
    break;

  case 52:
#line 264 "lsc-st.y"
                       {
        (yyval.node) = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs((yyval.node), CopyStr("break"), CopyStr("delimiter ;"));
    }
#line 2039 "lsc-st.tab.c"
    break;

  case 53:
#line 267 "lsc-st.y"
                        {
        (yyval.node) = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs((yyval.node), CopyStr("return"), CopyStr("delimiter ;"));
    }
#line 2048 "lsc-st.tab.c"
    break;

  case 54:
#line 270 "lsc-st.y"
                                   {
        (yyval.node) = NewSTNode(JUMP_STATEMENT, 3);
        AddAttrs((yyval.node), CopyStr("return"), (yyvsp[-1].node), CopyStr("delimiter ;"));
    }
#line 2057 "lsc-st.tab.c"
    break;

  case 55:
#line 276 "lsc-st.y"
                                             {
        (yyval.node) = NewSTNode(SELECTION_STATEMENT, 5);
        AddAttrs((yyval.node), CopyStr("if"), CopyStr("delimiter ("), (yyvsp[-2].node), CopyStr("delimiter )"), (yyvsp[0].node));
    }
#line 2066 "lsc-st.tab.c"
    break;

  case 56:
#line 279 "lsc-st.y"
                                                                      {
        (yyval.node) = NewSTNode(SELECTION_STATEMENT, 7);
        AddAttrs((yyval.node), CopyStr("if"), CopyStr("delimiter ("), (yyvsp[-4].node), CopyStr("delimiter )"), (yyvsp[-2].node), CopyStr("else"), (yyvsp[0].node));
    }
#line 2075 "lsc-st.tab.c"
    break;

  case 57:
#line 282 "lsc-st.y"
                                                                       {
        (yyval.node) = NewSTNode(SELECTION_STATEMENT, 7);
        AddAttrs((yyval.node), CopyStr("if"), CopyStr("delimiter ("), (yyvsp[-4].node), CopyStr("delimiter )"), (yyvsp[-2].node), CopyStr("else"), (yyvsp[0].node));
    }
#line 2084 "lsc-st.tab.c"
    break;

  case 58:
#line 288 "lsc-st.y"
                                                                             {
        (yyval.node) = NewSTNode(LOOP_STATEMENT, 6);
        AddAttrs((yyval.node), CopyStr("for"), CopyStr("delimiter ("), (yyvsp[-3].node), (yyvsp[-2].node), CopyStr("delimiter )"), (yyvsp[0].node));
    }
#line 2093 "lsc-st.tab.c"
    break;

  case 59:
#line 291 "lsc-st.y"
                                                                                         {
        (yyval.node) = NewSTNode(LOOP_STATEMENT, 7);
        AddAttrs((yyval.node), CopyStr("for"), CopyStr("delimiter ("), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), CopyStr("delimiter )"), (yyvsp[0].node));
    }
#line 2102 "lsc-st.tab.c"
    break;

  case 60:
#line 297 "lsc-st.y"
                                          {
        (yyval.node) = NewSTNode(IO_STATEMENT, 5);
        AddAttrs((yyval.node), CopyStr("print"), CopyStr("delimiter ("), (yyvsp[-2].node), CopyStr("delimiter )"), CopyStr("delimiter ;"));
    }
#line 2111 "lsc-st.tab.c"
    break;

  case 61:
#line 300 "lsc-st.y"
                                          {
        (yyval.node) = NewSTNode(IO_STATEMENT, 5);
        AddAttrs((yyval.node), CopyStr("scan"), CopyStr("delimiter ("), (yyvsp[-2].node), CopyStr("delimiter )"), CopyStr("delimiter ;"));
    }
#line 2120 "lsc-st.tab.c"
    break;

  case 62:
#line 306 "lsc-st.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2128 "lsc-st.tab.c"
    break;

  case 63:
#line 308 "lsc-st.y"
                                              {
        (yyval.node) = NewSTNode(EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator ,"), (yyvsp[0].node));
    }
#line 2137 "lsc-st.tab.c"
    break;

  case 64:
#line 314 "lsc-st.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2145 "lsc-st.tab.c"
    break;

  case 65:
#line 316 "lsc-st.y"
                                                       {
        (yyval.node) = NewSTNode(ASSIGNMENT_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator ="), (yyvsp[0].node));
    }
#line 2154 "lsc-st.tab.c"
    break;

  case 66:
#line 322 "lsc-st.y"
                         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2162 "lsc-st.tab.c"
    break;

  case 67:
#line 324 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator ++"), (yyvsp[0].node));
    }
#line 2171 "lsc-st.tab.c"
    break;

  case 68:
#line 327 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator --"), (yyvsp[0].node));
    }
#line 2180 "lsc-st.tab.c"
    break;

  case 69:
#line 330 "lsc-st.y"
                             {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator +"), (yyvsp[0].node));
    }
#line 2189 "lsc-st.tab.c"
    break;

  case 70:
#line 333 "lsc-st.y"
                              {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator -"), (yyvsp[0].node));
    }
#line 2198 "lsc-st.tab.c"
    break;

  case 71:
#line 336 "lsc-st.y"
                             {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator ~"), (yyvsp[0].node));
    }
#line 2207 "lsc-st.tab.c"
    break;

  case 72:
#line 339 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs((yyval.node), CopyStr("operator !"), (yyvsp[0].node));
    }
#line 2216 "lsc-st.tab.c"
    break;

  case 73:
#line 345 "lsc-st.y"
                         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2224 "lsc-st.tab.c"
    break;

  case 74:
#line 347 "lsc-st.y"
                                             {
        (yyval.node) = NewSTNode(POSTFIX_EXPRESSION, 4);
        AddAttrs((yyval.node), (yyvsp[-3].node), CopyStr("delimiter ["), (yyvsp[-1].node), CopyStr("delimiter ]"));
    }
#line 2233 "lsc-st.tab.c"
    break;

  case 75:
#line 350 "lsc-st.y"
                                {
        (yyval.node) = NewSTNode(POSTFIX_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ("), CopyStr("delimiter )"));
    }
#line 2242 "lsc-st.tab.c"
    break;

  case 76:
#line 353 "lsc-st.y"
                                              {
        (yyval.node) = NewSTNode(POSTFIX_EXPRESSION, 4);
        AddAttrs((yyval.node), (yyvsp[-3].node), CopyStr("delimiter ("), (yyvsp[-1].node), CopyStr("delimiter )"));
    }
#line 2251 "lsc-st.tab.c"
    break;

  case 77:
#line 359 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 2260 "lsc-st.tab.c"
    break;

  case 78:
#line 362 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 2269 "lsc-st.tab.c"
    break;

  case 79:
#line 365 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 2278 "lsc-st.tab.c"
    break;

  case 80:
#line 368 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 2287 "lsc-st.tab.c"
    break;

  case 81:
#line 371 "lsc-st.y"
                 {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs((yyval.node), CopyStr(yytext));
    }
#line 2296 "lsc-st.tab.c"
    break;

  case 82:
#line 374 "lsc-st.y"
                        {
        (yyval.node) = NewSTNode(PRIMARY_EXPRESSION, 3);
        AddAttrs((yyval.node), CopyStr("delimiter ("), (yyvsp[-1].node), CopyStr("delimiter )"));
    }
#line 2305 "lsc-st.tab.c"
    break;

  case 83:
#line 380 "lsc-st.y"
                            {
        (yyval.node) = NewSTNode(ARGUMENT_LIST, 1);
        AddAttrs((yyval.node), (yyvsp[0].node));
    }
#line 2314 "lsc-st.tab.c"
    break;

  case 84:
#line 383 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(ARGUMENT_LIST, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("delimiter ,"), (yyvsp[0].node));
    }
#line 2323 "lsc-st.tab.c"
    break;

  case 85:
#line 389 "lsc-st.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2331 "lsc-st.tab.c"
    break;

  case 86:
#line 391 "lsc-st.y"
                                                       {
        (yyval.node) = NewSTNode(LOGICAL_OR_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator ||"), (yyvsp[0].node));
    }
#line 2340 "lsc-st.tab.c"
    break;

  case 87:
#line 397 "lsc-st.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2348 "lsc-st.tab.c"
    break;

  case 88:
#line 399 "lsc-st.y"
                                                        {
        (yyval.node) = NewSTNode(LOGICAL_AND_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator &&"), (yyvsp[0].node));
    }
#line 2357 "lsc-st.tab.c"
    break;

  case 89:
#line 405 "lsc-st.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2365 "lsc-st.tab.c"
    break;

  case 90:
#line 407 "lsc-st.y"
                                                        {
        (yyval.node) = NewSTNode(BITWISE_OR_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator |"), (yyvsp[0].node));
    }
#line 2374 "lsc-st.tab.c"
    break;

  case 91:
#line 413 "lsc-st.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2382 "lsc-st.tab.c"
    break;

  case 92:
#line 415 "lsc-st.y"
                                                          {
        (yyval.node) = NewSTNode(BITWISE_XOR_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator ^"), (yyvsp[0].node));
    }
#line 2391 "lsc-st.tab.c"
    break;

  case 93:
#line 421 "lsc-st.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2399 "lsc-st.tab.c"
    break;

  case 94:
#line 423 "lsc-st.y"
                                                       {
        (yyval.node) = NewSTNode(BITWISE_AND_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator &"), (yyvsp[0].node));
    }
#line 2408 "lsc-st.tab.c"
    break;

  case 95:
#line 429 "lsc-st.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2416 "lsc-st.tab.c"
    break;

  case 96:
#line 431 "lsc-st.y"
                                                    {
        (yyval.node) = NewSTNode(EQUALITY_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator =="), (yyvsp[0].node));
    }
#line 2425 "lsc-st.tab.c"
    break;

  case 97:
#line 434 "lsc-st.y"
                                                    {
        (yyval.node) = NewSTNode(EQUALITY_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator !="), (yyvsp[0].node));
    }
#line 2434 "lsc-st.tab.c"
    break;

  case 98:
#line 440 "lsc-st.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2442 "lsc-st.tab.c"
    break;

  case 99:
#line 442 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator <"), (yyvsp[0].node));
    }
#line 2451 "lsc-st.tab.c"
    break;

  case 100:
#line 445 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator >"), (yyvsp[0].node));
    }
#line 2460 "lsc-st.tab.c"
    break;

  case 101:
#line 448 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator <="), (yyvsp[0].node));
    }
#line 2469 "lsc-st.tab.c"
    break;

  case 102:
#line 451 "lsc-st.y"
                                                 {
        (yyval.node) = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator >="), (yyvsp[0].node));
    }
#line 2478 "lsc-st.tab.c"
    break;

  case 103:
#line 457 "lsc-st.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2486 "lsc-st.tab.c"
    break;

  case 104:
#line 459 "lsc-st.y"
                                               {
        (yyval.node) = NewSTNode(SHIFT_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator <<"), (yyvsp[0].node)); 
    }
#line 2495 "lsc-st.tab.c"
    break;

  case 105:
#line 462 "lsc-st.y"
                                               {
        (yyval.node) = NewSTNode(SHIFT_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator >>"), (yyvsp[0].node));
    }
#line 2504 "lsc-st.tab.c"
    break;

  case 106:
#line 468 "lsc-st.y"
                                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2512 "lsc-st.tab.c"
    break;

  case 107:
#line 470 "lsc-st.y"
                                                          {
        (yyval.node) = NewSTNode(ADDITIVE_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator +"), (yyvsp[0].node));
    }
#line 2521 "lsc-st.tab.c"
    break;

  case 108:
#line 473 "lsc-st.y"
                                                           {
        (yyval.node) = NewSTNode(ADDITIVE_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator -"), (yyvsp[0].node));
    }
#line 2530 "lsc-st.tab.c"
    break;

  case 109:
#line 479 "lsc-st.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2538 "lsc-st.tab.c"
    break;

  case 110:
#line 481 "lsc-st.y"
                                                      {
        (yyval.node) = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator *"), (yyvsp[0].node));
    }
#line 2547 "lsc-st.tab.c"
    break;

  case 111:
#line 484 "lsc-st.y"
                                                      {
        (yyval.node) = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator /"), (yyvsp[0].node));
    }
#line 2556 "lsc-st.tab.c"
    break;

  case 112:
#line 487 "lsc-st.y"
                                                      {
        (yyval.node) = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs((yyval.node), (yyvsp[-2].node), CopyStr("operator %"), (yyvsp[0].node));
    }
#line 2565 "lsc-st.tab.c"
    break;


#line 2569 "lsc-st.tab.c"

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
#line 491 "lsc-st.y"


extern int yylineno;
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}