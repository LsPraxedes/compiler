#ifndef QUADRUPLAS_H
#define QUADRUPLAS_H

#include "global.h"
#define MAX 200

typedef struct {

    char lexema[MAX];
    char ret[MAX];
    int num;
    char escopo[MAX];

} tempTab;

char* gerarQuadruplas(tempTab** ttabela, NoArvore* arvoreSintatica, char* escopo); // Percorre a árvore e gera código intermediário
void imprimirQuadruplas();    // Imprime o código intermediário gerado
void printTTabela();
tempTab** criarTempTabela();
void adicionarQuadruplas(const char* formato, ...);

#endif