/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_PARSER_TAB_H_INCLUDED
# define YY_YY_YACC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_IF = 258,                   /* TK_IF  */
    TK_ELSE = 259,                 /* TK_ELSE  */
    TK_VIRGULA = 260,              /* TK_VIRGULA  */
    TK_PONTO_VIRGULA = 261,        /* TK_PONTO_VIRGULA  */
    TK_ABRE_PARENTESES = 262,      /* TK_ABRE_PARENTESES  */
    TK_FECHA_PARENTESES = 263,     /* TK_FECHA_PARENTESES  */
    TK_ABRE_CHAVES = 264,          /* TK_ABRE_CHAVES  */
    TK_FECHA_CHAVES = 265,         /* TK_FECHA_CHAVES  */
    TK_ABRE_COLCHETES = 266,       /* TK_ABRE_COLCHETES  */
    TK_FECHA_COLCHETES = 267,      /* TK_FECHA_COLCHETES  */
    TK_MAIS = 268,                 /* TK_MAIS  */
    TK_MENOS = 269,                /* TK_MENOS  */
    TK_MULTIPLICACAO = 270,        /* TK_MULTIPLICACAO  */
    TK_DIVISAO = 271,              /* TK_DIVISAO  */
    TK_MENOR = 272,                /* TK_MENOR  */
    TK_MAIOR = 273,                /* TK_MAIOR  */
    TK_MENOR_IGUAL = 274,          /* TK_MENOR_IGUAL  */
    TK_MAIOR_IGUAL = 275,          /* TK_MAIOR_IGUAL  */
    TK_ATRIBUICAO = 276,           /* TK_ATRIBUICAO  */
    TK_IGUALDADE = 277,            /* TK_IGUALDADE  */
    TK_DIFERENTE = 278,            /* TK_DIFERENTE  */
    TK_ABRE_COMENTARIO = 279,      /* TK_ABRE_COMENTARIO  */
    TK_FECHA_COMENTARIO = 280,     /* TK_FECHA_COMENTARIO  */
    TK_COMENTARIO_LINHA = 281,     /* TK_COMENTARIO_LINHA  */
    TK_ID = 282,                   /* TK_ID  */
    TK_NUM = 283,                  /* TK_NUM  */
    TK_INT = 284,                  /* TK_INT  */
    TK_RETORNO = 285,              /* TK_RETORNO  */
    TK_VOID = 286,                 /* TK_VOID  */
    TK_WHILE = 287,                /* TK_WHILE  */
    ERROR = 288,                   /* ERROR  */
    ENDFILE = 289                  /* ENDFILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_YACC_PARSER_TAB_H_INCLUDED  */
