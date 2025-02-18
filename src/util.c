#include "../headers/global.h"
#include "../headers/util.h"

void printToken( TokenType token, const char* lexema ) { switch (token)
   { case TK_IF:   fprintf(stdout,"%s\n",lexema);break;
     case TK_RETORNO:  fprintf(stdout,"%s\n",lexema);break;
     case TK_ELSE: fprintf(stdout,"%s\n",lexema);break;
     case TK_INT:  fprintf(stdout,"%s\n",lexema);break;
     case TK_WHILE:  fprintf(stdout,"%s\n",lexema);break;
     case TK_VOID: fprintf(stdout,"%s\n",lexema);break;
     case TK_IGUALDADE: fprintf(stdout,"==\n"); break;
     case TK_ATRIBUICAO: fprintf(stdout,"=\n"); break;
     case TK_DIFERENTE: fprintf(stdout,"!=\n"); break;
     case TK_MENOR: fprintf(stdout,"<\n"); break;
     case TK_MAIOR: fprintf(stdout,">\n"); break;
     case TK_MENOR_IGUAL: fprintf(stdout,"<=\n"); break;
     case TK_MAIOR_IGUAL: fprintf(stdout,">=\n"); break;
     case TK_ABRE_PARENTESES: fprintf(stdout,"(\n"); break;
     case TK_FECHA_PARENTESES: fprintf(stdout,")\n"); break;
     case TK_ABRE_COLCHETES: fprintf(stdout,"[\n"); break;
     case TK_FECHA_COLCHETES: fprintf(stdout,"]\n"); break;
     case TK_ABRE_CHAVES: fprintf(stdout,"{\n"); break;
     case TK_FECHA_CHAVES: fprintf(stdout,"}\n"); break;
     case TK_PONTO_VIRGULA: fprintf(stdout,";\n"); break;
     case TK_VIRGULA: fprintf(stdout,",\n"); break;
     case TK_MAIS: fprintf(stdout,"+\n"); break;
     case TK_MENOS: fprintf(stdout,"-\n"); break;
     case TK_MULTIPLICACAO: fprintf(stdout,"*\n"); break;
     case TK_DIVISAO: fprintf(stdout,"/\n"); break;
     case ENDFILE: fprintf(stdout,"EOF\n"); break;
     case TK_NUM: fprintf(stdout,"NUM, val = %s\n",lexema);break;
     case TK_ID:  fprintf(stdout,"ID, nome = %s\n",lexema);break;
     case ERROR:  fprintf(stdout,"%s\n",lexema); break;
     default: /* Nunca deve acontecer */
       fprintf(stdout,"Token Desconhecido: %d\n",token);
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

void printArvore(NoArvore* raiz, int num){

    int i;
    
    if(raiz == NULL)
        return;

    fprintf(stdout,"|");
    for(i = 0; i < num; i++)
        fprintf(stdout, "----");

    fprintf(stdout, "%s\n", raiz->lexema);

    for (i=0; i < 3; i++)
        printArvore(raiz->filho[i], num +1);
    
    printArvore(raiz->irmao, num);
}