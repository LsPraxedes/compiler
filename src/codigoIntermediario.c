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
char* gerarCodigoIntermediario(NoArvore* no) {
    if (no == NULL)
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
    
   if (no->tipono == Expressao) {
        if (no->lexema != NULL && strcmp(no->lexema, "=") == 0) {
            // Nó de atribuição: filho[0] = variável, filho[1] = expressão
            char* var = gerarCodigoIntermediario(no->filho[0]);
            char* expr = gerarCodigoIntermediario(no->filho[1]);
            char* temp=novaTemp();
            adicionarCodigo("LOAD: %s = %s", temp, var);
            adicionarCodigo("%s = %s", var, expr);
            
            result = var;
            processado = 1;
        }
        else if (no->lexema != NULL &&
                (strcmp(no->lexema, "+") == 0 ||
                strcmp(no->lexema, "-") == 0 ||
                strcmp(no->lexema, "*") == 0 ||
                strcmp(no->lexema, "/") == 0)) {
            // Operação aritmética
            char* left = gerarCodigoIntermediario(no->filho[0]);
            char* right = gerarCodigoIntermediario(no->filho[1]);
            if(no->filho[0] != NULL && 
                (strcmp(no->filho[0]->lexema, "+") == 0 ||
                strcmp(no->filho[0]->lexema, "-") == 0 ||
                strcmp(no->filho[0]->lexema, "*") == 0 ||
                strcmp(no->filho[0]->lexema, "/") == 0)){
                char* temp = novaTemp();

                adicionarCodigo("%s = %s %s %s", temp, left, no->lexema,right);
                                
                result = temp;
            }
            else{
                result = (char*)malloc((strlen(left)+strlen(right)+strlen(no->lexema)+3)*sizeof(char));
                strcpy(result,left);
                strcat(result, " ");
                strcat(result,no->lexema);
                strcat(result, " ");
                strcat(result, right);
            }
            processado = 1;
        }
        else if (no->expressao == FunCallT) {
            // Chamada de função
            adicionarCodigo("CALL %s (%s)", no->lexema, gerarCodigoIntermediario(no->filho[0]));
            char* temp = novaTemp();
            adicionarCodigo("%s = RET", temp);
            result = temp;
            processado = 1;
        }
        else if (no->expressao == IdT) {
            // Nó identificador ou literal
            
                // Este é um acesso a uma variável simples (não array, ou array usado como um todo, o que C- pode não permitir)
                result = no->lexema;
                processado = 1;

        }
        else if(no->expressao==VetorParamT){
            char* nomeArray = no->lexema; // Nome do array (ex: "a")
        
                // Gera código para a expressão do índice e obtém seu valor/temporário
                char* tempIndice = gerarCodigoIntermediario(no->filho[0]); // Processa o nó 'i'
        
                // Cria um novo temporário para armazenar o valor lido de a[i]
                char* tempResultadoLeituraArray = novaTemp();
        
                // Adiciona a instrução TAC para carregar o valor do array
                // Formato: t_resultado = nome_array [ valor_indice ]
                adicionarCodigo("%s = %s*4", tempResultadoLeituraArray, tempIndice);
                result = (char*)malloc((strlen(tempResultadoLeituraArray)+strlen(nomeArray)+3)*sizeof(char));
                strcat(result, nomeArray);
                strcat(result, "[");
                strcat(result, tempResultadoLeituraArray);
                strcat(result, "]");
                processado = 1;
        }
        else if (no->lexema != NULL &&
            (strcmp(no->lexema, "<") == 0 || strcmp(no->lexema, ">") == 0 ||
            strcmp(no->lexema, "==") == 0 || strcmp(no->lexema, "!=") == 0 ||
            strcmp(no->lexema, "<=") == 0 || strcmp(no->lexema, ">=") == 0)) {

            char* left = gerarCodigoIntermediario(no->filho[0]);
            char* right = gerarCodigoIntermediario(no->filho[1]);
            char* temp = novaTemp();
            int val=0;
            for (int i = 0; i < strlen(right)-1; i++) {
                if (right[i] == ' '){ // Verifica se o caractere é um espaço literal
                    val=1;   
                break;
                }
            }
    
            if(val){
                adicionarCodigo("%s = %s", temp, right);
                char* temp2 = novaTemp();
                adicionarCodigo("%s = %s %s %s", temp2, left, no->lexema, temp);
                result = temp2; 
            }
            else{
                adicionarCodigo("%s = %s %s %s", temp, left, no->lexema, right);
                result = temp; 
            }
                
            processado = 1;
        }
    }
    else if (no->tipono == Statement) {
        if (no->statement == DeclFuncT) {
            // Para declaração de função, assume-se:
            //   filho[1] -> nome da função
            //   filho[2] -> corpo da função
            
            adicionarCodigo("\nFUNC %s:", no->filho[1]->lexema);
            gerarCodigoIntermediario(no->filho[1]->filho[0]); // Processa o corpo
            processado = 1;
        }
        else if (no->statement == IfT) {
            char* cond = gerarCodigoIntermediario(no->filho[1]);
            char* labelFalse = novoLabel();
            adicionarCodigo("IF !%s GOTO %s", cond, labelFalse);
            gerarCodigoIntermediario(no->filho[0]); // Bloco do IF
            adicionarCodigo("%s:", labelFalse);
            processado = 1;
        }
        else if (no->statement == WhileT) {
            char* labelInicio = novoLabel();
            char* labelSaida = novoLabel();
            adicionarCodigo("%s:", labelInicio);
            char* cond = gerarCodigoIntermediario(no->filho[0]);
            adicionarCodigo("IF !%s GOTO %s", cond, labelSaida);
            gerarCodigoIntermediario(no->filho[1]); // Corpo do loop
            adicionarCodigo("GOTO %s", labelInicio);
            adicionarCodigo("%s:", labelSaida);
            processado = 1;
        }
        else if (no->statement == RetornoINTT || no->statement == RetornoVOIDT) {
            char* retorno = gerarCodigoIntermediario(no->filho[0]);
            adicionarCodigo("RET %s", retorno);
            processado = 1;
        }
    }
    else{
            /* Percorre os filhos (assumindo um número máximo de filhos definido por MAX_FILHOS) */
        for (int i = 0; i < MAX_FILHOS; i++) {
            if (no->filho[i] != NULL) {
                char* aux = gerarCodigoIntermediario(no->filho[i]);
                printf("no %s no->filho%d %s\n",no->lexema,i,no->filho[i]->lexema);
            }
        }
    }

/* Se o nó não foi tratado especificamente, verifica se há um lexema
   (por exemplo, para declarações de variáveis ou literais) */
if (!processado) {
    if (no->lexema != NULL)
        result = no->lexema;
}


/* Processa os nós irmãos */
if (no->irmao){
    gerarCodigoIntermediario(no->irmao);
}
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