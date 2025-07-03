#include "../headers/global.h"
#include "../headers/util.h"

void printToken( TokenType token, FILE *arq, const char* lexema) {
   switch (token)
   {
     case TK_IF:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_RETORNO:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_ELSE:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_INT:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_WHILE:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_VOID:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_IGUALDADE:
        fprintf(stdout,"==\n");
        fprintf(arq,"==\n"); // Adicionado para arquivo
        break;
     case TK_ATRIBUICAO:
        fprintf(stdout,"=\n");
        fprintf(arq,"=\n"); // Adicionado para arquivo
        break;
     case TK_DIFERENTE:
        fprintf(stdout,"!=\n");
        fprintf(arq,"!=\n"); // Adicionado para arquivo
        break;
     case TK_MENOR:
        fprintf(stdout,"<\n");
        fprintf(arq,"<\n"); // Adicionado para arquivo
        break;
     case TK_MAIOR:
        fprintf(stdout,">\n");
        fprintf(arq,">\n"); // Adicionado para arquivo
        break;
     case TK_MENOR_IGUAL:
        fprintf(stdout,"<=\n");
        fprintf(arq,"<=\n"); // Adicionado para arquivo
        break;
     case TK_MAIOR_IGUAL:
        fprintf(stdout,">=\n");
        fprintf(arq,">=\n"); // Adicionado para arquivo
        break;
     case TK_ABRE_PARENTESES:
        fprintf(stdout,"(\n");
        fprintf(arq,"(\n"); // Adicionado para arquivo
        break;
     case TK_FECHA_PARENTESES:
        fprintf(stdout,")\n");
        fprintf(arq,")\n"); // Adicionado para arquivo
        break;
     case TK_ABRE_COLCHETES:
        fprintf(stdout,"[\n");
        fprintf(arq,"[\n"); // Adicionado para arquivo
        break;
     case TK_FECHA_COLCHETES:
        fprintf(stdout,"]\n");
        fprintf(arq,"]\n"); // Adicionado para arquivo
        break;
     case TK_ABRE_CHAVES:
        fprintf(stdout,"{\n");
        fprintf(arq,"{\n"); // Adicionado para arquivo
        break;
     case TK_FECHA_CHAVES:
        fprintf(stdout,"}\n");
        fprintf(arq,"}\n"); // Adicionado para arquivo
        break;
     case TK_PONTO_VIRGULA:
        fprintf(stdout,";\n");
        fprintf(arq,";\n"); // Adicionado para arquivo
        break;
     case TK_VIRGULA:
        fprintf(stdout,",\n");
        fprintf(arq,",\n"); // Adicionado para arquivo
        break;
     case TK_MAIS:
        fprintf(stdout,"+\n");
        fprintf(arq,"+\n"); // Adicionado para arquivo
        break;
     case TK_MENOS:
        fprintf(stdout,"-\n");
        fprintf(arq,"-\n"); // Adicionado para arquivo
        break;
     case TK_MULTIPLICACAO:
        fprintf(stdout,"*\n");
        fprintf(arq,"*\n"); // Adicionado para arquivo
        break;
     case TK_DIVISAO:
        fprintf(stdout,"/\n");
        fprintf(arq,"/\n"); // Adicionado para arquivo
        break;
     case ENDFILE:
        fprintf(stdout,"EOF\n");
        fprintf(arq,"EOF\n"); // Adicionado para arquivo
        break;
     case TK_NUM:
        fprintf(stdout,"NUM\n");
        fprintf(arq,"NUM: %s\n", lexema); // Adicionado para arquivo
        break;
     case TK_ID:
        fprintf(stdout,"ID\n");
        fprintf(arq,"ID: %s\n", lexema); // Adicionado para arquivo
        break;
     case ERROR:
        fprintf(stdout,"%s\n",lexema);
        fprintf(arq,"%s\n",lexema); // Adicionado para arquivo
        break;
     case TK_ABRE_COMENTARIO:
        fprintf(stdout,"/*\n");
        fprintf(arq,"/*\n"); // Adicionado para arquivo
        break;
     case TK_FECHA_COMENTARIO:
        fprintf(stdout,"*/\n");
        fprintf(arq,"*/\n"); // Adicionado para arquivo
        break;
     case TK_COMENTARIO_LINHA:
        fprintf(stdout,"//\n");
        fprintf(arq,"//\n"); // Adicionado para arquivo
        break;
    }
}

NoArvore* novoNo (){

    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));

    novoNo->filho[0] = NULL;
    novoNo->filho[1] = NULL;
    novoNo->filho[2] = NULL;

    novoNo->irmao = NULL;

    bzero(novoNo->lexema, MAXLEXEMA);

    novoNo->linha = 0;

    novoNo->tipono = Nenhum;

    novoNo->statement = NuloDecl;

    novoNo->expressao = NuloEXP;

    return novoNo;
}

NoArvore* addIrmao(NoArvore* raiz, NoArvore* no){

    NoArvore* aux = raiz;

    if(aux == NULL){
        return NULL;
    }

    while(aux->irmao != NULL){
        aux = aux->irmao;
    }

    aux->irmao = no;

    return raiz;
}

NoArvore* addFilho(NoArvore* raiz, NoArvore* no){

    NoArvore* aux = raiz;

    int i;

    if(aux == NULL)
        return NULL;

    for (i=0; i < 3 && aux->filho[i] != NULL; i++);
    
    aux->filho[i] = no;

    return raiz;
}

void printArvore(NoArvore* raiz, FILE *arq, int num, int u){

    int i, j;
    
    if(raiz == NULL)
        return;

    fprintf(stdout, "pai  ' %s '  %d %d %d\n", raiz->lexema, raiz->tipono, raiz->statement, raiz->expressao);
    fprintf(arq, "%s\n", raiz->lexema);

    for (i=0; i < 3; i++){
        if(raiz->filho[i]){
            for(j = -1; j < num; j++){
                printf("\t");
                fprintf(arq,"\t");
            }
            printf("filho %d - ", i);
            fprintf(arq,"%d - ", i);
            
        } 
        printArvore(raiz->filho[i], arq, num +1, u+1);

    }
    if(raiz->irmao){
        for(j = 0; j < num; j++){
            printf("\t");
            fprintf(arq,"\t");
        }
        printf("irmao %d ", num);
        printArvore(raiz->irmao, arq, num, u);
    }
}