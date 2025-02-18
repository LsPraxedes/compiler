#include "global.h"
#include "flex.h"

int linha = 1;

FILE * source;

int Error = FALSE;

int main(int argc, char **argv){

    char nomeInput[120];

    if(argc != 2){
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        exit(1);
    }

    strcpy(nomeInput, argv[1]);

    source = fopen(nomeInput, "r");

    while (getToken() != ENDFILE);
    
    return 0;
}
