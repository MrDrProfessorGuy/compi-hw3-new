/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"


/* Declarations section */


#include <cstdlib>
#include "hw3_output.hpp"

#define YYDEBUG 1 


extern int yylex(); 
int yyerror(const char * message);

#define NewNode(attr, children) $$ = createNode(); $$->setAttributes(attr); $$->setChildren(children);
#define Cast(obj, Type) (std::static_pointer_cast<TYPE>(obj))



#line 91 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_BYTE = 8,                       /* BYTE  */
  YYSYMBOL_B = 9,                          /* B  */
  YYSYMBOL_BOOL = 10,                      /* BOOL  */
  YYSYMBOL_TRUE = 11,                      /* TRUE  */
  YYSYMBOL_FALSE = 12,                     /* FALSE  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_SC = 17,                        /* SC  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_LPAREN = 19,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 20,                    /* RPAREN  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_EQUALITY = 26,                  /* EQUALITY  */
  YYSYMBOL_RELOP = 27,                     /* RELOP  */
  YYSYMBOL_BINOP_ADD = 28,                 /* BINOP_ADD  */
  YYSYMBOL_BINOP_MUL = 29,                 /* BINOP_MUL  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_LBRACE = 31,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 32,                    /* RBRACE  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_Program = 34,                   /* Program  */
  YYSYMBOL_Funcs = 35,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 36,                  /* FuncDecl  */
  YYSYMBOL_RetType = 37,                   /* RetType  */
  YYSYMBOL_Formals = 38,                   /* Formals  */
  YYSYMBOL_FormalsList = 39,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 40,                /* FormalDecl  */
  YYSYMBOL_Statements = 41,                /* Statements  */
  YYSYMBOL_Statement = 42,                 /* Statement  */
  YYSYMBOL_Call = 43,                      /* Call  */
  YYSYMBOL_ExpList = 44,                   /* ExpList  */
  YYSYMBOL_Type = 45,                      /* Type  */
  YYSYMBOL_Exp = 46                        /* Exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    97,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM", "STRING",
  "VOID", "INT", "BYTE", "B", "BOOL", "TRUE", "FALSE", "RETURN", "WHILE",
  "BREAK", "CONTINUE", "SC", "COMMA", "LPAREN", "RPAREN", "ASSIGN", "IF",
  "ELSE", "OR", "AND", "EQUALITY", "RELOP", "BINOP_ADD", "BINOP_MUL",
  "NOT", "LBRACE", "RBRACE", "$accept", "Program", "Funcs", "FuncDecl",
  "RetType", "Formals", "FormalsList", "FormalDecl", "Statements",
  "Statement", "Call", "ExpList", "Type", "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   -29,   -29,   -29,   -29,    10,   -29,     7,    13,   -29,
     -29,   -29,    12,    47,    15,   -29,    20,    59,    32,    47,
     -29,   111,   -29,    50,   126,    56,    65,    66,    69,   111,
      71,   -29,    72,    87,   143,    61,    73,    86,   -29,   -29,
     -29,   -29,    29,    61,   -29,   142,    61,   -29,   -29,    61,
      91,   -29,   -29,   -29,     4,   -29,    76,   180,   155,   -29,
      77,   190,   -29,   -29,    81,    61,    61,    61,    61,    61,
      61,   200,   210,   -29,   -29,    61,   -29,    61,   -29,    61,
     -29,    61,   -22,    82,    22,    -1,    83,   -29,   111,   111,
     168,   -29,   228,   220,   -29,    92,   -29,    93,   111,    61,
     -29,   234
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     7,    31,    32,    33,     0,     2,     3,     0,     6,
       1,     4,     0,     8,     0,     9,    10,     0,     0,     0,
      12,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,    38,    40,    42,    43,
      44,    20,     0,     0,    39,     0,     0,    25,    26,     0,
       0,     5,    14,    19,     0,    28,     0,    29,     0,    41,
       0,     0,    45,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,     0,    27,     0,    18,     0,
      34,     0,    47,    46,    49,    48,    36,    37,     0,     0,
       0,    30,    50,     0,    24,    22,    17,     0,     0,     0,
      23,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   110,   -29,   -29,   -29,   101,   -29,    99,   -28,
     -21,    55,    11,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    14,    15,    16,    30,    31,
      44,    56,    33,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    45,    52,    66,    67,    68,    69,    70,    32,    32,
      10,     9,    58,     1,     2,     3,    12,     4,     9,    61,
      62,    74,    52,    71,    17,    75,    72,    69,    70,    32,
      17,    13,    36,    37,    38,    18,     2,     3,    19,     4,
      39,    40,    82,    83,    84,    85,    86,    87,    42,    68,
      69,    70,    90,    60,     2,     3,    92,     4,    93,    43,
      94,    95,    20,    21,    36,    37,    38,    32,    32,    34,
     100,    35,    39,    40,    23,    46,   101,    32,     2,     3,
      42,     4,    47,    48,    24,    25,    26,    27,    49,    53,
      54,    43,    34,    28,    23,    59,    76,    79,     2,     3,
      81,     4,    29,    51,    24,    25,    26,    27,    67,    68,
      69,    70,    70,    28,    23,    98,    99,    11,     2,     3,
      22,     4,    29,    73,    24,    25,    26,    27,    50,    36,
      37,    38,    91,    28,     0,     0,     0,    39,    40,     0,
       0,     0,    29,    41,     0,    42,    36,    37,    38,     0,
       0,     0,     0,     0,    39,    40,    43,     0,     0,    63,
       0,     0,    42,    55,    64,     0,    65,    66,    67,    68,
      69,    70,    78,    43,     0,     0,     0,    64,     0,    65,
      66,    67,    68,    69,    70,    96,     0,     0,     0,     0,
      64,     0,    65,    66,    67,    68,    69,    70,    77,     0,
       0,     0,    64,     0,    65,    66,    67,    68,    69,    70,
      80,     0,    64,     0,    65,    66,    67,    68,    69,    70,
      88,     0,    64,     0,    65,    66,    67,    68,    69,    70,
      89,     0,    64,     0,    65,    66,    67,    68,    69,    70,
      97,     0,    64,     0,    65,    66,    67,    68,    69,    70,
      64,     0,    65,    66,    67,    68,    69,    70,    65,    66,
      67,    68,    69,    70
};

static const yytype_int8 yycheck[] =
{
      21,    24,    30,    25,    26,    27,    28,    29,    29,    30,
       0,     0,    35,     6,     7,     8,     3,    10,     7,    42,
      43,    17,    50,    46,    13,    21,    49,    28,    29,    50,
      19,    19,     3,     4,     5,    20,     7,     8,    18,    10,
      11,    12,    65,    66,    67,    68,    69,    70,    19,    27,
      28,    29,    75,    42,     7,     8,    79,    10,    81,    30,
      88,    89,     3,    31,     3,     4,     5,    88,    89,    19,
      98,    21,    11,    12,     3,    19,    99,    98,     7,     8,
      19,    10,    17,    17,    13,    14,    15,    16,    19,    17,
       3,    30,    19,    22,     3,     9,    20,    20,     7,     8,
      19,    10,    31,    32,    13,    14,    15,    16,    26,    27,
      28,    29,    29,    22,     3,    23,    23,     7,     7,     8,
      19,    10,    31,    32,    13,    14,    15,    16,    29,     3,
       4,     5,    77,    22,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    31,    17,    -1,    19,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    11,    12,    30,    -1,    -1,    17,
      -1,    -1,    19,    20,    22,    -1,    24,    25,    26,    27,
      28,    29,    17,    30,    -1,    -1,    -1,    22,    -1,    24,
      25,    26,    27,    28,    29,    17,    -1,    -1,    -1,    -1,
      22,    -1,    24,    25,    26,    27,    28,    29,    18,    -1,
      -1,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      22,    -1,    24,    25,    26,    27,    28,    29,    24,    25,
      26,    27,    28,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,    10,    34,    35,    36,    37,    45,
       0,    35,     3,    19,    38,    39,    40,    45,    20,    18,
       3,    31,    39,     3,    13,    14,    15,    16,    22,    31,
      41,    42,    43,    45,    19,    21,     3,     4,     5,    11,
      12,    17,    19,    30,    43,    46,    19,    17,    17,    19,
      41,    32,    42,    17,     3,    20,    44,    46,    46,     9,
      45,    46,    46,    17,    22,    24,    25,    26,    27,    28,
      29,    46,    46,    32,    17,    21,    20,    18,    17,    20,
      20,    19,    46,    46,    46,    46,    46,    46,    20,    20,
      46,    44,    46,    46,    42,    42,    17,    20,    23,    23,
      42,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    37,    37,    38,    38,
      39,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    43,    43,    44,
      44,    45,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     8,     1,     1,     0,     1,
       1,     3,     2,     1,     2,     3,     3,     5,     4,     2,
       2,     3,     5,     7,     5,     2,     2,     4,     3,     1,
       3,     1,     1,     1,     3,     7,     3,     3,     1,     1,
       1,     2,     1,     1,     1,     2,     3,     3,     3,     3,
       4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* Program: Funcs  */
#line 97 "parser.ypp"
                                                                                {output::printProductionRule(1);}
#line 1217 "parser.tab.cpp"
    break;

  case 3: /* Funcs: %empty  */
#line 98 "parser.ypp"
                                                                                       {output::printProductionRule(2);}
#line 1223 "parser.tab.cpp"
    break;

  case 4: /* Funcs: FuncDecl Funcs  */
#line 99 "parser.ypp"
                                                                                {output::printProductionRule(3);}
#line 1229 "parser.tab.cpp"
    break;

  case 5: /* FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE  */
#line 100 "parser.ypp"
                                                                                {(yyval.NodeFuncDecl) = new Node_FuncDecl((yyvsp[-7].NodeRetType),(yyvsp[-6].NodeToken),(yyvsp[-5].NodeToken),(yyvsp[-4].NodeFormals),(yyvsp[-3].NodeToken),(yyvsp[-2].NodeToken),(yyvsp[-1].NodeStatement),(yyvsp[0].NodeToken));output::printProductionRule(4);}
#line 1235 "parser.tab.cpp"
    break;

  case 6: /* RetType: Type  */
#line 101 "parser.ypp"
                                                                                {(yyval.NodeRetType) = new Node_RetType({(yyvsp[0].NodeExp)}, ((yyvsp[0].NodeExp))->type);output::printProductionRule(5);}
#line 1241 "parser.tab.cpp"
    break;

  case 7: /* RetType: VOID  */
#line 102 "parser.ypp"
                                                                                {(yyval.NodeRetType) = new Node_RetType({(yyvsp[0].NodeToken)}, Type::VOID);output::printProductionRule(6);}
#line 1247 "parser.tab.cpp"
    break;

  case 8: /* Formals: %empty  */
#line 103 "parser.ypp"
                                                                                       {(yyval.NodeFormals) = new Node_Formals();output::printProductionRule(7);}
#line 1253 "parser.tab.cpp"
    break;

  case 9: /* Formals: FormalsList  */
#line 104 "parser.ypp"
                                                                                {(yyval.NodeFormals) = new Node_Formals((yyvsp[0].NodeFormalsList));output::printProductionRule(8);}
#line 1259 "parser.tab.cpp"
    break;

  case 10: /* FormalsList: FormalDecl  */
#line 105 "parser.ypp"
                                                                                {(yyval.NodeFormalsList) = new Node_FormalsList((yyvsp[0].NodeFormalDecl));output::printProductionRule(9);}
#line 1265 "parser.tab.cpp"
    break;

  case 11: /* FormalsList: FormalDecl COMMA FormalsList  */
#line 106 "parser.ypp"
                                                                                {(yyval.NodeFormalsList) = new Node_FormalsList((yyvsp[-2].NodeFormalDecl), (yyvsp[-1].NodeToken), (yyvsp[0].NodeFormalsList));output::printProductionRule(10);}
#line 1271 "parser.tab.cpp"
    break;

  case 12: /* FormalDecl: Type ID  */
#line 107 "parser.ypp"
                                                                                {(yyval.NodeFormalDecl) = new Node_FormalDecl((yyvsp[-1].NodeExp), (yyvsp[0].NodeToken));output::printProductionRule(11);}
#line 1277 "parser.tab.cpp"
    break;

  case 13: /* Statements: Statement  */
#line 108 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement({(yyvsp[0].NodeStatement)});output::printProductionRule(12);}
#line 1283 "parser.tab.cpp"
    break;

  case 14: /* Statements: Statements Statement  */
#line 109 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement({(yyvsp[-1].NodeStatement), (yyvsp[0].NodeStatement)});output::printProductionRule(13);}
#line 1289 "parser.tab.cpp"
    break;

  case 15: /* Statement: LBRACE Statements RBRACE  */
#line 110 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement({(yyvsp[-2].NodeToken), (yyvsp[-1].NodeStatement), (yyvsp[0].NodeToken)});output::printProductionRule(14);}
#line 1295 "parser.tab.cpp"
    break;

  case 16: /* Statement: Type ID SC  */
#line 111 "parser.ypp"
                                                                                {output::printProductionRule(15);(yyval.NodeStatement) = new Node_Statement_ID_Decl((yyvsp[-2].NodeExp), (yyvsp[-1].NodeToken), (yyvsp[0].NodeToken));}
#line 1301 "parser.tab.cpp"
    break;

  case 17: /* Statement: Type ID ASSIGN Exp SC  */
#line 112 "parser.ypp"
                                                                                {output::printProductionRule(16);(yyval.NodeStatement) = new Node_Statement_ID_Decl((yyvsp[-4].NodeExp), (yyvsp[-3].NodeToken), (yyvsp[-2].NodeToken), (yyvsp[-1].NodeExp), (yyvsp[0].NodeToken));}
#line 1307 "parser.tab.cpp"
    break;

  case 18: /* Statement: ID ASSIGN Exp SC  */
#line 113 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_ID_Assign((yyvsp[-3].NodeToken),(yyvsp[-2].NodeToken),(yyvsp[-1].NodeExp),(yyvsp[0].NodeToken));output::printProductionRule(17);}
#line 1313 "parser.tab.cpp"
    break;

  case 19: /* Statement: Call SC  */
#line 114 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_Call((yyvsp[-1].NodeCall),(yyvsp[0].NodeToken));output::printProductionRule(18);}
#line 1319 "parser.tab.cpp"
    break;

  case 20: /* Statement: RETURN SC  */
#line 115 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_Ret((yyvsp[-1].NodeToken),(yyvsp[0].NodeToken));output::printProductionRule(19);}
#line 1325 "parser.tab.cpp"
    break;

  case 21: /* Statement: RETURN Exp SC  */
#line 116 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_Ret((yyvsp[-2].NodeToken),(yyvsp[-1].NodeExp),(yyvsp[0].NodeToken));output::printProductionRule(20);}
#line 1331 "parser.tab.cpp"
    break;

  case 22: /* Statement: IF LPAREN Exp RPAREN Statement  */
#line 117 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_IF((yyvsp[-4].NodeToken),(yyvsp[-3].NodeToken),(yyvsp[-2].NodeExp),(yyvsp[-1].NodeToken),(yyvsp[0].NodeStatement));output::printProductionRule(21);}
#line 1337 "parser.tab.cpp"
    break;

  case 23: /* Statement: IF LPAREN Exp RPAREN Statement ELSE Statement  */
#line 118 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_IF((yyvsp[-6].NodeToken),(yyvsp[-5].NodeToken),(yyvsp[-4].NodeExp),(yyvsp[-3].NodeToken),(yyvsp[-2].NodeStatement),(yyvsp[-1].NodeToken),(yyvsp[0].NodeStatement));output::printProductionRule(22);}
#line 1343 "parser.tab.cpp"
    break;

  case 24: /* Statement: WHILE LPAREN Exp RPAREN Statement  */
#line 119 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_While((yyvsp[-4].NodeToken),(yyvsp[-3].NodeToken),(yyvsp[-2].NodeExp),(yyvsp[-1].NodeToken),(yyvsp[0].NodeStatement));output::printProductionRule(23);}
#line 1349 "parser.tab.cpp"
    break;

  case 25: /* Statement: BREAK SC  */
#line 120 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_LoopMod((yyvsp[-1].NodeToken),(yyvsp[0].NodeToken));output::printProductionRule(24);}
#line 1355 "parser.tab.cpp"
    break;

  case 26: /* Statement: CONTINUE SC  */
#line 121 "parser.ypp"
                                                                                {(yyval.NodeStatement) = new Node_Statement_LoopMod((yyvsp[-1].NodeToken),(yyvsp[0].NodeToken));output::printProductionRule(25);}
#line 1361 "parser.tab.cpp"
    break;

  case 27: /* Call: ID LPAREN ExpList RPAREN  */
#line 122 "parser.ypp"
                                                                                {(yyval.NodeCall) = new Node_Call((yyvsp[-3].NodeToken),(yyvsp[-2].NodeToken),(yyvsp[-1].NodeExpList),(yyvsp[0].NodeToken));output::printProductionRule(26);}
#line 1367 "parser.tab.cpp"
    break;

  case 28: /* Call: ID LPAREN RPAREN  */
#line 123 "parser.ypp"
                                                                                {(yyval.NodeCall) = new Node_Call((yyvsp[-2].NodeToken),(yyvsp[-1].NodeToken),(yyvsp[0].NodeToken));output::printProductionRule(27);}
#line 1373 "parser.tab.cpp"
    break;

  case 29: /* ExpList: Exp  */
#line 124 "parser.ypp"
                                                                                {(yyval.NodeExpList) = new Node_ExpList((yyvsp[0].NodeExp));output::printProductionRule(28);}
#line 1379 "parser.tab.cpp"
    break;

  case 30: /* ExpList: Exp COMMA ExpList  */
#line 125 "parser.ypp"
                                                                                {(yyval.NodeExpList) = new Node_ExpList((yyvsp[-2].NodeExp),(yyvsp[-1].NodeToken),(yyvsp[0].NodeExpList));output::printProductionRule(29);}
#line 1385 "parser.tab.cpp"
    break;

  case 31: /* Type: INT  */
#line 126 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Type({(yyvsp[0].NodeToken)}, Type::INT);output::printProductionRule(30);}
#line 1391 "parser.tab.cpp"
    break;

  case 32: /* Type: BYTE  */
#line 127 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Type({(yyvsp[0].NodeToken)}, Type::BYTE);output::printProductionRule(31);}
#line 1397 "parser.tab.cpp"
    break;

  case 33: /* Type: BOOL  */
#line 128 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Type({(yyvsp[0].NodeToken)}, Type::BOOL);output::printProductionRule(32);}
#line 1403 "parser.tab.cpp"
    break;

  case 34: /* Exp: LPAREN Exp RPAREN  */
#line 129 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp({(yyvsp[-2].NodeToken),(yyvsp[-1].NodeExp),(yyvsp[0].NodeToken)},(yyvsp[-1].NodeExp)->type);output::printProductionRule(33);}
#line 1409 "parser.tab.cpp"
    break;

  case 35: /* Exp: Exp IF LPAREN Exp RPAREN ELSE Exp  */
#line 130 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_IfElse({(yyvsp[-6].NodeExp),(yyvsp[-5].NodeToken),(yyvsp[-4].NodeToken),(yyvsp[-3].NodeExp),(yyvsp[-2].NodeToken),(yyvsp[-1].NodeToken),(yyvsp[0].NodeExp)});output::printProductionRule(34);}
#line 1415 "parser.tab.cpp"
    break;

  case 36: /* Exp: Exp BINOP_ADD Exp  */
#line 131 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Binop({(yyvsp[-2].NodeExp),(yyvsp[-1].NodeToken),(yyvsp[0].NodeExp)});output::printProductionRule(35);}
#line 1421 "parser.tab.cpp"
    break;

  case 37: /* Exp: Exp BINOP_MUL Exp  */
#line 132 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Binop({(yyvsp[-2].NodeExp),(yyvsp[-1].NodeToken),(yyvsp[0].NodeExp)});output::printProductionRule(35);}
#line 1427 "parser.tab.cpp"
    break;

  case 38: /* Exp: ID  */
#line 133 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_ID((yyvsp[0].NodeToken));output::printProductionRule(36);(yyval.NodeExp) = new Node_Exp_ID((yyvsp[0].NodeToken));}
#line 1433 "parser.tab.cpp"
    break;

  case 39: /* Exp: Call  */
#line 134 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Call({(yyvsp[0].NodeCall)});output::printProductionRule(37);}
#line 1439 "parser.tab.cpp"
    break;

  case 40: /* Exp: NUM  */
#line 135 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_NUM({(yyvsp[0].NodeToken)}, Type::INT);output::printProductionRule(38);}
#line 1445 "parser.tab.cpp"
    break;

  case 41: /* Exp: NUM B  */
#line 136 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_NUM({(yyvsp[-1].NodeToken)}, Type::BYTE);output::printProductionRule(39);}
#line 1451 "parser.tab.cpp"
    break;

  case 42: /* Exp: STRING  */
#line 137 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Str({(yyvsp[0].NodeToken)});output::printProductionRule(40);}
#line 1457 "parser.tab.cpp"
    break;

  case 43: /* Exp: TRUE  */
#line 138 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Bool({(yyvsp[0].NodeToken)});output::printProductionRule(41);}
#line 1463 "parser.tab.cpp"
    break;

  case 44: /* Exp: FALSE  */
#line 139 "parser.ypp"
                                                                                {(yyval.NodeExp) = new Node_Exp_Bool({(yyvsp[0].NodeToken)});output::printProductionRule(42);}
#line 1469 "parser.tab.cpp"
    break;

  case 45: /* Exp: NOT Exp  */
#line 140 "parser.ypp"
                                                                                {output::printProductionRule(43);}
#line 1475 "parser.tab.cpp"
    break;

  case 46: /* Exp: Exp AND Exp  */
#line 141 "parser.ypp"
                                                                                {output::printProductionRule(44);}
#line 1481 "parser.tab.cpp"
    break;

  case 47: /* Exp: Exp OR Exp  */
#line 142 "parser.ypp"
                                                                                {output::printProductionRule(44);}
#line 1487 "parser.tab.cpp"
    break;

  case 48: /* Exp: Exp RELOP Exp  */
#line 143 "parser.ypp"
                                                                                {output::printProductionRule(45);}
#line 1493 "parser.tab.cpp"
    break;

  case 49: /* Exp: Exp EQUALITY Exp  */
#line 144 "parser.ypp"
                                                                                {output::printProductionRule(45);}
#line 1499 "parser.tab.cpp"
    break;

  case 50: /* Exp: LPAREN Type RPAREN Exp  */
#line 145 "parser.ypp"
                                                                                {output::printProductionRule(46);}
#line 1505 "parser.tab.cpp"
    break;


#line 1509 "parser.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 146 "parser.ypp"


int main(){
	yydebug = 0;
	int token;
	Frame_class::getInstance();
	while ((token = yyparse())) {
		continue;
	      //printf("%d %s %s\n", yylineno, token, yytext);
		  //cout << yylineno << " " << tokentype_str[token] << " " << token_value.c_str() << endl;
		  //flush(cout);
	}
	
	return 0;
}

int yyerror(const char * message){
    output::errorSyn(yylineno);
    exit(0);
}



