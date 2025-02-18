#include "global.h"
#include "flex.h"
#include "util.h"
#include "parser.h"
#include "tabelaSimbolos.h"

int Error = FALSE;

int linha = 1;
int linhas = 1;

FILE * source;

int main(int argc, char **argv){

    NoArvore* AST;
    SimboloTabela** tabela = criarTabela();
    
    char escopo[MAXLEXEMA] = "global";
    char nomeInput[120];
    
    if(argc != 2){
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        exit(1);
    }
    
    strcpy(nomeInput, argv[1]);
    source = fopen(nomeInput, "r");

    AST = parse();

    if (AST == NULL)
        fprintf(stdout, "ERRO NA GERAÇÃO DA AST.\n");

    else {
        fprintf(stdout, "\nAST:\n\n");
        printArvore(AST, 0);
    }

    percorrerArvore(AST, tabela, escopo);
    printTabela(tabela);
        
    return 0;
}
