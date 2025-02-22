#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../headers/global.h"
#include "../headers/tabelaSimbolos.h"

#define MAX_INTERMEDIARIO 1000
#define MAX_FILHOS 3

typedef struct {
    char instrucao[50];
} CodigoIntermediario;

CodigoIntermediario codigo[MAX_INTERMEDIARIO];
int contador_codigo = 0;
int tempVarCounter = 0;
int labelCounter = 0;

/* Gera uma nova variável temporária */
char* novaTemp() {
    char* temp = (char*)malloc(10 * sizeof(char));
    sprintf(temp, "t%d", tempVarCounter++);
    return temp;
}

/* Gera um novo rótulo */
char* novoLabel() {
    char* label = (char*)malloc(10 * sizeof(char));
    sprintf(label, "L%d", labelCounter++);
    return label;
}

/* Adiciona uma instrução ao código intermediário */
void adicionarCodigo(const char* formato, ...) {
    if (contador_codigo >= MAX_INTERMEDIARIO) {
        fprintf(stderr, "Erro: Código intermediário excedeu o limite.\n");
        exit(1);
    }
    
    va_list args;
    va_start(args, formato);
    vsprintf(codigo[contador_codigo].instrucao, formato, args);
    va_end(args);
    contador_codigo++;
}

/* Percorre a árvore e gera código intermediário */
char* gerarCodigoIntermediario(NoArvore* arvoreSintatica) {
    if (arvoreSintatica == NULL)
        return NULL;
    
    char* result = NULL;
    int processado = 0; // indica se o nó já foi tratado especificamente

    /* 
       Se o nó é do tipo Expressao, tentamos identificar operações específicas.
       Aqui tratamos:
         - Atribuição: lexema "="
         - Operações aritméticas: "+", "-", "*", "/"
         - Chamada de função e identificador, conforme os campos 'expressao'
    */
    if (arvoreSintatica->tipono == Expressao) {
        if (arvoreSintatica->lexema != NULL && strcmp(arvoreSintatica->lexema, "=") == 0) {
            // Nó de atribuição: filho[0] = variável, filho[1] = expressão
            char* var = gerarCodigoIntermediario(arvoreSintatica->filho[0]);
            char* expr = gerarCodigoIntermediario(arvoreSintatica->filho[1]);
            adicionarCodigo("%s = %s", var, expr);
            result = var;
            processado = 1;
        }
        else if (arvoreSintatica->lexema != NULL &&
                 (strcmp(arvoreSintatica->lexema, "+") == 0 ||
                  strcmp(arvoreSintatica->lexema, "-") == 0 ||
                  strcmp(arvoreSintatica->lexema, "*") == 0 ||
                  strcmp(arvoreSintatica->lexema, "/") == 0)) {
            // Operação aritmética
            char* left = gerarCodigoIntermediario(arvoreSintatica->filho[0]);
            char* right = gerarCodigoIntermediario(arvoreSintatica->filho[1]);
            char* temp = novaTemp();
            adicionarCodigo("%s = %s %s %s", temp, left, arvoreSintatica->lexema, right);
            result = temp;
            processado = 1;
        }
        else if (arvoreSintatica->expressao == FunCallT) {
            // Chamada de função
            adicionarCodigo("CALL %s", arvoreSintatica->lexema);
            char* temp = novaTemp();
            adicionarCodigo("%s = RET", temp);
            result = temp;
            processado = 1;
        }
        else if (arvoreSintatica->expressao == IdT) {
            // Nó identificador ou literal
            result = arvoreSintatica->lexema;
            processado = 1;
        }
    }
    else if (arvoreSintatica->tipono == Statement) {
        if (arvoreSintatica->statement == DeclFuncT) {
            // Para declaração de função, assume-se:
            //   filho[1] -> nome da função
            //   filho[2] -> corpo da função
            adicionarCodigo("\nFUNC %s:", arvoreSintatica->filho[1]->lexema);
            gerarCodigoIntermediario(arvoreSintatica->filho[2]); // Processa o corpo
            processado = 1;
        }
        else if (arvoreSintatica->statement == IfT) {
            char* cond = gerarCodigoIntermediario(arvoreSintatica->filho[0]);
            char* labelFalse = novoLabel();
            adicionarCodigo("IF !%s GOTO %s", cond, labelFalse);
            gerarCodigoIntermediario(arvoreSintatica->filho[1]); // Bloco do IF
            adicionarCodigo("%s:", labelFalse);
            processado = 1;
        }
        else if (arvoreSintatica->statement == WhileT) {
            char* labelInicio = novoLabel();
            char* labelSaida = novoLabel();
            adicionarCodigo("%s:", labelInicio);
            char* cond = gerarCodigoIntermediario(arvoreSintatica->filho[0]);
            adicionarCodigo("IF !%s GOTO %s", cond, labelSaida);
            gerarCodigoIntermediario(arvoreSintatica->filho[1]); // Corpo do loop
            adicionarCodigo("GOTO %s", labelInicio);
            adicionarCodigo("%s:", labelSaida);
            processado = 1;
        }
        else if (arvoreSintatica->statement == RetornoINTT || arvoreSintatica->statement == RetornoVOIDT) {
            char* retorno = gerarCodigoIntermediario(arvoreSintatica->filho[0]);
            adicionarCodigo("RET %s", retorno);
            processado = 1;
        }
    }
    
    /* Se o nó não foi tratado especificamente, verifica se há um lexema
       (por exemplo, para declarações de variáveis ou literais) */
    if (!processado) {
        if (arvoreSintatica->lexema != NULL)
            result = arvoreSintatica->lexema;
    }
    
    /* Percorre os filhos (assumindo um número máximo de filhos definido por MAX_FILHOS) */
    for (int i = 0; i < MAX_FILHOS; i++) {
        if (arvoreSintatica->filho[i] != NULL) {
            char* aux = gerarCodigoIntermediario(arvoreSintatica->filho[i]);
            // Se ainda não há resultado e o filho gerou algo, utiliza-o
            if (result == NULL && aux != NULL)
                result = aux;
        }
    }
    
    /* Processa os nós irmãos */
    if (arvoreSintatica->irmao)
        gerarCodigoIntermediario(arvoreSintatica->irmao);
    
    return result;
}

/* Imprime o código intermediário */
void imprimirCodigoIntermediario() {
    printf("\nCÓDIGO INTERMEDIÁRIO\n");
    printf("=========================================\n");
    for (int i = 0; i < contador_codigo; i++) {
        printf("%s\n", codigo[i].instrucao);
    }
    printf("=========================================\n");
}
