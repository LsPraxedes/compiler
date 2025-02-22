#ifndef _TABELA_SIMBOLOS_H_
#define _TABELA_SIMBOLOS_H_

#include "global.h"

extern int teveErroSemantico;

typedef enum {
    DeclVoidVar,
    DeclFuncExiste,
    DeclVarExiste,
    DeclFuncVar,
    DeclVarFunc,
    VarNaoDeclarada,
    FuncaoNaoDeclarada,
    AtribFuncVoid,
    FuncMainNaoDeclarada,
    VetorNaoDeclarado,
    ChamadaFuncao
} erroSemantico;

struct SimboloTabela {

    char nomeID[MAXLEXEMA];
    char escopo[MAXLEXEMA];
    StatementTipo tipoID;
    Tipagem tipagem;
    int linha;
};
typedef struct SimboloTabela SimboloTabela;

SimboloTabela** criarTabela(void);

SimboloTabela** inserirSimbolo(SimboloTabela** tabela, const char* nomeID, const char* escopo, StatementTipo tipoID, Tipagem tipagem, int linha);

void percorrerArvore(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo);

int verificarMain(SimboloTabela** tabela);

void printTabela(SimboloTabela** tabela);

#endif