#include "global.h"
#include "flex.h"

int lineno = 1;

FILE * source;
FILE * listing;


int Error = FALSE;

int main(int argc, char **argv){

    char nomeInput[120];

    if(argc != 2){
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        exit(1);
    }

    strcpy(nomeInput, argv[1]);

    source = fopen(nomeInput, "r");
    listing = stdout;

    while (getToken() != ENDFILE);
    
    return 0;
}
