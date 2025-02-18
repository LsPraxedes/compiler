#include "global.h"
#include "flex.h"
#include "util.h"
#include "parser.h"

int linha = 1;

int linhas = 1;

extern void yylex_destroy(void);


FILE * source;

int Error = FALSE;

int main(int argc, char **argv){

    NoArvore* AST;
    char nomeInput[120];

    if(argc != 2){
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        exit(1);
    }

    strcpy(nomeInput, argv[1]);

    source = fopen(nomeInput, "r");

    // while (getToken() != ENDFILE);

    // fprintf(stdout, "\n\n\n");

    AST = parse();

    if (AST == NULL) {
        fprintf(stdout, "ERRO NA GERAÇÃO DA AST.\n");
    } else {
        fprintf(stdout, "\nAST:\n");
        printArvore(AST, 0);
    }

    return 0;
}
