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
#line 1 "YACC/parser.y"

    #define YYPARSER

    #include "../headers/global.h"
    #include "../headers/lexer.h"
    #include "../headers/util.h"

    #define YYSTYPE NoArvore*
    #define MAX_NOS 1000

    static int yylex();
    extern int linha;

    int yyparse(void);
    int yyerror(char *message);

    void printArvore(NoArvore* raiz, FILE* arq, int num, int u);

    NoArvore* AST;

#line 92 "YACC/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_IF = 3,                      /* TK_IF  */
  YYSYMBOL_TK_ELSE = 4,                    /* TK_ELSE  */
  YYSYMBOL_TK_VIRGULA = 5,                 /* TK_VIRGULA  */
  YYSYMBOL_TK_PONTO_VIRGULA = 6,           /* TK_PONTO_VIRGULA  */
  YYSYMBOL_TK_ABRE_PARENTESES = 7,         /* TK_ABRE_PARENTESES  */
  YYSYMBOL_TK_FECHA_PARENTESES = 8,        /* TK_FECHA_PARENTESES  */
  YYSYMBOL_TK_ABRE_CHAVES = 9,             /* TK_ABRE_CHAVES  */
  YYSYMBOL_TK_FECHA_CHAVES = 10,           /* TK_FECHA_CHAVES  */
  YYSYMBOL_TK_ABRE_COLCHETES = 11,         /* TK_ABRE_COLCHETES  */
  YYSYMBOL_TK_FECHA_COLCHETES = 12,        /* TK_FECHA_COLCHETES  */
  YYSYMBOL_TK_MAIS = 13,                   /* TK_MAIS  */
  YYSYMBOL_TK_MENOS = 14,                  /* TK_MENOS  */
  YYSYMBOL_TK_MULTIPLICACAO = 15,          /* TK_MULTIPLICACAO  */
  YYSYMBOL_TK_DIVISAO = 16,                /* TK_DIVISAO  */
  YYSYMBOL_TK_MENOR = 17,                  /* TK_MENOR  */
  YYSYMBOL_TK_MAIOR = 18,                  /* TK_MAIOR  */
  YYSYMBOL_TK_MENOR_IGUAL = 19,            /* TK_MENOR_IGUAL  */
  YYSYMBOL_TK_MAIOR_IGUAL = 20,            /* TK_MAIOR_IGUAL  */
  YYSYMBOL_TK_ATRIBUICAO = 21,             /* TK_ATRIBUICAO  */
  YYSYMBOL_TK_IGUALDADE = 22,              /* TK_IGUALDADE  */
  YYSYMBOL_TK_DIFERENTE = 23,              /* TK_DIFERENTE  */
  YYSYMBOL_TK_ABRE_COMENTARIO = 24,        /* TK_ABRE_COMENTARIO  */
  YYSYMBOL_TK_FECHA_COMENTARIO = 25,       /* TK_FECHA_COMENTARIO  */
  YYSYMBOL_TK_COMENTARIO_LINHA = 26,       /* TK_COMENTARIO_LINHA  */
  YYSYMBOL_TK_ID = 27,                     /* TK_ID  */
  YYSYMBOL_TK_NUM = 28,                    /* TK_NUM  */
  YYSYMBOL_TK_INT = 29,                    /* TK_INT  */
  YYSYMBOL_TK_RETORNO = 30,                /* TK_RETORNO  */
  YYSYMBOL_TK_VOID = 31,                   /* TK_VOID  */
  YYSYMBOL_TK_WHILE = 32,                  /* TK_WHILE  */
  YYSYMBOL_ERROR = 33,                     /* ERROR  */
  YYSYMBOL_ENDFILE = 34,                   /* ENDFILE  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_programa = 36,                  /* programa  */
  YYSYMBOL_declaracao_lista = 37,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 38,                /* declaracao  */
  YYSYMBOL_var_declaracao = 39,            /* var_declaracao  */
  YYSYMBOL_tipo_especificador = 40,        /* tipo_especificador  */
  YYSYMBOL_fun_declaracao = 41,            /* fun_declaracao  */
  YYSYMBOL_fun_id = 42,                    /* fun_id  */
  YYSYMBOL_params = 43,                    /* params  */
  YYSYMBOL_param_lista = 44,               /* param_lista  */
  YYSYMBOL_param = 45,                     /* param  */
  YYSYMBOL_composto_decl = 46,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 47,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 48,           /* statement_lista  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_expressao_decl = 50,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 51,              /* selecao_decl  */
  YYSYMBOL_fatoracao = 52,                 /* fatoracao  */
  YYSYMBOL_iteracao_decl = 53,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 54,              /* retorno_decl  */
  YYSYMBOL_expressao = 55,                 /* expressao  */
  YYSYMBOL_var = 56,                       /* var  */
  YYSYMBOL_simples_expressao = 57,         /* simples_expressao  */
  YYSYMBOL_relacional = 58,                /* relacional  */
  YYSYMBOL_soma_expressao = 59,            /* soma_expressao  */
  YYSYMBOL_soma = 60,                      /* soma  */
  YYSYMBOL_termo = 61,                     /* termo  */
  YYSYMBOL_mult = 62,                      /* mult  */
  YYSYMBOL_fator = 63,                     /* fator  */
  YYSYMBOL_ativacao = 64,                  /* ativacao  */
  YYSYMBOL_args = 65,                      /* args  */
  YYSYMBOL_arg_lista = 66                  /* arg_lista  */
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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   98

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  105

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    60,    60,    65,    74,    77,    80,    85,   100,   124,
     131,   140,   152,   163,   167,   170,   181,   190,   195,   210,
     227,   237,   245,   250,   258,   263,   266,   269,   272,   275,
     280,   283,   288,   305,   308,   313,   327,   336,   349,   361,
     367,   379,   394,   403,   408,   414,   420,   426,   432,   438,
     446,   455,   460,   466,   474,   483,   488,   494,   502,   505,
     508,   511,   524,   533,   536,   541,   549
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
  "\"end of file\"", "error", "\"invalid token\"", "TK_IF", "TK_ELSE",
  "TK_VIRGULA", "TK_PONTO_VIRGULA", "TK_ABRE_PARENTESES",
  "TK_FECHA_PARENTESES", "TK_ABRE_CHAVES", "TK_FECHA_CHAVES",
  "TK_ABRE_COLCHETES", "TK_FECHA_COLCHETES", "TK_MAIS", "TK_MENOS",
  "TK_MULTIPLICACAO", "TK_DIVISAO", "TK_MENOR", "TK_MAIOR",
  "TK_MENOR_IGUAL", "TK_MAIOR_IGUAL", "TK_ATRIBUICAO", "TK_IGUALDADE",
  "TK_DIFERENTE", "TK_ABRE_COMENTARIO", "TK_FECHA_COMENTARIO",
  "TK_COMENTARIO_LINHA", "TK_ID", "TK_NUM", "TK_INT", "TK_RETORNO",
  "TK_VOID", "TK_WHILE", "ERROR", "ENDFILE", "$accept", "programa",
  "declaracao_lista", "declaracao", "var_declaracao", "tipo_especificador",
  "fun_declaracao", "fun_id", "params", "param_lista", "param",
  "composto_decl", "local_declaracoes", "statement_lista", "statement",
  "expressao_decl", "selecao_decl", "fatoracao", "iteracao_decl",
  "retorno_decl", "expressao", "var", "simples_expressao", "relacional",
  "soma_expressao", "soma", "termo", "mult", "fator", "ativacao", "args",
  "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      31,   -40,   -40,     7,    31,   -40,   -40,    -9,   -40,   -40,
     -40,    -5,    14,   -40,    -1,    34,    21,    45,    12,    49,
      56,   -40,    64,    60,    63,    31,   -40,    61,   -40,   -40,
     -40,   -40,    31,   -40,    47,     2,    -5,    68,   -40,     8,
     -40,     3,   -40,    -4,    69,    70,   -40,   -40,   -40,   -40,
     -40,   -40,    72,    58,   -40,    32,    51,   -40,   -40,     8,
      73,     8,   -40,    74,     8,     8,   -40,     8,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,     8,     8,   -40,   -40,
       8,    75,   -40,    76,   -40,    77,   -40,    78,    79,   -40,
     -40,    55,    51,   -40,    10,   -40,    10,   -40,     8,    83,
     -40,   -40,    10,   -40,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    12,     0,     7,     0,    13,     0,    10,     0,     0,
      14,    17,     0,    18,     0,     0,     8,     0,    22,    11,
      16,    19,    24,    21,     0,     0,     0,     0,    31,     0,
      20,    40,    61,     0,     0,     0,    26,    23,    25,    27,
      28,    29,     0,    59,    39,    43,    51,    55,    60,     0,
       0,     0,    36,     0,     0,    64,    30,     0,    52,    53,
      45,    46,    44,    47,    48,    49,     0,     0,    56,    57,
       0,     0,    58,     0,    37,     0,    66,     0,    63,    38,
      59,    42,    50,    54,     0,    41,     0,    62,     0,    34,
      35,    65,     0,    32,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,    85,    50,    16,   -40,    84,   -40,   -40,
      65,    71,   -40,   -40,   -38,   -40,   -40,   -40,   -40,   -40,
     -39,   -33,   -40,   -40,    17,   -40,    15,   -40,    18,   -40,
     -40,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    45,    19,    20,
      21,    46,    32,    35,    47,    48,    49,   103,    50,    51,
      52,    53,    54,    76,    55,    77,    56,    80,    57,    58,
      87,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      60,    13,    62,    39,    63,    37,    14,     9,    38,    39,
     -12,    28,    40,    37,    61,    39,    38,    39,    11,    28,
      81,    15,    83,    41,    42,    85,    86,    16,    89,    41,
      42,    18,    43,    22,    44,    41,    42,    41,    42,    23,
      43,    18,    44,    90,    90,    68,    69,    90,    34,    70,
      71,    72,    73,   -15,    74,    75,    99,    24,   100,   101,
       1,    25,     2,     1,   104,    17,    78,    79,    68,    69,
      26,    27,    28,    31,    36,    59,    64,    65,    66,    67,
      84,    82,    33,    94,    98,    96,    97,   102,    95,    10,
      30,    12,    92,    91,     0,    29,     0,     0,    93
};

static const yytype_int8 yycheck[] =
{
      39,     6,     6,     7,    43,     3,    11,     0,     6,     7,
       7,     9,    10,     3,    11,     7,     6,     7,    27,     9,
      59,     7,    61,    27,    28,    64,    65,    28,    67,    27,
      28,    15,    30,    12,    32,    27,    28,    27,    28,    27,
      30,    25,    32,    76,    77,    13,    14,    80,    32,    17,
      18,    19,    20,     8,    22,    23,    94,     8,    96,    98,
      29,     5,    31,    29,   102,    31,    15,    16,    13,    14,
       6,    11,     9,    12,    27,     7,     7,     7,     6,    21,
       6,     8,    32,     8,     5,     8,     8,     4,    12,     4,
      25,     7,    77,    76,    -1,    24,    -1,    -1,    80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    31,    36,    37,    38,    39,    40,    41,     0,
      38,    27,    42,     6,    11,     7,    28,    31,    40,    43,
      44,    45,    12,    27,     8,     5,     6,    11,     9,    46,
      45,    12,    47,    39,    40,    48,    27,     3,     6,     7,
      10,    27,    28,    30,    32,    42,    46,    49,    50,    51,
      53,    54,    55,    56,    57,    59,    61,    63,    64,     7,
      55,    11,     6,    55,     7,     7,     6,    21,    13,    14,
      17,    18,    19,    20,    22,    23,    58,    60,    15,    16,
      62,    55,     8,    55,     6,    55,    55,    65,    66,    55,
      56,    59,    61,    63,     8,    12,     8,     8,     5,    49,
      49,    55,     4,    52,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    39,    39,    40,
      40,    41,    42,    43,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    64,    65,    65,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     0,     1,     1,     3,     1,     2,     4,
       4,     2,     0,     2,     0,     1,     1,     1,     1,     1,
       2,     1,     6,     2,     0,     5,     2,     3,     3,     1,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     4,     1,     0,     3,     1
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
  case 2: /* programa: declaracao_lista  */
#line 60 "YACC/parser.y"
                               {
                AST = yyvsp[0];
            }
#line 1222 "YACC/parser.tab.c"
    break;

  case 3: /* declaracao_lista: declaracao_lista declaracao  */
#line 65 "YACC/parser.y"
                                                   {
                        if (yyvsp[-1] != NULL){
                            yyval = yyvsp[-1];
                            addIrmao(yyval, yyvsp[0]);
                        } 
                        else {
                            yyval = yyvsp[0];
                        }
                    }
#line 1236 "YACC/parser.tab.c"
    break;

  case 4: /* declaracao_lista: declaracao  */
#line 74 "YACC/parser.y"
                                 {yyval = yyvsp[0];}
#line 1242 "YACC/parser.tab.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 77 "YACC/parser.y"
                             {
                yyval = yyvsp[0];
            }
#line 1250 "YACC/parser.tab.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 80 "YACC/parser.y"
                             {
                yyval = yyvsp[0];
            }
#line 1258 "YACC/parser.tab.c"
    break;

  case 7: /* var_declaracao: tipo_especificador TK_ID TK_PONTO_VIRGULA  */
#line 85 "YACC/parser.y"
                                                            {
                    yyval = yyvsp[-2];
                    yyval->tipono = Statement;
                    yyval->statement = DeclVarT;
                    yyval->linha = linha;

                    NoArvore* aux = novoNo();

                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                    addFilho(yyval, aux);

                    
                }
#line 1278 "YACC/parser.tab.c"
    break;

  case 8: /* var_declaracao: tipo_especificador TK_ID TK_ABRE_COLCHETES TK_NUM TK_FECHA_COLCHETES TK_PONTO_VIRGULA  */
#line 100 "YACC/parser.y"
                                                                                                        {
                    yyval = yyvsp[-5];
                    yyval->tipono = Statement;
                    yyval->statement = DeclVetorT;
                    yyval->linha = linha;

                    NoArvore* aux = novoNo();
                    NoArvore* aux2 = novoNo();
                    
                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                   

                    strcpy(aux2->lexema, pilha[indPilha]);
                    indPilha--;
                    
                    addFilho(yyval, aux2);
                    addFilho(yyval, aux);

                    
                }
#line 1305 "YACC/parser.tab.c"
    break;

  case 9: /* tipo_especificador: TK_INT  */
#line 124 "YACC/parser.y"
                             {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "INT");
                        yyval->linha = linha;

                        
                    }
#line 1317 "YACC/parser.tab.c"
    break;

  case 10: /* tipo_especificador: TK_VOID  */
#line 131 "YACC/parser.y"
                              {
                        yyval = novoNo();
                        strcpy(yyval->lexema, "VOID");
                        yyval->linha = linha;

                        
                    }
#line 1329 "YACC/parser.tab.c"
    break;

  case 11: /* fun_declaracao: tipo_especificador fun_id TK_ABRE_PARENTESES params TK_FECHA_PARENTESES composto_decl  */
#line 140 "YACC/parser.y"
                                                                                                        {
                    yyval = yyvsp[-5];

                    addFilho(yyval, yyvsp[-2]);
                    addFilho(yyval, yyvsp[-4]);
                    addFilho(yyvsp[-4], yyvsp[0]);
                    
                    yyval->tipono = Statement;
                    yyval->statement = DeclFuncT;
                }
#line 1344 "YACC/parser.tab.c"
    break;

  case 12: /* fun_id: TK_ID  */
#line 152 "YACC/parser.y"
                {
            yyval = novoNo();
                        
            strcpy(yyval->lexema, pilha[indPilha]);
            indPilha--;

            yyval->linha = linha;

            
        }
#line 1359 "YACC/parser.tab.c"
    break;

  case 13: /* params: %empty  */
#line 163 "YACC/parser.y"
                 {
            yyval = novoNo();
        }
#line 1367 "YACC/parser.tab.c"
    break;

  case 14: /* params: param_lista  */
#line 167 "YACC/parser.y"
                    {
            yyval = yyvsp[0];
        }
#line 1375 "YACC/parser.tab.c"
    break;

  case 15: /* params: TK_VOID  */
#line 170 "YACC/parser.y"
                  {
            yyval = novoNo();
            yyval->tipono = Statement;
            yyval->linha = linha;
            yyval->statement = ParametroVOIDT;
            strcpy(yyval->lexema, "VOID");

            
        }
#line 1389 "YACC/parser.tab.c"
    break;

  case 16: /* param_lista: param_lista TK_VIRGULA param  */
#line 181 "YACC/parser.y"
                                           {
                if(yyvsp[-2] != NULL){
                    yyval = yyvsp[-2];
                    addIrmao(yyval, yyvsp[0]);
                }
                else{
                    yyval = yyvsp[0];
                }	
            }
#line 1403 "YACC/parser.tab.c"
    break;

  case 17: /* param_lista: param  */
#line 190 "YACC/parser.y"
                    {
                yyval = yyvsp[0];
            }
#line 1411 "YACC/parser.tab.c"
    break;

  case 18: /* param: tipo_especificador TK_ID  */
#line 195 "YACC/parser.y"
                                   {
            yyval = yyvsp[-1];
            yyval->tipono = Statement;
            yyval->linha = linha;
            yyval->statement = VarParametroT;

            NoArvore* aux = novoNo();

            strcpy(aux->lexema, pilha[indPilha]);
            indPilha--;
        
            addFilho(yyval, aux);

            
        }
#line 1431 "YACC/parser.tab.c"
    break;

  case 19: /* param: tipo_especificador TK_ID TK_ABRE_COLCHETES TK_FECHA_COLCHETES  */
#line 210 "YACC/parser.y"
                                                                        {
            yyval = yyvsp[-3];
            yyval->tipono = Statement;
            yyval->linha = linha;
            yyval->statement = VetorParametroT;
            NoArvore* aux = novoNo();


            strcpy(aux->lexema, pilha[indPilha]);
            indPilha--;

            addFilho(yyval, aux);		

            
        }
#line 1451 "YACC/parser.tab.c"
    break;

  case 20: /* composto_decl: TK_ABRE_CHAVES local_declaracoes statement_lista TK_FECHA_CHAVES  */
#line 227 "YACC/parser.y"
                                                                                   {
                    if(yyvsp[-2] != NULL) {
                        yyval = yyvsp[-2];
                        addIrmao(yyval, yyvsp[-1]);
                    } else {
                        yyval = yyvsp[-1];
                    }
                }
#line 1464 "YACC/parser.tab.c"
    break;

  case 21: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 237 "YACC/parser.y"
                                                       {
                        if(yyvsp[-1] != NULL) {
                            yyval = yyvsp[-1];
                            addIrmao(yyval, yyvsp[0]);
                        } else {
                            yyval = yyvsp[0];
                        }
                    }
#line 1477 "YACC/parser.tab.c"
    break;

  case 22: /* local_declaracoes: %empty  */
#line 245 "YACC/parser.y"
                             {
                        yyval = NULL;
                    }
#line 1485 "YACC/parser.tab.c"
    break;

  case 23: /* statement_lista: statement_lista statement  */
#line 250 "YACC/parser.y"
                                            {
                    if(yyvsp[-1] != NULL) {
                        yyval = yyvsp[-1];
                        addIrmao(yyval, yyvsp[0]);
                    } else {
                        yyval = yyvsp[0];
                    }
                }
#line 1498 "YACC/parser.tab.c"
    break;

  case 24: /* statement_lista: %empty  */
#line 258 "YACC/parser.y"
                         {
                    yyval = NULL;
                }
#line 1506 "YACC/parser.tab.c"
    break;

  case 25: /* statement: expressao_decl  */
#line 263 "YACC/parser.y"
                             {
                yyval = yyvsp[0];
            }
#line 1514 "YACC/parser.tab.c"
    break;

  case 26: /* statement: composto_decl  */
#line 266 "YACC/parser.y"
                            {
                yyval = yyvsp[0];
            }
#line 1522 "YACC/parser.tab.c"
    break;

  case 27: /* statement: selecao_decl  */
#line 269 "YACC/parser.y"
                           {
                yyval = yyvsp[0];
            }
#line 1530 "YACC/parser.tab.c"
    break;

  case 28: /* statement: iteracao_decl  */
#line 272 "YACC/parser.y"
                            {
                yyval = yyvsp[0];
            }
#line 1538 "YACC/parser.tab.c"
    break;

  case 29: /* statement: retorno_decl  */
#line 275 "YACC/parser.y"
                           {
                yyval = yyvsp[0];
            }
#line 1546 "YACC/parser.tab.c"
    break;

  case 30: /* expressao_decl: expressao TK_PONTO_VIRGULA  */
#line 280 "YACC/parser.y"
                                             {
                    yyval = yyvsp[-1];
                }
#line 1554 "YACC/parser.tab.c"
    break;

  case 31: /* expressao_decl: TK_PONTO_VIRGULA  */
#line 283 "YACC/parser.y"
                                   {
                    yyval = NULL;
                }
#line 1562 "YACC/parser.tab.c"
    break;

  case 32: /* selecao_decl: TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement fatoracao  */
#line 288 "YACC/parser.y"
                                                                                            {
                    yyval = novoNo();
                    strcpy(yyval->lexema, "IF");
                    yyval->tipono = Statement;
                    yyval->linha = linha;
                    yyval->statement = IfT;

                    addFilho(yyval, yyvsp[-1]);		
                    addFilho(yyval, yyvsp[-3]);
                    if(yyvsp[0] != NULL){
                        addFilho(yyval, yyvsp[0]);
                    }

                    
                }
#line 1582 "YACC/parser.tab.c"
    break;

  case 33: /* fatoracao: TK_ELSE statement  */
#line 305 "YACC/parser.y"
                                {
                yyval = yyvsp[0];
            }
#line 1590 "YACC/parser.tab.c"
    break;

  case 34: /* fatoracao: %empty  */
#line 308 "YACC/parser.y"
                     {
                yyval = NULL;
            }
#line 1598 "YACC/parser.tab.c"
    break;

  case 35: /* iteracao_decl: TK_WHILE TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement  */
#line 313 "YACC/parser.y"
                                                                                      {
                    yyval = novoNo();
                    strcpy(yyval->lexema, "WHILE");
                    yyval->tipono = Statement;
                    yyval->linha = linha;
                    yyval->statement = WhileT;

                    addFilho(yyval, yyvsp[-2]);
                    addFilho(yyval, yyvsp[0]);

                    
                }
#line 1615 "YACC/parser.tab.c"
    break;

  case 36: /* retorno_decl: TK_RETORNO TK_PONTO_VIRGULA  */
#line 327 "YACC/parser.y"
                                              {
                    yyval = novoNo();
                    yyval->tipono = Statement;
                    yyval->linha = linha;
                    yyval->statement = RetornoVOIDT;
                    strcpy(yyval->lexema, "RetornoVOID");

                    
                }
#line 1629 "YACC/parser.tab.c"
    break;

  case 37: /* retorno_decl: TK_RETORNO expressao TK_PONTO_VIRGULA  */
#line 336 "YACC/parser.y"
                                                        {
                    yyval = novoNo();
                    yyval->tipono = Statement;
                    yyval->linha = linha;
                    yyval->statement = RetornoINTT;
                    strcpy(yyval->lexema, "RetornoINT");

                    addFilho(yyval, yyvsp[-1]);

                    
                }
#line 1645 "YACC/parser.tab.c"
    break;

  case 38: /* expressao: var TK_ATRIBUICAO expressao  */
#line 349 "YACC/parser.y"
                                          {
                yyval = novoNo();
                strcpy(yyval->lexema, "=");
                yyval->tipono = Expressao;
                yyval->linha = linha;
                yyval->expressao = AtribuicaoT;
            
                addFilho(yyval, yyvsp[-2]);
                addFilho(yyval, yyvsp[0]);

                
            }
#line 1662 "YACC/parser.tab.c"
    break;

  case 39: /* expressao: simples_expressao  */
#line 361 "YACC/parser.y"
                                {
                yyval = yyvsp[0];

            }
#line 1671 "YACC/parser.tab.c"
    break;

  case 40: /* var: TK_ID  */
#line 367 "YACC/parser.y"
            {
        yyval = novoNo();
        yyval->tipono = Expressao;
        yyval->linha = linha;
        yyval->expressao = IdT;

        strcpy(yyval->lexema, pilha[indPilha]);

        indPilha--;
        

    }
#line 1688 "YACC/parser.tab.c"
    break;

  case 41: /* var: TK_ID TK_ABRE_COLCHETES expressao TK_FECHA_COLCHETES  */
#line 379 "YACC/parser.y"
                                                           {
        yyval = novoNo();
        yyval->tipono = Expressao;
        yyval->linha = linha;
        yyval->expressao = VetorParamT;

        strcpy(yyval->lexema, pilha[indPilha]);
        indPilha--;

        addFilho(yyval, yyvsp[-1]);

        
    }
#line 1706 "YACC/parser.tab.c"
    break;

  case 42: /* simples_expressao: soma_expressao relacional soma_expressao  */
#line 394 "YACC/parser.y"
                                                               {
                        yyval = yyvsp[-1];
                        yyval->tipono = Expressao;
                        yyval->linha = linha;
                        yyval->expressao = OperadorRelacionalT;

                        addFilho(yyval, yyvsp[-2]);
                        addFilho(yyval, yyvsp[0]);
                    }
#line 1720 "YACC/parser.tab.c"
    break;

  case 43: /* simples_expressao: soma_expressao  */
#line 403 "YACC/parser.y"
                                     {
                        yyval = yyvsp[0];
                    }
#line 1728 "YACC/parser.tab.c"
    break;

  case 44: /* relacional: TK_MENOR_IGUAL  */
#line 408 "YACC/parser.y"
                             {
                yyval = novoNo();
                strcpy(yyval->lexema, "<=");

                
            }
#line 1739 "YACC/parser.tab.c"
    break;

  case 45: /* relacional: TK_MENOR  */
#line 414 "YACC/parser.y"
                       {
                yyval = novoNo();
                strcpy(yyval->lexema, "<");

                
            }
#line 1750 "YACC/parser.tab.c"
    break;

  case 46: /* relacional: TK_MAIOR  */
#line 420 "YACC/parser.y"
                       {
                yyval = novoNo();
                strcpy(yyval->lexema, ">");

                
            }
#line 1761 "YACC/parser.tab.c"
    break;

  case 47: /* relacional: TK_MAIOR_IGUAL  */
#line 426 "YACC/parser.y"
                             {
                yyval = novoNo();
                strcpy(yyval->lexema, ">=");

                
            }
#line 1772 "YACC/parser.tab.c"
    break;

  case 48: /* relacional: TK_IGUALDADE  */
#line 432 "YACC/parser.y"
                           {
                yyval = novoNo();
                strcpy(yyval->lexema, "==");

                
            }
#line 1783 "YACC/parser.tab.c"
    break;

  case 49: /* relacional: TK_DIFERENTE  */
#line 438 "YACC/parser.y"
                           {
                yyval = novoNo();
                strcpy(yyval->lexema, "!=");

                
            }
#line 1794 "YACC/parser.tab.c"
    break;

  case 50: /* soma_expressao: soma_expressao soma termo  */
#line 446 "YACC/parser.y"
                                            {
                    yyval = yyvsp[-1];
                    yyval->tipono = Expressao;
                    yyval->linha = linha;
                    yyval->expressao = OperandoT;

                    addFilho(yyval, yyvsp[-2]);
                    addFilho(yyval, yyvsp[0]);
                }
#line 1808 "YACC/parser.tab.c"
    break;

  case 51: /* soma_expressao: termo  */
#line 455 "YACC/parser.y"
                        {
                    yyval = yyvsp[0];
                }
#line 1816 "YACC/parser.tab.c"
    break;

  case 52: /* soma: TK_MAIS  */
#line 460 "YACC/parser.y"
                  {
            yyval = novoNo();
            strcpy(yyval->lexema, "+");

            
        }
#line 1827 "YACC/parser.tab.c"
    break;

  case 53: /* soma: TK_MENOS  */
#line 466 "YACC/parser.y"
                   {
            yyval = novoNo();
            strcpy(yyval->lexema, "-");

            
        }
#line 1838 "YACC/parser.tab.c"
    break;

  case 54: /* termo: termo mult fator  */
#line 474 "YACC/parser.y"
                           {
            yyval = yyvsp[-1];
            yyval->tipono = Expressao;
            yyval->linha = linha;
            yyval->expressao = OperandoT;

            addFilho(yyval, yyvsp[-2]);
            addFilho(yyval, yyvsp[0]);
        }
#line 1852 "YACC/parser.tab.c"
    break;

  case 55: /* termo: fator  */
#line 483 "YACC/parser.y"
                {
            yyval = yyvsp[0];
        }
#line 1860 "YACC/parser.tab.c"
    break;

  case 56: /* mult: TK_MULTIPLICACAO  */
#line 488 "YACC/parser.y"
                           {
            yyval = novoNo();
            strcpy(yyval->lexema, "*");
        
            
        }
#line 1871 "YACC/parser.tab.c"
    break;

  case 57: /* mult: TK_DIVISAO  */
#line 494 "YACC/parser.y"
                     {
            yyval = novoNo();
            strcpy(yyval->lexema, "/");

            
        }
#line 1882 "YACC/parser.tab.c"
    break;

  case 58: /* fator: TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES  */
#line 502 "YACC/parser.y"
                                                           {
            yyval = yyvsp[-1];
        }
#line 1890 "YACC/parser.tab.c"
    break;

  case 59: /* fator: var  */
#line 505 "YACC/parser.y"
              {
            yyval = yyvsp[0];
        }
#line 1898 "YACC/parser.tab.c"
    break;

  case 60: /* fator: ativacao  */
#line 508 "YACC/parser.y"
                   {
            yyval = yyvsp[0];
        }
#line 1906 "YACC/parser.tab.c"
    break;

  case 61: /* fator: TK_NUM  */
#line 511 "YACC/parser.y"
                 {
            yyval = novoNo();
            yyval->tipono = Expressao;
            yyval->linha = linha;
            yyval->expressao = ConstanteT;

            strcpy(yyval->lexema, pilha[indPilha]);
            indPilha--;

                        
        }
#line 1922 "YACC/parser.tab.c"
    break;

  case 62: /* ativacao: fun_id TK_ABRE_PARENTESES args TK_FECHA_PARENTESES  */
#line 524 "YACC/parser.y"
                                                                 {
                yyval = yyvsp[-3];
                yyval->tipono = Expressao;
                yyval->linha = linha;
                yyval->expressao = FunCallT;
                addFilho(yyval, yyvsp[-1]);
            }
#line 1934 "YACC/parser.tab.c"
    break;

  case 63: /* args: arg_lista  */
#line 533 "YACC/parser.y"
                    {
            yyval = yyvsp[0];
        }
#line 1942 "YACC/parser.tab.c"
    break;

  case 64: /* args: %empty  */
#line 536 "YACC/parser.y"
                 {
            yyval = NULL;
        }
#line 1950 "YACC/parser.tab.c"
    break;

  case 65: /* arg_lista: arg_lista TK_VIRGULA expressao  */
#line 541 "YACC/parser.y"
                                             {
                if(yyvsp[-2] != NULL){
                    yyval = yyvsp[-2];
                    addIrmao(yyval, yyvsp[0]);
                } else {
                    yyval = yyvsp[0];
                }
            }
#line 1963 "YACC/parser.tab.c"
    break;

  case 66: /* arg_lista: expressao  */
#line 549 "YACC/parser.y"
                        {
                yyval = yyvsp[0];
            }
#line 1971 "YACC/parser.tab.c"
    break;


#line 1975 "YACC/parser.tab.c"

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

#line 554 "YACC/parser.y"


int yyerror(char *message) {

    if (yychar == -2) 
        return 0;

    Error = TRUE;

    if (yychar == ERROR)
        printf("Erro léxico na linha %d. Lexema: ", linha);
    else
        printf("Erro sintático na linha %d. Token: ", linha-1);

    switch (yychar) {

        case TK_IF: printf("%s\n", ultimoLexema); break;
        case TK_ELSE: printf("%s\n", ultimoLexema); break;
        case TK_VIRGULA: printf("%s\n", ultimoLexema); break;
        case TK_PONTO_VIRGULA: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_PARENTESES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_PARENTESES: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_CHAVES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_CHAVES: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_COLCHETES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_COLCHETES: printf("%s\n", ultimoLexema); break;
        case TK_MAIS: printf("%s\n", ultimoLexema); break;
        case TK_MENOS: printf("%s\n", ultimoLexema); break;
        case TK_MULTIPLICACAO: printf("%s\n", ultimoLexema); break;
        case TK_DIVISAO: printf("%s\n", ultimoLexema); break;
        case TK_MENOR: printf("%s\n", ultimoLexema); break;
        case TK_MAIOR: printf("%s\n", ultimoLexema); break;
        case TK_MENOR_IGUAL: printf("%s\n", ultimoLexema); break;
        case TK_MAIOR_IGUAL: printf("%s\n", ultimoLexema); break;
        case TK_ATRIBUICAO: printf("%s\n", ultimoLexema); break;
        case TK_IGUALDADE: printf("%s\n", ultimoLexema); break;
        case TK_DIFERENTE: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_COMENTARIO: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_COMENTARIO: printf("%s\n", ultimoLexema); break;
        case TK_COMENTARIO_LINHA: printf("%s\n", ultimoLexema); break;
        case TK_ID: printf("%s\n", ultimoLexema); break;
        case TK_NUM: printf("%s\n", ultimoLexema); break;
        case TK_INT: printf("%s\n", ultimoLexema); break;
        case TK_RETORNO: printf("%s\n", ultimoLexema); break;
        case TK_VOID: printf("%s\n", ultimoLexema); break;
        case TK_WHILE: printf("%s\n", ultimoLexema); break;
        case ERROR: printf("%s\n", ultimoLexema); break;
        case ENDFILE: printf("\n"); break;

        default: printf("Token desconhecido: %d\n", yychar);
    }

    return 0;
}

static int yylex(void) {
    return getToken();
}

NoArvore* parse(void) {
    yyparse();
    return AST;
}
