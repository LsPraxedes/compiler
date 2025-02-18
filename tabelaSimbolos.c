#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "tabelaSimbolos.h"

#define MAX 200

#define DECLARACAO 1
#define EXPRESSAO 2

int teveErroSemantico = 0;


/* Cria a tabela, alocando um vetor de ponteiros e inicializando com NULL */
SimboloTabela** criarTabela() {
    SimboloTabela** tabela = (SimboloTabela**) malloc(MAX * sizeof(SimboloTabela*));
    if (tabela == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a tabela de símbolos.\n");
        exit(1);
    }
    for (int i = 0; i < MAX; i++)
        tabela[i] = NULL;
    return tabela;
}

/* Retorna o índice do primeiro slot livre no vetor ou -1 se estiver cheio */
int proximoIndiceLivre(SimboloTabela** tabela) {
    for (int i = 0; i < MAX; i++) {
        if (tabela[i] == NULL)
            return i;
    }
    return -1;
}

/* Insere um novo símbolo na tabela */
SimboloTabela** inserirSimbolo(SimboloTabela** tabela, const char* nomeID, const char* escopo, StatementTipo tipoID, Tipagem tipagem, int linha) {
    int indice = proximoIndiceLivre(tabela);
    if (indice == -1) {
        fprintf(stderr, "Tabela de símbolos cheia.\n");
        return tabela;
    }
    tabela[indice] = (SimboloTabela*) malloc(sizeof(SimboloTabela));
    if (tabela[indice] == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o símbolo '%s'.\n", nomeID);
        exit(1);
    }
    strcpy(tabela[indice]->nomeID, nomeID);
    strcpy(tabela[indice]->escopo, escopo);
    tabela[indice]->tipoID = tipoID;
    tabela[indice]->tipagem = tipagem;
    tabela[indice]->linha = linha;
    return tabela;
}

/* Busca um símbolo na tabela pelo nome e escopo (ou global).
   Retorna o índice se encontrado ou -1 se não encontrado. */
int buscarSimbolo(SimboloTabela** tabela, const char* nomeID, const char* escopo) {
    for (int i = 0; i < MAX; i++) {
        if (tabela[i] != NULL) {
            if (strcmp(tabela[i]->nomeID, nomeID) == 0 &&
               (strcmp(tabela[i]->escopo, escopo) == 0 || strcmp(tabela[i]->escopo, "global") == 0))
                return i;
        }
    }
    return -1;
}

/* Verifica se o símbolo pode ser inserido (não foi declarado anteriormente).
   Se não houver duplicata retorna 1; caso contrário, imprime erro e retorna 0. */
int buscaIgual(SimboloTabela** tabela, const char* nomeID, const char* escopo, int linha) {
    if (buscarSimbolo(tabela, nomeID, escopo) == -1)
        return 1; // Ainda não declarado
    else {
        teveErroSemantico++;
        printf("ERRO SEMÂNTICO, LINHA: %d: Identificador '%s' já declarado no escopo '%s'.\n",
               linha, nomeID, escopo);
        return 0;
    }
}

/* Imprime a tabela de símbolos */
void printTabela(SimboloTabela** tabela) {
    printf("\nTABELA DE SIMBOLOS\n\n===================================================================================\n");
    printf("| %-4s | %-20s | %-15s | %-10s | %-10s | %-5s |\n",
           "ID", "Nome", "Escopo", "Tipo", "Tipagem", "Linha");
    printf("===================================================================================\n");
    for (int i = 0; i < MAX; i++) {
        if (tabela[i] != NULL) {
            printf("| %-4d | %-20s | %-15s | %-10s | %-10s | %-5d |\n",
                   i, tabela[i]->nomeID, tabela[i]->escopo,
                   (tabela[i]->tipoID == DeclVarT) ? "Variavel" : "Funcao",
                   (tabela[i]->tipagem == TIPO_INT) ? "Int" : "Void",
                   tabela[i]->linha);
        }
    }
    printf("===================================================================================\n");
}

/* Libera a memória alocada para a tabela */
void liberarTabela(SimboloTabela** tabela) {
    for (int i = 0; i < MAX; i++) {
        if (tabela[i] != NULL)
            free(tabela[i]);
    }
    free(tabela);
}


/* ======================= FUNÇÕES DE ANÁLISE SEMÂNTICA ======================= */


void percorrerArvore(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo);

/* Função que imprime a mensagem de erro semântico */
void mostrarErroSemantico(erroSemantico erro, char* nome, int linha) {

    teveErroSemantico++;
    
    printf("ERRO SEMÂNTICO, LINHA: %d: ", linha);
    switch (erro) {
        case DeclVoidVar:
            printf("Variável '%s' declarada como void.\n", nome);
            break;
        case DeclFuncExiste:
            printf("Função '%s' já declarada.\n", nome);
            break;
        case DeclVarExiste:
            printf("Variável '%s' já declarada.\n", nome);
            break;
        case DeclFuncVar:
            printf("Identificador '%s' já declarado como variável.\n", nome);
            break;
        case DeclVarFunc:
            printf("Identificador '%s' já declarado como função.\n", nome);
            break;
        case VarNaoDeclarada:
            printf("Variável '%s' não declarada.\n", nome);
            break;
        case FuncaoNaoDeclarada:
            printf("Função '%s' não declarada.\n", nome);
            break;
        case AtribFuncVoid:
            printf("Atribuição inválida: função '%s' do tipo void.\n", nome);
            break;
        case FuncMainNaoDeclarada:
            printf("Função main não declarada.\n");
            break;
        case VetorNaoDeclarado:
            printf("Vetor '%s' não declarado.\n", nome);
            break;
        case ChamadaFuncao:
            printf("Chamada de função '%s' inválida, utilize os ().\n", nome);
            break;
        default:
            printf("Erro semântico desconhecido.\n");
            break;
    }
}

/* Função que percorre declarações na árvore sintática e insere os símbolos na tabela */
void percorrerDecl(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* auxEscopo) {
    // Declaração de função
    if (arvoreSintatica->statement == DeclFuncT) {
        // Descobrir se a função é int ou void
        Tipagem tipo = (strcmp(arvoreSintatica->lexema, "INT") == 0) ? TIPO_INT : TIPO_VOID;
        
        // Nome da função (supondo que está em filho[1])
        char* nomeFunc = arvoreSintatica->filho[1]->lexema;
        
        // 1) Insira a função com escopo = "global"
        if (buscaIgual(tabela, nomeFunc, "global", arvoreSintatica->linha)) {
            inserirSimbolo(tabela, nomeFunc, "global", DeclFuncT, tipo, arvoreSintatica->linha);
        }
        
        // 2) Agora sim, troque o auxEscopo para o nome da função
        strcpy(auxEscopo, nomeFunc);

        // Se a função possui parâmetros (por exemplo, filho[0])
        // eles devem ser inseridos com escopo = nome da função (auxEscopo).
        if (arvoreSintatica->filho[0] != NULL && arvoreSintatica->filho[0]->statement != ParametroVOIDT) {
            NoArvore* auxNo = arvoreSintatica->filho[0];
            while (auxNo != NULL) {
                if (auxNo->filho[0] != NULL &&
                    buscaIgual(tabela, auxNo->filho[0]->lexema, auxEscopo, auxNo->linha)) {
                    
                    // Se parâmetro for int
                    if (strcmp(auxNo->lexema, "INT") == 0) {
                        inserirSimbolo(tabela, auxNo->filho[0]->lexema, auxEscopo,
                                       DeclVarT, TIPO_INT, auxNo->linha);
                    }
                    else {
                        // Se for void, emita erro
                        mostrarErroSemantico(DeclVoidVar, auxNo->filho[0]->lexema, auxNo->linha);
                    }
                }
                auxNo = auxNo->irmao;
            }
        }
    }
    // Se o nó é declaração de variável ou vetor
    else if (arvoreSintatica->statement == DeclVarT || arvoreSintatica->statement == DeclVetorT) {
        if (buscaIgual(tabela, arvoreSintatica->filho[0]->lexema, auxEscopo, arvoreSintatica->linha)) {
            if (strcmp(arvoreSintatica->lexema, "INT") == 0)
                inserirSimbolo(tabela, arvoreSintatica->filho[0]->lexema, auxEscopo, DeclVarT, TIPO_INT, arvoreSintatica->linha);
            else
                mostrarErroSemantico(DeclVoidVar, arvoreSintatica->filho[0]->lexema, arvoreSintatica->linha);
        }
    }
}

/* Função para tratar chamadas de função na árvore */
void chamadaFunc(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo) {
    if (arvoreSintatica->expressao == FunCallT) {
        if (buscarSimbolo(tabela, arvoreSintatica->lexema, escopo) == -1)
            mostrarErroSemantico(FuncaoNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->linha);
        // Aqui você pode adicionar linhas de código para atualizar informações do símbolo, se necessário.
    }
    else if (arvoreSintatica->expressao == IdT) {
        if (buscarSimbolo(tabela, arvoreSintatica->lexema, escopo) == -1)
            mostrarErroSemantico(VarNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->linha);
    }
}

/* Função que percorre expressões na árvore e verifica erros semânticos */
void percorrerExp(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo) {
    if (arvoreSintatica->expressao == IdT) {
        if (buscarSimbolo(tabela, arvoreSintatica->lexema, escopo) == -1)
            mostrarErroSemantico(VarNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->linha);
    }
    else if (arvoreSintatica->expressao == FunCallT) {
        if (buscarSimbolo(tabela, arvoreSintatica->lexema, escopo) == -1)
            mostrarErroSemantico(FuncaoNaoDeclarada, arvoreSintatica->lexema, arvoreSintatica->linha);
        NoArvore* filhoFunc = arvoreSintatica->filho[0];
        while (filhoFunc != NULL) {
            if (filhoFunc->filho[0] != NULL)
                percorrerArvore(filhoFunc, tabela, escopo);
            else
                chamadaFunc(filhoFunc, tabela, escopo);
            filhoFunc = filhoFunc->irmao;
        }
    }
    else if (arvoreSintatica->expressao == AtribuicaoT) {
        if (arvoreSintatica->filho[1]->expressao == FunCallT) {
            // Se necessário, verifique se função de tipo void está sendo atribuída
            if (buscarSimbolo(tabela, arvoreSintatica->filho[1]->lexema, escopo) != -1) {
                // Exemplo: se a função for void, emita erro (implemente conforme sua lógica)
            }
        }
    }
    else if (arvoreSintatica->expressao == VetorParamT) {
        if (buscarSimbolo(tabela, arvoreSintatica->lexema, escopo) == -1)
            mostrarErroSemantico(VetorNaoDeclarado, arvoreSintatica->lexema, arvoreSintatica->linha);
    }
}

/* Função recursiva que percorre toda a árvore sintática */
void percorrerArvore(NoArvore* arvoreSintatica, SimboloTabela** tabela, char* escopo) {
    char auxEscopo[MAXLEXEMA];
    strcpy(auxEscopo, escopo);
    
    if (arvoreSintatica == NULL)
        return;
    
    if (arvoreSintatica->tipono == Statement)
        percorrerDecl(arvoreSintatica, tabela, auxEscopo);
    
    if (arvoreSintatica->tipono == Expressao)
        percorrerExp(arvoreSintatica, tabela, auxEscopo);
    
    if (arvoreSintatica->expressao != FunCallT) {
        for (int i = 0; i < 3; i++) {
            if (arvoreSintatica->filho[i] != NULL)
                percorrerArvore(arvoreSintatica->filho[i], tabela, auxEscopo);
        }
    }
    
    if (strcmp(escopo, "global") == 0)
        percorrerArvore(arvoreSintatica->irmao, tabela, escopo);
    else
        percorrerArvore(arvoreSintatica->irmao, tabela, auxEscopo);
}

int verificarMain(SimboloTabela** tabela) {
    if (buscarSimbolo(tabela, "main", "global") == -1) {
        /* Aqui, usamos 0 como valor da linha; você pode ajustar para o valor que julgar adequado */
        mostrarErroSemantico(FuncMainNaoDeclarada, "main", 0);
        return -1;
    }
    return 0;
}