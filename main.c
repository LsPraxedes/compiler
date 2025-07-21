#include "headers/global.h"
#include "headers/lexer.h"
#include "headers/util.h"
#include "headers/parser.h"
#include "headers/tabelaSimbolos.h"
#include "headers/codigoIntermediario.h"
#include "headers/quadruplas.h"
#include "headers/assembler.h"
#include "headers/binario.h"

int Error = FALSE;

int linha = 1;

FILE * source;

int main(int argc, char **argv){

    teveErroSemantico = 0;

    NoArvore* AST;
    SimboloTabela** tabela = criarTabela();
    tempTab** ttabela = criarTempTabela();

    char escopo[MAXLEXEMA] = "global";
    char nomeInput[120];
    printf("------------------------------------------\nINICIO_ANALISE_SINTATICA\n\n");
    FILE *arq;
    char* nomeArq = "outputs/AST.txt";
    arq = fopen(nomeArq, "w");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo"); // Mostra a mensagem de erro do sistema
    exit(EXIT_FAILURE); // Encerra o programa com código de erro
    }

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
        printArvore(AST, arq, 0, 0);
        fclose(arq);
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
        gerarQuadruplas(ttabela, AST, "global");   // Gera o código intermediário
        adicionarQuadruplas("(HALT, -, -, -)");
        imprimirQuadruplas(); 
        printTTabela(ttabela);
        processaQuadruplas(); // Processa as quadruplas geradas
        processaAssembly();
    }



    return 0;
}