#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER

#include "parser.tab.h"

#define ENDFILE 0

#endif


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int TokenType;

typedef enum {Statement, Expressao, Nenhum} TipoNo;
typedef enum {IfT, WhileT, RetornoINT, RetornoVOIDT, NuloDecl, DeclVarT, DeclVetorT, DeclFuncT, VarParametroT, VetorParametroT, ParametroVOIDT } StatementTipo;
typedef enum {OperandoT, ConstanteT, IdT, VarDeclT, FunCallT, VetorParamT, AtribuicaoT, NuloEXP, OperadorRelacionalT} ExpressaoTipo;
struct noArvore {

    struct noArvore * filho[3];
    struct noArvore * irmao;

    int linha;
    char lexema[25];

    TipoNo tipono;
    StatementTipo statement;
    ExpressaoTipo expressao;
};
typedef struct noArvore NoArvore;

extern FILE* source;

extern int TraceScan;

extern int Error;

extern int linha; 


#endif