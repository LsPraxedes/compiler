#ifndef _TABELA_SIMBOLOS_H_
#define _TABELA_SIMBOLOS_H_

#include "global.h"

extern int teveErroSemantico;

/* Enumeração para os tipos de erro semântico */
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

/* Estrutura para armazenar informações do símbolo */
struct SimboloTabela {
    char nomeID[MAXLEXEMA];
    char escopo[MAXLEXEMA];
    StatementTipo tipoID;
    Tipagem tipagem;
    int linha;
    struct SimboloTabela* prox;
    struct SimboloTabela* inicial;
};
typedef struct SimboloTabela SimboloTabela;

/* Protótipos das funções de manipulação da tabela de símbolos */
SimboloTabela** criarTabela(void);
int proximoIndiceLivre(SimboloTabela** tabela);

SimboloTabela** inserirSimbolo(SimboloTabela** tabela, const char* nomeID, const char* escopo, StatementTipo tipoID, Tipagem tipagem, int linha);
int buscarSimbolo(SimboloTabela** tabela, const char* nomeID, const char* escopo); 
int buscaIgual(SimboloTabela** tabela, const char* nomeID,const char* escopo,int linha);
void printTabela(SimboloTabela** tabela);
void liberarTabela(SimboloTabela** tabela);

/* Protótipos das funções de análise semântica */
void percorrerArvore(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo);
void mostrarErroSemantico(erroSemantico erro, char* nome, int linha);

#endif