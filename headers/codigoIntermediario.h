#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include "global.h"
#include "tabelaSimbolos.h"

#define MAX_INTERMEDIARIO 1000

/* Estrutura para armazenar instruções do código intermediário */
typedef struct {
    char instrucao[50];
} CodigoIntermediario;

/* Variáveis globais */
extern CodigoIntermediario codigo[MAX_INTERMEDIARIO];
extern int contador_codigo;
extern int tempVarCounter;
extern int labelCounter;

/* Funções para geração do código intermediário */
char* novaTemp();                     // Gera uma nova variável temporária (t0, t1, ...)
char* novoLabel();                     // Gera um novo rótulo (L0, L1, ...)
void adicionarCodigo(const char* formato, ...);  // Adiciona uma nova instrução ao código intermediário
char* gerarCodigoIntermediario(NoArvore* arvoreSintatica); // Percorre a árvore e gera código intermediário
void imprimirCodigoIntermediario();    // Imprime o código intermediário gerado

#endif /* CODIGO_INTERMEDIARIO_H */
