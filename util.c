#include "global.h"
#include "util.h"

void printToken( TokenType token, const char* lexema ) { switch (token)
   { case TK_IF:   fprintf(listing,"%s\n",lexema);break;
     case TK_RETORNO:  fprintf(listing,"%s\n",lexema);break;
     case TK_ELSE: fprintf(listing,"%s\n",lexema);break;
     case TK_INT:  fprintf(listing,"%s\n",lexema);break;
     case TK_WHILE:  fprintf(listing,"%s\n",lexema);break;
     case TK_VOID: fprintf(listing,"%s\n",lexema);break;
     case TK_IGUALDADE: fprintf(listing,"==\n"); break;
     case TK_ATRIBUICAO: fprintf(listing,"=\n"); break;
     case TK_DIFERENTE: fprintf(listing,"!=\n"); break;
     case TK_MENOR: fprintf(listing,"<\n"); break;
     case TK_MAIOR: fprintf(listing,">\n"); break;
     case TK_MENOR_IGUAL: fprintf(listing,"<=\n"); break;
     case TK_MAIOR_IGUAL: fprintf(listing,">=\n"); break;
     case TK_ABRE_PARENTESES: fprintf(listing,"(\n"); break;
     case TK_FECHA_PARENTESES: fprintf(listing,")\n"); break;
     case TK_ABRE_COLCHETES: fprintf(listing,"[\n"); break;
     case TK_FECHA_COLCHETES: fprintf(listing,"]\n"); break;
     case TK_ABRE_CHAVES: fprintf(listing,"{\n"); break;
     case TK_FECHA_CHAVES: fprintf(listing,"}\n"); break;
     case TK_PONTO_VIRGULA: fprintf(listing,";\n"); break;
     case TK_VIRGULA: fprintf(listing,",\n"); break;
     case TK_MAIS: fprintf(listing,"+\n"); break;
     case TK_MENOS: fprintf(listing,"-\n"); break;
     case TK_MULTIPLICACAO: fprintf(listing,"*\n"); break;
     case TK_DIVISAO: fprintf(listing,"/\n"); break;
    //  case FIM: fprintf(listing,"EOF\n"); break;
     case TK_NUM: fprintf(listing,"NUM, val = %s\n",lexema);break;
     case TK_ID:  fprintf(listing,"ID, nome = %s\n",lexema);break;
     case ERROR:  fprintf(listing,"%s\n",lexema); break;
     default: /* Nunca deve acontecer */
       fprintf(listing,"Token Desconhecido: %d\n",token);
   }
}
