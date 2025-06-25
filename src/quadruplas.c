#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../headers/global.h"
#include "../headers/tabelaSimbolos.h"
#include "../headers/quadruplas.h"

#define MAX 200
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

tempTab** criarTempTabela(){
    tempTab** ttabela = (tempTab**)malloc(MAX * sizeof(tempTab*));
    if (ttabela == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a tabela de símbolos.\n");
        exit(1);
    }
    for (int i = 0; i < MAX; i++)
        ttabela[i] = NULL;

    return ttabela;
}

void inserirTempTab(tempTab** ttabela,char* lexema, int num){
    
    int i;
    for (i = 0; i < MAX; i++) {
        if (ttabela[i] == NULL)
            break;
    }

    ttabela[i] = (tempTab*) malloc(sizeof(tempTab));
    if (ttabela[i] == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o símbolo '%s'.\n", lexema);
        exit(1);
    }
    strcpy(ttabela[i]->lexema, lexema);
    ttabela[i]->num = num;

}

int pesquisarTempTab(tempTab** ttabela, char* var){

    int i;
    for(i=0;i<tempCounter; i++){
        printf("i %d\n",i);
        printf("ttabela[%d] %s\n",i, ttabela[i]->lexema);
        if(ttabela[i]->lexema != NULL && strcmp(var,ttabela[i]->lexema)==0)
            return i;
    }
    return -1;

}

void printTTabela(tempTab** ttabela) {
    printf("\nTABELA DE TEMPORARIOS\n\n===================================================================================\n");
    printf("| ID, Num |");
    printf("===================================================================================\n");
    for (int i = 0; i < MAX; i++) {
        if (ttabela[i] != NULL) {
            printf("| %s %d |\n",
                   ttabela[i]->lexema, ttabela[i]->num);
        }
    }
    printf("===================================================================================\n");
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
char* gerarQuadruplas(tempTab** ttabela, NoArvore* no) {
    if (no == NULL)
        return NULL;
    printf("%s\n", no->lexema);
    char* result = NULL;
    int processado = 0; // indica se o nó já foi tratado especificamente
    
   if (no->tipono == Expressao) {
        if (no->lexema != NULL && strcmp(no->lexema, "=") == 0) {
            // Nó de atribuição: filho[0] = variável, filho[1] = expressão
            char* var = gerarQuadruplas(ttabela, no->filho[0]);
            int indice = -1;
            indice = pesquisarTempTab(ttabela, var);
            if(indice==-1){
                char* temp = novoTemp();
                adicionarQuadruplas("(LOAD, %s, %s, -)", temp, var);
                char* expr = gerarQuadruplas(ttabela, no->filho[1]);
                adicionarQuadruplas("(ASSIGN, %s, %s, -)", temp, expr);
                adicionarQuadruplas("(SW, %s, %s, -)", var, temp);
            }else{
                char* expr = gerarQuadruplas(ttabela, no->filho[1]);
                adicionarQuadruplas("(ASSIGN, t%d, %s, -)", ttabela[indice]->num, expr);
                adicionarQuadruplas("(SW, %s, t%d, -)", var, ttabela[indice]->num);
            }
            
            
            result = var;
            processado = 1;
        }
        else if (no->lexema != NULL &&
                (strcmp(no->lexema, "+") == 0 ||
                strcmp(no->lexema, "-") == 0 ||
                strcmp(no->lexema, "*") == 0 ||
                strcmp(no->lexema, "/") == 0)) {
            // Operação aritmética
            char* left = gerarQuadruplas(ttabela, no->filho[0]);
            char* right = gerarQuadruplas(ttabela, no->filho[1]);
            char* temp = novoTemp();

            if(strcmp(no->lexema, "+")==0){
                adicionarQuadruplas("(ADD, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "-")==0){
                adicionarQuadruplas("(SUB, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "*")==0){
                adicionarQuadruplas("(MULT, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "/")==0){
                adicionarQuadruplas("(DIV, %s, %s, %s)", temp, left, right);
            }
                
            result = temp;

            processado = 1;
        }
        else if (no->expressao == FunCallT) {
            // Chamada de função
            char* param;
            char* temp;
            int num_arg=0;
            int indice;
            if(no->filho[0]!=NULL){
                num_arg++;
                if(no->filho[0]->irmao!=NULL){
                    num_arg++;
                    if(no->filho[0]->irmao->irmao!=NULL){
                        param = gerarQuadruplas(ttabela, no->filho[0]->irmao->irmao);
                        temp = novoTemp();
                        adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                        adicionarQuadruplas("(PARAM, %s, -, -)", temp);
                        no->filho[0]->irmao->irmao=NULL;
                        num_arg++;
                    }
                    param = gerarQuadruplas(ttabela, no->filho[0]->irmao);
                    temp = novoTemp();
                    adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                    adicionarQuadruplas("(PARAM, %s, -, -)", temp);
                    no->filho[0]->irmao=NULL;
                }
                param = gerarQuadruplas(ttabela, no->filho[0]);
                temp = novoTemp();
                adicionarQuadruplas("(LOAD, %s, %s, -)", temp,param);
                adicionarQuadruplas("(PARAM, %s, -, -)", temp);
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
        
                
                char* tempIndice = gerarQuadruplas(ttabela, no->filho[0]);
        
                
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

            char* left = gerarQuadruplas(ttabela, no->filho[0]);
            char* right = gerarQuadruplas(ttabela, no->filho[1]);
            int indice = -1;
            indice = pesquisarTempTab(ttabela, left);
            char temp[10];
            if(indice==-1){
                strcpy(temp,novoTemp());
            }else{
                sprintf(temp, "t%d", ttabela[indice]->num);
            }

            if(strcmp(no->lexema, "<")==0){
                adicionarQuadruplas("(SLT, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "==")==0){
                adicionarQuadruplas("(EQUAL, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "<=")==0){
                adicionarQuadruplas("(SLTEQ, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, ">")==0){
                adicionarQuadruplas("(SGT, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, ">=")==0){
                adicionarQuadruplas("(SGTEQ, %s, %s, %s)", temp, left, right);
            }else if(strcmp(no->lexema, "!=")==0){
                adicionarQuadruplas("(NEQ, %s, %s, %s)", temp, left, right);
            }
                result = temp; 
                        

            processado = 1;
        }
        else 
        if(no->statement == VarParametroT){
            char* irmao = gerarQuadruplas(ttabela, no->filho[0]);
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
            adicionarQuadruplas("(FUNC, %s, %s, -)", no->lexema,no->filho[1]->lexema);
            gerarQuadruplas(ttabela, no->filho[0]); // Processa os argumentos
            gerarQuadruplas(ttabela, no->filho[1]->filho[0]); // Processa o corpo
            adicionarQuadruplas("(END, %s, -, -)\n", no->filho[1]->lexema);
            processado = 1;
        }
        else if (no->statement == IfT) {
            char* cond = gerarQuadruplas(ttabela, no->filho[1]);
            char* labelFalse = novaLabel();
            char* labelTrue = novaLabel();
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelFalse);
            gerarQuadruplas(ttabela, no->filho[0]); // Bloco do IF
            adicionarQuadruplas("(GOTO, %s, - , -)", labelTrue);
            adicionarQuadruplas("(LAB, %s, -, -)", labelFalse);
            if(no->filho[2]!=NULL){
                gerarQuadruplas(ttabela, no->filho[2]);
                adicionarQuadruplas("(GOTO, %s, - , -)", labelTrue);
            }
            adicionarQuadruplas("(LAB, %s, -, -)", labelTrue);
            processado = 1;
        }
        else if (no->statement == WhileT) {
            char* labelInicio = novaLabel();
            char* labelSaida = novaLabel();
            adicionarQuadruplas("(LAB, %s, -, -)", labelInicio);
            char* cond = gerarQuadruplas(ttabela, no->filho[0]);
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelSaida);
            gerarQuadruplas(ttabela, no->filho[1]); // Corpo do loop
            adicionarQuadruplas("(GOTO %s, -, -)", labelInicio);
            adicionarQuadruplas("(LAB, %s, -, -)", labelSaida);
            processado = 1;
        }
        else if (no->statement == RetornoINTT || no->statement == RetornoVOIDT) {
            char* result = gerarQuadruplas(ttabela, no->filho[0]);
            char* temp = novoTemp();
            adicionarQuadruplas("(LOAD, %s, %s, -)", temp, result);
            adicionarQuadruplas("(RET, %s, -, -)", temp);
            processado = 1;
        }
        else if(no->statement == DeclVarT){
            char *right=gerarQuadruplas(ttabela, no->filho[0]);
            adicionarQuadruplas("(ALLOC, %s, -, -)", right);
            processado = 1;
        }
        else if(no->statement == DeclVetorT){
            char* expr = gerarQuadruplas(ttabela, no->filho[1]);
            char *left = gerarQuadruplas(ttabela, no->filho[0]);
            adicionarQuadruplas("%s[%s]", left, expr);
            processado = 1;
        }
        else if(no->statement == VetorParametroT || no->statement == VarParametroT){
            char *left = gerarQuadruplas(ttabela, no->filho[0]);
            char *temp = novoTemp();
            inserirTempTab(ttabela, left,tempCounter-1);
            adicionarQuadruplas("(ARG, %s, %s, -)", no->lexema, left);
            adicionarQuadruplas("(LOAD, %s, %s, -)", temp, left);
            processado = 1;
        }
    }



/* Se o nó não foi tratado especificamente, verifica se há um lexema*/
if (!processado) {
    if (no->lexema != NULL)
        result = no->lexema;
}


/* Processa os nós irmãos */
if (no->irmao){
    gerarQuadruplas(ttabela, no->irmao);
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