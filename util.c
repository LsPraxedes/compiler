#include "global.h"
#include "util.h"

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
    //  case FIM: fprintf(stdout,"EOF\n"); break;
     case TK_NUM: fprintf(stdout,"NUM, val = %s\n",lexema);break;
     case TK_ID:  fprintf(stdout,"ID, nome = %s\n",lexema);break;
     case ERROR:  fprintf(stdout,"%s\n",lexema); break;
     default: /* Nunca deve acontecer */
       fprintf(stdout,"Token Desconhecido: %d\n",token);
   }
}
