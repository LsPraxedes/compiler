#ifndef QUADRUPLAS_H
#define QUADRUPLAS_H

#include "global.h"
#define MAX 200

typedef struct {

    char lexema[MAX];
    int num;

} tempTab;

char* gerarQuadruplas(tempTab** ttabela, NoArvore* arvoreSintatica); // Percorre a árvore e gera código intermediário
void imprimirQuadruplas();    // Imprime o código intermediário gerado
void printTTabela();
tempTab** criarTempTabela();

#endif