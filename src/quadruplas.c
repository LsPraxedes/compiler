#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
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

void inserirTempTab(tempTab** ttabela,char* lexema, char* ret, int num, char* escopo){
    
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
    strcpy(ttabela[i]->ret, ret);
    ttabela[i]->num = num;
    strcpy(ttabela[i]->escopo, escopo);

}

int pesquisarTempTab(tempTab** ttabela, char* var, char* escopo){

    int i;
    for(i=0;i<tempCounter; i++){
        if(ttabela[i]->lexema != NULL && strcmp(var,ttabela[i]->lexema)==0 && strcmp(escopo,ttabela[i]->escopo)==0)
            return i;
    }
    return -1;

}

void printTTabela(tempTab** ttabela) {
    FILE *arq;
    char* nomeArq = "outputs/TempTable.txt";
    arq = fopen(nomeArq, "w");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo"); // Mostra a mensagem de erro do sistema
    exit(EXIT_FAILURE); // Encerra o programa com código de erro
    }
    fprintf(arq,"\nTABELA DE TEMPORARIOS\n\n=============================================\n");
    fprintf(arq,"| %-8s | %-10s | %-5s | %-8s |\n","ID","RET Func","Num","Escopo");
    fprintf(arq,"=============================================\n");

    printf("\nTABELA DE TEMPORARIOS\n\n=============================================\n");
    printf("| %-8s | %-10s | %-5s | %-8s |\n","ID","RET Func","Num","Escopo");
    printf("=============================================\n");
    for (int i = 0; i < MAX; i++) {
        if (ttabela[i] != NULL) {
            printf("| %-8s | %-10s | %-5d | %-8s |\n",
                   ttabela[i]->lexema, ttabela[i]->ret, ttabela[i]->num, ttabela[i]->escopo);
            fprintf(arq,"| %-8s | %-10s | %-5d | %-8s |\n",
                   ttabela[i]->lexema, ttabela[i]->ret, ttabela[i]->num, ttabela[i]->escopo);
        }
    }
    printf("=============================================\n");
    fprintf(arq,"=============================================\n");
    fclose(arq);
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
char* gerarQuadruplas(tempTab** ttabela, NoArvore* no, char* escopo) {
    if (no == NULL)
        return NULL;

    char* result = NULL;
    int processado = 0; // indica se o nó já foi tratado especificamente
    
   if (no->tipono == Expressao) {
        if (no->lexema != NULL && strcmp(no->lexema, "=") == 0) {
            // Nó de atribuição: filho[0] = variável, filho[1] = expressão
            char* var = gerarQuadruplas(ttabela, no->filho[0], escopo);
            int indice1 = -1, indice2 = -1;
            indice1 = pesquisarTempTab(ttabela, var, escopo);
            char temp2[10];
            char temp[10];

            if(indice1==-1){
                strcpy(temp,novoTemp());    
                inserirTempTab(ttabela,var,"-",tempCounter-1, escopo);
            }
            else
                strcpy(temp, var);

            char* expr = gerarQuadruplas(ttabela, no->filho[1], escopo);
            if(!isdigit(expr[0])){
                indice2 = pesquisarTempTab(ttabela, expr, escopo);
                if(indice2==-1){
                    strcpy(temp2,novoTemp());
                    inserirTempTab(ttabela,expr,"-", tempCounter-1, escopo);
                }else{
                    sprintf(temp2, "t%d", ttabela[indice2]->num);
                }
            }else
                strcpy(temp2, expr);  
              
            if(indice1==-1){
                adicionarQuadruplas("(LOAD, %s, %s, -)", temp, var);
                adicionarQuadruplas("(ASSIGN, %s, %s, -)", temp, temp2);
                adicionarQuadruplas("(SW, %s, %s, -)", var, temp);
            }else{
                adicionarQuadruplas("(ASSIGN, t%d, %s, -)", ttabela[indice1]->num, temp2);
                adicionarQuadruplas("(SW, %s, t%d, -)", var, ttabela[indice1]->num);
            }
            
            
            result = var;
            processado = 1;
        }
        else if (no->lexema != NULL &&
            (strcmp(no->lexema, "+") == 0 || strcmp(no->lexema, "*") == 0 ||
            strcmp(no->lexema, "-") == 0 || strcmp(no->lexema, "/") == 0)) {

            char* left = gerarQuadruplas(ttabela, no->filho[0], escopo);
            char* right = gerarQuadruplas(ttabela, no->filho[1], escopo);
            int indice1 = -1;
            char temp[10];
            char temp2[10];
            char *temp3;
            indice1 = pesquisarTempTab(ttabela, left, escopo);
            if(indice1==-1){
                strcpy(temp,novoTemp());
                inserirTempTab(ttabela, left,"-", tempCounter-1,escopo);
            }else{
                sprintf(temp, "t%d", ttabela[indice1]->num);
            }

            if(!isdigit(right[0])){
                int indice2 =-1;
                indice2 = pesquisarTempTab(ttabela, right,escopo);
                if(indice2==-1){
                    strcpy(temp2,novoTemp());
                    inserirTempTab(ttabela,right,"-", tempCounter-1,escopo);
                }else{
                    sprintf(temp2, "t%d", ttabela[indice2]->num);
                }
                temp3 = novoTemp();
                if(strcmp(no->lexema, "+")==0){
                    adicionarQuadruplas("(ADD, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"ADD", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "-")==0){
                    adicionarQuadruplas("(SUB, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"SUB", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "*")==0){
                    adicionarQuadruplas("(MULT, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"MULT", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "/")==0){
                    adicionarQuadruplas("(DIV, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"DIV", tempCounter-1,escopo);
                }
            }else{
                strcpy(temp2, right);
                temp3 = novoTemp();
                if(strcmp(no->lexema, "+")==0){
                    adicionarQuadruplas("(ADDI, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"ADDI", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "-")==0){
                    adicionarQuadruplas("(SUBI, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"SUBI", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "*")==0){
                    adicionarQuadruplas("(MULTI, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"MULTI", tempCounter-1,escopo);
                }else if(strcmp(no->lexema, "/")==0){
                    adicionarQuadruplas("(DIVI, %s, %s, %s)", temp3, temp, temp2);
                    inserirTempTab(ttabela, temp3,"DIVI", tempCounter-1,escopo);
                }
            }
                

        
            
            result = temp3;

            processado = 1;
        }
        else if (no->expressao == FunCallT) {
            // Chamada de função
            char* param;
            char* temp;
            int num_arg=0;
            if(no->filho[0]!=NULL){
                num_arg++;
                if(no->filho[0]->irmao!=NULL){
                    num_arg++;
                    if(no->filho[0]->irmao->irmao!=NULL){
                        param = gerarQuadruplas(ttabela, no->filho[0]->irmao, escopo);
                        int indice = pesquisarTempTab(ttabela, param,escopo);
                        char temp1[10];
                        if(indice==-1){
                            strcpy(temp1,novoTemp());
                            inserirTempTab(ttabela, param,"-", tempCounter-1,escopo);
                            adicionarQuadruplas("(LOAD, %s, %s, -)", temp1,param);
                        }else{
                            sprintf(temp1, "t%d", ttabela[indice]->num);
                        }
                        adicionarQuadruplas("(PARAM, %s, %s, -)", temp1, no->lexema);
                        no->filho[0]->irmao->irmao=NULL;
                        num_arg++;
                    }
                    param = gerarQuadruplas(ttabela, no->filho[0]->irmao, escopo);
                    int indice2 = pesquisarTempTab(ttabela, param,escopo);
                    char temp2[10];
                    if(indice2==-1){
                        strcpy(temp2,novoTemp());
                        inserirTempTab(ttabela, param,"-", tempCounter-1,escopo);
                        adicionarQuadruplas("(LOAD, %s, %s, -)", temp2,param);
                    }else{
                        sprintf(temp2, "t%d", ttabela[indice2]->num);
                    }
                    adicionarQuadruplas("(PARAM, %s, %s, -)", temp2, no->lexema);
                    no->filho[0]->irmao=NULL;
                }
                param = gerarQuadruplas(ttabela, no->filho[0], escopo);
                int indice3 = pesquisarTempTab(ttabela, param,escopo);
                char temp3[10];
                if(indice3==-1){
                        strcpy(temp3,novoTemp());
                        inserirTempTab(ttabela, param,"-", tempCounter-1,escopo);
                        adicionarQuadruplas("(LOAD, %s, %s, -)", temp3,param);
                }else{
                    sprintf(temp3, "t%d", ttabela[indice3]->num);
                }
                
                adicionarQuadruplas("(PARAM, %s, %s, -)", temp3, no->lexema);
            }

            temp = novoTemp();
            char ID[10] = "RET ";
            strcat(ID, no->lexema);
            inserirTempTab(ttabela, temp,ID, tempCounter-1,escopo);
            adicionarQuadruplas("(CALL, %s, %s, %d)", temp,no->lexema, num_arg);
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

                int indice1 = -1, indice2 = -1;
                char temp[10];
                char* tempIndice = gerarQuadruplas(ttabela, no->filho[0], escopo);
                indice1 = pesquisarTempTab(ttabela, tempIndice, escopo);

                if(indice1==-1){
                    strcpy(temp,novoTemp());
                    inserirTempTab(ttabela, tempIndice,"-", tempCounter-1, escopo);
                    adicionarQuadruplas("(MULT, %s, %s, 1)", temp, tempIndice);
                }else{
                    sprintf(temp, "t%d", ttabela[indice1]->num);
                }

                strcat(no->lexema,"[");
                strcat(no->lexema,temp);
                strcat(no->lexema,"]");
                indice2 = pesquisarTempTab(ttabela, no->lexema, escopo);

                if(indice2==-1){
                    strcpy(temp,novoTemp());
                    inserirTempTab(ttabela, no->lexema,"-", tempCounter-1,escopo);
                    adicionarQuadruplas("(LOAD, %s, %s, -)", temp, no->lexema);
                }else{
                    sprintf(temp, "t%d", ttabela[indice2]->num);
                }

                result = no->lexema;
                processado = 1;
        }
        else if (no->lexema != NULL &&
            (strcmp(no->lexema, "<") == 0 || strcmp(no->lexema, ">") == 0 ||
            strcmp(no->lexema, "==") == 0 || strcmp(no->lexema, "!=") == 0 ||
            strcmp(no->lexema, "<=") == 0 || strcmp(no->lexema, ">=") == 0)) {

            char* left = gerarQuadruplas(ttabela, no->filho[0], escopo);
            char* right = gerarQuadruplas(ttabela, no->filho[1], escopo);
            int indice1 = -1;
            indice1 = pesquisarTempTab(ttabela, left, escopo);
            char temp[10];
            char temp2[10];
            if(indice1==-1){
                strcpy(temp,novoTemp());
                inserirTempTab(ttabela, left,"-", tempCounter-1,escopo);
            }else{
                sprintf(temp, "t%d", ttabela[indice1]->num);
            }
            for(int i=0; i<strlen(right); i++){
                if(!isdigit(right[i])){
                    int indice2 =-1;
                    indice2 = pesquisarTempTab(ttabela, right,escopo);
                    if(indice2==-1){
                        strcpy(temp2,novoTemp());
                        inserirTempTab(ttabela, right,"-", tempCounter-1,escopo);
                        adicionarQuadruplas("(LOAD, %s, %s, -)", temp2, right);
                    }else{
                        sprintf(temp2, "t%d", ttabela[indice2]->num);
                    }
                    break;
                }
                strcpy(temp2, right);
                    
            }
            
            char *temp3 = novoTemp();
            if(strcmp(no->lexema, "<")==0){
                adicionarQuadruplas("(SLT, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET SLT", tempCounter-1, escopo);
            }else if(strcmp(no->lexema, "==")==0){
                adicionarQuadruplas("(EQ, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET EQ", tempCounter-1, escopo);
            }else if(strcmp(no->lexema, "<=")==0){
                adicionarQuadruplas("(SLTEQ, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET SLTEQ", tempCounter-1, escopo);
            }else if(strcmp(no->lexema, ">")==0){
                adicionarQuadruplas("(SGT, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET SGT", tempCounter-1, escopo);
            }else if(strcmp(no->lexema, ">=")==0){
                adicionarQuadruplas("(SGTEQ, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET SGTEQ", tempCounter-1, escopo);
            }else if(strcmp(no->lexema, "!=")==0){
                adicionarQuadruplas("(NEQ, %s, %s, %s)", temp3, temp, temp2);
                inserirTempTab(ttabela,temp3,"RET NEQ", tempCounter-1, escopo);
            }

            result = temp3; 
                        

            processado = 1;
        }
        else 
        if(no->statement == VarParametroT){
            char* irmao = gerarQuadruplas(ttabela, no->filho[0], escopo);
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
            gerarQuadruplas(ttabela, no->filho[0], no->filho[1]->lexema); // Processa os argumentos
            gerarQuadruplas(ttabela, no->filho[1]->filho[0], no->filho[1]->lexema); // Processa o corpo
            adicionarQuadruplas("(END, %s, -, -)\n", no->filho[1]->lexema);
            processado = 1;
        }
        else if (no->statement == IfT) {
            char* cond = gerarQuadruplas(ttabela, no->filho[1], escopo);
            char* labelFalse = novaLabel();
            char* labelTrue = novaLabel();
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelFalse);
            gerarQuadruplas(ttabela, no->filho[0], escopo); // Bloco do IF
            adicionarQuadruplas("(GOTO, %s, - , -)", labelTrue);
            adicionarQuadruplas("(LAB, %s, -, -)", labelFalse);
            if(no->filho[2]!=NULL){
                gerarQuadruplas(ttabela, no->filho[2], escopo);
            }
            adicionarQuadruplas("(LAB, %s, -, -)", labelTrue);
            processado = 1;
        }
        else if (no->statement == WhileT) {
            char* labelInicio = novaLabel();
            char* labelSaida = novaLabel();
            adicionarQuadruplas("(LAB, %s, -, -)", labelInicio);
            char* cond = gerarQuadruplas(ttabela, no->filho[0], escopo);
            adicionarQuadruplas("(IFF, %s, %s, -)", cond, labelSaida);
            gerarQuadruplas(ttabela, no->filho[1], escopo); // Corpo do loop
            adicionarQuadruplas("(GOTO %s, -, -)", labelInicio);
            adicionarQuadruplas("(LAB, %s, -, -)", labelSaida);
            processado = 1;
        }
        else if (no->statement == RetornoINTT || no->statement == RetornoVOIDT) {
            char* result = gerarQuadruplas(ttabela, no->filho[0], escopo);
            char* temp = novoTemp();
            inserirTempTab(ttabela, result,"-",tempCounter-1,escopo);
            adicionarQuadruplas("(LOAD, %s, %s, -)", temp, result);
            adicionarQuadruplas("(RET, %s, -, -)", temp);
            processado = 1;
        }
        else if(no->statement == DeclVarT){
            char *right=gerarQuadruplas(ttabela, no->filho[0], escopo);
            adicionarQuadruplas("(ALLOC, %s, %s, -)", right, escopo);
            processado = 1;
        }
        else if(no->statement == DeclVetorT){
            char* temp = novoTemp();
            char* expr = gerarQuadruplas(ttabela, no->filho[1], escopo);
            char *left = gerarQuadruplas(ttabela, no->filho[0], escopo);
            strcat(left,"[");
            strcat(left,expr);
            strcat(left,"]");
            inserirTempTab(ttabela, left,"-", tempCounter-1, escopo);
            adicionarQuadruplas("(LOAD, %s, %s, -)", temp, left);
            processado = 1;
        }
        else if(no->statement == VetorParametroT || no->statement == VarParametroT){
            char *left = gerarQuadruplas(ttabela, no->filho[0], escopo);
            char *temp = novoTemp();
            inserirTempTab(ttabela, left,"-",tempCounter-1,escopo);
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
    gerarQuadruplas(ttabela, no->irmao, escopo);
}

return result;
}

/* Imprime o código intermediário */
void imprimirQuadruplas() {
    FILE *arq;
    char* nomeArq = "outputs/Quadruplas.txt";
    arq = fopen(nomeArq, "w");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo"); // Mostra a mensagem de erro do sistema
    exit(EXIT_FAILURE); // Encerra o programa com código de erro
}
    printf("\nCÓDIGO INTERMEDIÁRIO\n");
    printf("=========================================\n");
    for (int i = 0; i < contador_quad; i++) {
        printf("%s\n", quad[i].instrucao);
        fprintf(arq, "%s\n", quad[i].instrucao);
    }
    fclose(arq);
    printf("=========================================\n");
}