#include "headers/global.h"
#include "headers/lexer.h"
#include "headers/util.h"
#include "headers/parser.h"
#include "headers/tabelaSimbolos.h"
#include "headers/codigoIntermediario.h"

int Error = FALSE;

int linha = 1;

FILE * source;

int main(int argc, char **argv){

    teveErroSemantico = 0;

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

    if (AST == NULL) {
        fprintf(stdout, "ERRO NA GERAÇÃO DA AST. Encerrando o programa.\n");
        return -1;
    }

    else {
        fprintf(stdout, "\nAST:\n\n");
        printArvore(AST, 0);
    }

    printf("\nFIM_ANALISE_SINTATICA\n------------------------------------------\nINICIO_ANALISE_SEMANTICA\n\n");

    inserirSimbolo(tabela, "input", "global", DeclFuncT, TIPO_INT, 0);
    inserirSimbolo(tabela, "output", "global", DeclFuncT, TIPO_VOID, 0);

    percorrerArvore(AST, tabela, escopo);
    
    if (verificarMain(tabela) == -1 ){
        printf("Encerrando o programa...\n");
        return 1;
    }

    printTabela(tabela);
    if (teveErroSemantico > 0)
        printf("Foram encontrados %d erro(s) semântico(s).\n", teveErroSemantico);
    else {
        printf("Análise semântica concluída sem erros.\n");
        gerarCodigoIntermediario(AST);   // Gera o código intermediário
        imprimirCodigoIntermediario(); 
    }

    return 0;
}