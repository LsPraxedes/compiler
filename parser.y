%{

#define YYPARSER

#include "global.h"
#include "flex.h"
#include "util.h"

static int yylex();

extern int linha;

int yyerror(char *message);

NoArvore AST;

%}

%start programa
%token TK_IF
%token TK_ELSE
%token TK_VIRGULA
%token TK_PONTO_VIRGULA
%token TK_ABRE_PARENTESES
%token TK_FECHA_PARENTESES
%token TK_ABRE_CHAVES
%token TK_FECHA_CHAVES
%token TK_ABRE_COLCHETES
%token TK_FECHA_COLCHETES
%left TK_MAIS
%left TK_MENOS
%left TK_MULTIPLICACAO
%left TK_DIVISAO
%left TK_MENOR
%left TK_MAIOR
%left TK_MENOR_IGUAL
%left TK_MAIOR_IGUAL
%token TK_ATRIBUICAO
%left  TK_IGUALDADE
%left  TK_DIFERENTE
%token TK_ABRE_COMENTARIO
%token TK_FECHA_COMENTARIO
%token TK_ID
%token TK_NUM
%token TK_INT
%token TK_RETORNO
%token TK_VOID
%token TK_WHILE
%token ERROR


%%

programa : declaracao_lista {
            AST = $1;
        };

declaracao_lista : declaracao_lista declaracao  {
                    if ($1 != NULL){
                        $$ = $1;
                        addIrmao($$, $2);
                    } 
                    else {
                        $$ = $2;
                    }
                    }
    | declaracao {$$ = $1;}
    ;

declaracao  : var_declaracao {$$ = $1;}
            | fun_declaracao {$$ = $1;}
            ;

var_declaracao  : tipo_especificador TK_ID TK_PONTO_VIRGULA {
                    $$ = $1;
                    $$->tipono = Statement;
                    $$->tipoDecl
}
    | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_NUM TK_FECHA_COLCHETES TK_PONTO_VIRGULA
    ;

tipo_especificador
    : TK_INT
    | TK_VOID
    ;

fun_declaracao
    : tipo_especificador TK_ID TK_ABRE_PARENTESES params TK_FECHA_PARENTESES composto_decl
    ;

params
    : param_lista
    | TK_VOID
    ;

param_lista
    : param_lista TK_VIRGULA param
    | param
    ;

param
    : tipo_especificador TK_ID
    | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_FECHA_COLCHETES
    ;

composto_decl
    : TK_ABRE_CHAVES local_declaracoes statement_lista TK_FECHA_CHAVES
    ;

local_declaracoes
    : local_declaracoes var_declaracao
    | TK_VOID    /* cuidado: isso permite um 'void' literal no código */
    ;

statement_lista
    : statement_lista statement
    | TK_VOID     /* idem */
    ;

statement
    : expressao_decl
    | composto_decl
    | selecao_decl
    | iteracao_decl
    | retorno_decl
    ;

expressao_decl
    : expressao TK_PONTO_VIRGULA
    | TK_PONTO_VIRGULA
    ;

selecao_decl
    : TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement
    | TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement TK_ELSE statement
    ;

iteracao_decl
    : TK_WHILE TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement
    ;

retorno_decl
    : TK_RETORNO TK_PONTO_VIRGULA
    | TK_RETORNO expressao TK_PONTO_VIRGULA
    ;

expressao
    : var TK_ATRIBUICAO expressao
    | simples_expressao
    ;

var
    : TK_ID
    | TK_ID TK_ABRE_COLCHETES expressao TK_FECHA_COLCHETES
    ;

simples_expressao
    : soma_expressao relacional soma_expressao
    | soma_expressao
    ;

relacional
    : TK_MENOR_IGUAL
    | TK_MENOR
    | TK_MAIOR
    | TK_MAIOR_IGUAL
    | TK_IGUALDADE
    | TK_DIFERENTE
    ;

soma_expressao
    : soma_expressao soma termo
    | termo
    ;

soma
    : TK_MAIS
    | TK_MENOS
    ;

termo
    : termo mult fator
    | fator
    ;

mult
    : TK_MULTIPLICACAO
    | TK_DIVISAO
    ;

fator
    : TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES
    | var
    | ativacao
    | TK_NUM
    ;

ativacao
    : TK_ID TK_ABRE_PARENTESES args TK_FECHA_PARENTESES
    ;

args
    : arg_lista
    | TK_VOID
    ;

arg_lista
    : arg_lista TK_VIRGULA expressao
    | expressao
    ;

%%

int yyerror(char *message) {

    if (yychar == -2) return 0;

    Error = TRUE;

    if (yychar == ERROR)
        printf("Erro léxico na linha %d. Lexema: ", linha);
    else
        printf("Erro sintático na linha %d. Token: ", linha);


    switch (yychar) {
        case TK_IF: printf("%s\n", lexema); break;
        case TK_ELSE: printf("%s\n", lexema); break;
        case TK_VIRGULA: printf("%s\n", lexema); break;
        case TK_PONTO_VIRGULA: printf("%s\n", lexema); break;
        case TK_ABRE_PARENTESES: printf("%s\n", lexema); break;
        case TK_FECHA_PARENTESES: printf("%s\n", lexema); break;
        case TK_ABRE_CHAVES: printf("%s\n", lexema); break;
        case TK_FECHA_CHAVES: printf("%s\n", lexema); break;
        case TK_ABRE_COLCHETES: printf("%s\n", lexema); break;
        case TK_FECHA_COLCHETES: printf("%s\n", lexema); break;
        case TK_MAIS: printf("%s\n", lexema); break;
        case TK_MENOS: printf("%s\n", lexema); break;
        case TK_MULTIPLICACAO: printf("%s\n", lexema); break;
        case TK_DIVISAO: printf("%s\n", lexema); break;
        case TK_MENOR: printf("%s\n", lexema); break;
        case TK_MAIOR: printf("%s\n", lexema); break;
        case TK_MENOR_IGUAL: printf("%s\n", lexema); break;
        case TK_MAIOR_IGUAL: printf("%s\n", lexema); break;
        case TK_ATRIBUICAO: printf("%s\n", lexema); break;
        case TK_IGUALDADE: printf("%s\n", lexema); break;
        case TK_DIFERENTE: printf("%s\n", lexema); break;
        case TK_ABRE_COMENTARIO: printf("%s\n", lexema); break;
        case TK_FECHA_COMENTARIO: printf("%s\n", lexema); break;
        case TK_ID: printf("%s\n", lexema); break;
        case TK_NUM: printf("%s\n", lexema); break;
        case TK_INT: printf("%s\n", lexema); break;
        case TK_RETORNO: printf("%s\n", lexema); break;
        case TK_VOID: printf("%s\n", lexema); break;
        case TK_WHILE: printf("%s\n", lexema); break;
        case ERROR: printf("%s\n", lexema); break;
        default: printf("Token desconhecido: %d\n", yychar);
    }

    return 0;
}

static int yylex(void) {
    return getToken();
}