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
} Quadruplas;

Quadruplas quad[MAX_INTERMEDIARIO];
int contador_quad = 0;
int tempCounter = 0;
int labelCount = 0;

/* Gera uma nova variável temporária */
char* novoTemp() {
    char* temp = (char*)malloc(10 * sizeof(char));
    sprintf(temp, "t%d", tempCounter++);
    return temp;
}

/* Gera um novo rótulo */
char* novaLabel() {
    char* label = (char*)malloc(10 * sizeof(char));
    sprintf(label, "L%d", labelCount++);
    return label;
}

/* Adiciona uma instrução ao código intermediário */
void adicionarQuadruplas(const char* formato, ...) {
    if (contador_quad >= MAX_INTERMEDIARIO) {
        fprintf(stderr, "Erro: Código intermediário excedeu o limite.\n");
        exit(1);
    }
    
    va_list args;
    va_start(args, formato);
    vsprintf(quad[contador_quad].instrucao, formato, args);
    va_end(args);
    contador_quad++;
}

/* Percorre a árvore e gera código intermediário */
char* gerarQuadruplas(NoArvore* no) {
    if (no == NULL)
        return NULL;

    char* result = NULL;
    int processado = 0; // indica se o nó já foi tratado especificamente
    
   if (no->tipono == Expressao) {
        if (no->lexema != NULL && strcmp(no->lexema, "=") == 0) {
            // Nó de atribuição: filho[0] = variável, filho[1] = expressão
            char* var = gerarQuadruplas(no->filho[0]);
            char* expr = gerarQuadruplas(no->filho[1]);
            
            adicionarQuadruplas("(ASSIGN, %s, %s, -)", var, expr);
            
            result = var;
            processado = 1;
        }
        else if (no->lexema != NULL &&
                (strcmp(no->lexema, "+") == 0 ||
                strcmp(no->lexema, "-") == 0 ||
                strcmp(no->lexema, "*") == 0 ||
                strcmp(no->lexema, "/") == 0)) {
            // Operação aritmética
            char* left = gerarQuadruplas(no->filho[0]);
            char* right = gerarQuadruplas(no->filho[1]);
            if(no->filho[0] != NULL && 
                (strcmp(no->filho[0]->lexema, "+") == 0 ||
                strcmp(no->filho[0]->lexema, "-") == 0 ||
                strcmp(no->filho[0]->lexema, "*") == 0 ||
                strcmp(no->filho[0]->lexema, "/") == 0)){
                char* temp = novoTemp();

                adicionarQuadruplas
            ("%s = %s %s %s", temp, left, no->lexema,right);
                                
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
            char* param;
            char* temp;
            int num_arg=0;
            if(no->filho[0]!=NULL){
                param = gerarQuadruplas(no->filho[0]);
                temp = novoTemp();
                adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                adicionarQuadruplas("(PARAM, %s, -, -)", temp);
                num_arg++;
                if(no->filho[0]->irmao!=NULL){
                    param = gerarQuadruplas(no->filho[0]->irmao);
                    temp = novoTemp();
                    adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                    adicionarQuadruplas("(PARAM, %s, -, -)", temp);
                    num_arg++;
                    if(no->filho[0]->irmao->irmao!=NULL){
                        param = gerarQuadruplas(no->filho[0]->irmao->irmao);
                        temp = novoTemp();
                        adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                        adicionarQuadruplas("(PARAM, %s, -, -)", temp);
                        num_arg++;
                }
                }
            }
            temp = novoTemp();
            adicionarQuadruplas("(CALL, %s, %s, %d)", temp ,no->lexema, num_arg);
            result = temp;
            processado = 1;
        }
        else if (no->expressao == IdT) {
            // Nó identificador ou literal
            
                
                result = no->lexema;
                processado = 1;

        }
        else if(no->expressao==VetorParamT){
            char* nomeArray = no->lexema; 
        
                
                char* tempIndice = gerarQuadruplas(no->filho[0]);
        
                
                char* tempResultadoLeituraArray = novoTemp();

                
                adicionarQuadruplas
            ("%s = %s*4", tempResultadoLeituraArray, tempIndice);
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

            char* left = gerarQuadruplas(no->filho[0]);
            char* right = gerarQuadruplas(no->filho[1]);
            char* temp = novoTemp();

            int val=0;
            for (int i = 0; i < strlen(right)-1; i++) {
                if (right[i] == ' '){ // Verifica se o caractere é um espaço literal
                    val=1;   
                break;
                }
            }
    
            if(val){
                adicionarQuadruplas("%s = %s", temp, right);
                char* temp2 = novoTemp();

                adicionarQuadruplas("%s = %s %s %s", temp2, left, no->lexema, temp);
                result = temp2; 
            }
            else{
                adicionarQuadruplas("%s = %s %s %s", temp, left, no->lexema, right);
                result = temp; 
            }
                
            processado = 1;
        }
        else 
        if(no->statement == VarParametroT){
            char* irmao = gerarQuadruplas(no->filho[0]);
            result = (char*)malloc((strlen(irmao)+strlen(no->lexema)+3)*sizeof(char));
            strcat(result,no->lexema);
            if(irmao!=NULL){
                strcat(result,",");
                strcat(result,irmao);
            }
        }
    }
    else if (no->tipono == Statement) {
        if (no->statement == DeclFuncT) {
            //   filho[1] -> nome da função
            //   filho[1]->filho[0] -> corpo da função
            gerarQuadruplas(no->filho[0]); // Processa o argumento
            adicionarQuadruplas("(FUNC, %s, %s, -)", no->lexema,no->filho[1]->lexema);
            gerarQuadruplas(no->filho[1]->filho[0]); // Processa o corpo
            adicionarQuadruplas("(END, %s, -, -)\n", no->filho[1]->lexema);
            processado = 1;
        }
        else if (no->statement == IfT) {
            char* cond = gerarQuadruplas(no->filho[1]);
            char* labelFalse = novaLabel();
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelFalse);
            gerarQuadruplas(no->filho[0]); // Bloco do IF
            adicionarQuadruplas("(LAB, %s, -, -)", labelFalse);
            gerarQuadruplas(no->filho[2]);
            processado = 1;
        }
        else if (no->statement == WhileT) {
            char* labelInicio = novaLabel();
            char* labelSaida = novaLabel();
            adicionarQuadruplas("(LAB, %s, -, -)", labelInicio);
            char* cond = gerarQuadruplas(no->filho[0]);
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelSaida);
            gerarQuadruplas(no->filho[1]); // Corpo do loop
            adicionarQuadruplas("(GOTO %s, -, -)", labelInicio);
            adicionarQuadruplas("(LAB, %s, -, -)", labelSaida);
            processado = 1;
        }
        else if (no->statement == RetornoINTT || no->statement == RetornoVOIDT) {
            char* result = gerarQuadruplas(no->filho[0]);
            char* temp = novoTemp();
            adicionarQuadruplas("(LOAD, %s, %s, -)", temp, result);
            adicionarQuadruplas("(RET, %s, -, -)", temp);
            processado = 1;
        }
        else if(no->statement == DeclVarT){
            char *right=gerarQuadruplas(no->filho[0]);
            adicionarQuadruplas("(ALLOC, %s, -, -)", right);
        }
        else if(no->statement == DeclVetorT){
            char* expr = gerarQuadruplas(no->filho[1]);
            char *left = gerarQuadruplas(no->filho[0]);
            adicionarQuadruplas("%s[%s]", left, expr);
        }
        else if(no->statement == VetorParametroT || no->statement == VarParametroT){
            char *left = gerarQuadruplas(no->filho[0]);
            adicionarQuadruplas("(ARG, %s, %s, -)", no->lexema, left);
        
        }
    }



/* Se o nó não foi tratado especificamente, verifica se há um lexema*/
if (!processado) {
    if (no->lexema != NULL)
        result = no->lexema;
}


/* Processa os nós irmãos */
if (no->irmao){
    gerarQuadruplas(no->irmao);
}

return result;
}

/* Imprime o código intermediário */
void imprimirQuadruplas() {
    printf("\nCÓDIGO INTERMEDIÁRIO\n");
    printf("=========================================\n");
    for (int i = 0; i < contador_quad; i++) {
        printf("%s\n", quad[i].instrucao);
    }
    printf("=========================================\n");
}