/* Lexical Analyzer for C- */

%{     
#include <stdio.h>
#include <stdlib.h>

// =====================Definição dos Tokens===================== //
// Palavras-chave
#define TK_ELSE
#define TK_IF
#define TK_INT
#define TK_RETORNO
#define TK_VOID
#define TK_WHILE
#define TK_ID
#define TK_NUM

// Símbolos Especiais
#define TK_MAIS            // +
#define TK_MENOS           // -
#define TK_MULTIPLICACAO   // *
#define TK_DIVISAO         // /
#define TK_MENOR           // <
#define TK_MENOR_IGUAL     // <=
#define TK_MAIOR           // >
#define TK_MAIOR_IGUAL     // >=
#define TK_IGUALDADE       // ==
#define TK_DIFERENTE       // !=
#define TK_ATRIBUICAO      // =
#define TK_PONTO_VIRGULA   // ;
#define TK_VIRGULA         // ,
#define TK_ABRE_CHAVES     // {
#define TK_FECHA_CHAVES    // }
#define TK_ABRE_COLCHETES  // [
#define TK_FECHA_COLCHETES // ]
#define TK_ABRE_PARENTESES // (
#define TK_FECHA_PARENTESES// )
#define TK_ABRE_COMENTARIO // /*
#define TK_FECHA_COMENTARIO// */
#define ERROR              // Erro

// Variáveis Globais
int yylval; // Valor do Token
int yylineno; // Linha do Token

%}

BLANKSPACE [ \t\n]
LETTER [a-zA-Z]
DIGIT [0-9]

%%
"if"      { fprintf(yyout, "TK_IF "); return TK_IF; }
"else"    { fprintf(yyout, "TK_ELSE "); return TK_ELSE; }
"int"     { fprintf(yyout, "TK_INT "); return TK_INT; }
"return"  { fprintf(yyout, "TK_RETORNO "); return TK_RETORNO; }
"void"    { fprintf(yyout, "TK_VOID "); return TK_VOID; }
"while"   { fprintf(yyout, "TK_WHILE "); return TK_WHILE; }

{DIGIT}+ { yylval = atoi(yytext); fprintf(yyout, "TK_NUM(%d) ", yylval); return TK_NUM; }

{LETTER}+ { fprintf(yyout, "TK_ID(%s) ", yytext); return TK_ID; }

"+"       { fprintf(yyout, "+ "); return TK_MAIS; }
"-"       { fprintf(yyout, "- "); return TK_MENOS; }
"*"       { fprintf(yyout, "* "); return TK_MULTIPLICACAO; }
"/"       { fprintf(yyout, "/ "); return TK_DIVISAO; }
"<"       { fprintf(yyout, "< "); return TK_MENOR; }
"<="      { fprintf(yyout, "<="); return TK_MENOR_IGUAL; }
">"       { fprintf(yyout, "> "); return TK_MAIOR; }
">="      { fprintf(yyout, ">= "); return TK_MAIOR_IGUAL; }
"=="      { fprintf(yyout, "== "); return TK_IGUALDADE; }
"!="      { fprintf(yyout, "!= "); return TK_DIFERENTE; }
"="       { fprintf(yyout, "= "); return TK_ATRIBUICAO; }
";"       { fprintf(yyout, "; "); return TK_PONTO_VIRGULA; }
","       { fprintf(yyout, ", "); return TK_VIRGULA; }
"{"       { fprintf(yyout, "{ "); return TK_ABRE_CHAVES; }
"}"       { fprintf(yyout, "} "); return TK_FECHA_CHAVES; }
"["       { fprintf(yyout, "[ "); return TK_ABRE_COLCHETES; }
"]"       { fprintf(yyout, "] "); return TK_FECHA_COLCHETES; }
"("       { fprintf(yyout, "( "); return TK_ABRE_PARENTESES; }
")"       { fprintf(yyout, ") "); return TK_FECHA_PARENTESES; }

"/*"      { fprintf(yyout, "TK_ABRE_COMENTARIO "); return TK_ABRE_COMENTARIO; }
"*/"      { fprintf(yyout, "TK_FECHA_COMENTARIO "); return TK_FECHA_COMENTARIO; }

{BLANKSPACE}+ { fprintf(yyout, "%s", yytext); /* Ignora e Preserva Espaços em Branco e Quebras de Linha */ }


.         { fprintf(yyout, "ERROR(%s) ", yytext); return ERROR; }
%%



int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    // Abrindo o Arquivo de Entrada
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao Abrir o Arquivo de Entrada");
        return 1;
    }

    // Abrindo o Arquivo de Saída
    FILE *output = fopen("saida.txt", "w");
    if (!output) {
        perror("Erro ao Criar o Arquivo de Saída");
        fclose(file);
        return 1;
    }

    yyin = file; // Definindo o Fluxo de Entrada
    yyout = output; // Definindo o Fluxo de Saída

    while (yylex()); // Executando o Analisador Léxico

    fclose(file);
    fclose(output);

    printf("Análise Léxica Concluída. Arquivo de Saída: saida.txt\n");
    return 0;
}

int yywrap() {
    return 1;
}
