#ifndef _TABELA_SIMBOLOS_H_
#define _TABELA_SIMBOLOS_H_

#include "global.h"

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

// struct Tabela {

//     struct Tabela* prox;
//     struct Tabela* anterior;
// };
// typedef struct Tabela Tabela;



#endif