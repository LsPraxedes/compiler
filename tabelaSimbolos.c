#include "global.h"
#include "tabelaSimbolos.h"

#define MAX 200

// Tabela* criaTabela(){

//     Tabela* tabela = (Tabela*)malloc(sizeof(Tabela));
//     if (!tabela) {
//         fprintf(stderr, "Erro ao alocar memória para a tabela de símbolos.\n");
//         exit(EXIT_FAILURE);
//     }
//     tabela->prox = NULL;
//     tabela->anterior = NULL;
//     return tabela;
// }

SimboloTabela** criarTabela(){

    SimboloTabela** tabela = (SimboloTabela**)malloc(MAX*sizeof(SimboloTabela*));

    for (int i = 0; i<MAX; i++)
        tabela[i] = NULL;

    return tabela;
}

SimboloTabela** inserirSimbolo(SimboloTabela** tabela, char nomeID[MAXLEXEMA], char escopo[MAXLEXEMA], StatementTipo tipoID, Tipagem tipagem, int linha, int indice){

    strcpy(tabela[indice]->nomeID, nomeID);
    strcpy(tabela[indice]->escopo, escopo);    
    tabela[indice]->tipagem = tipagem;
    tabela[indice]->tipoID = tipoID;
    tabela[indice]->linha = linha;

    return tabela;
}

void printTabela(SimboloTabela** tabela) {
    printf("======================================================================\n");
    printf("| %-4s | %-20s | %-15s | %-10s | %-10s | %-5s |\n", "ID", "Nome", "Escopo", "Tipo", "Tipagem", "Linha");
    printf("======================================================================\n");
    
    for (int i = 0; i < MAX; i++) {
        if (tabela[i] != NULL) {
            printf("| %-4d | %-20s | %-15s | %-10s | %-10s | %-5d |\n",
                   i, tabela[i]->nomeID, tabela[i]->escopo,
                   (tabela[i]->tipoID == DeclVarT) ? "Variavel" : "Funcao",
                   (tabela[i]->tipagem == TIPO_INT) ? "Int" : "Void",
                   tabela[i]->linha);
        }
    }
    
    printf("======================================================================\n");
}



