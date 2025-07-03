%{

    #include "../headers/global.h"
    #include "../headers/lexer.h"
    #include "../headers/util.h"

    char lexema[MAXTOKENLEN+1];
    char ultimoLexema[MAXTOKENLEN+1];

    extern int yylex(void);


    static int firstTime = TRUE;
    int indPilha = -1;
    char pilha[4][MAXLEXEMA+1];
%}

%option noyywrap

TAB [\t]
NEWLINE [\n]
LETTER [a-zA-Z]
DIGIT [0-9]

%%

"if"      { return TK_IF; }
"else"    { return TK_ELSE; }
"int"     { return TK_INT; }
"return"  { return TK_RETORNO; }
"void"    { return TK_VOID; }
"while"   { return TK_WHILE; }

{DIGIT}{DIGIT}* { 
    
    indPilha++;
    strcpy(pilha[indPilha], yytext);
    yylval = atoi(yytext); fprintf(yyout, "TK_NUM(%d) ", yylval); return TK_NUM; 

}

{LETTER}({LETTER}|{DIGIT})* { 

    indPilha++;
    bzero(pilha[indPilha], MAXLEXEMA);
    strcpy(pilha[indPilha], yytext);
    fprintf(yyout, "TK_ID(%s) ", yytext); return TK_ID; 

}

"+"       { return TK_MAIS; }
"-"       { return TK_MENOS; }
"*"       { return TK_MULTIPLICACAO; }
"/"       { return TK_DIVISAO; }
"<"       { return TK_MENOR; }
"<="      { return TK_MENOR_IGUAL; }
">"       { return TK_MAIOR; }
">="      { return TK_MAIOR_IGUAL; }
"=="      { return TK_IGUALDADE; }
"!="      { return TK_DIFERENTE; }
"="       { return TK_ATRIBUICAO; }
";"       { return TK_PONTO_VIRGULA; }
","       { return TK_VIRGULA; }
"{"       { return TK_ABRE_CHAVES; }
"}"       { return TK_FECHA_CHAVES; }
"["       { return TK_ABRE_COLCHETES; }
"]"       { return TK_FECHA_COLCHETES; }
"("       { return TK_ABRE_PARENTESES; }
")"       { return TK_FECHA_PARENTESES; }
"/*"      { return TK_ABRE_COMENTARIO; }
"*/"      { return TK_FECHA_COMENTARIO; }
"//"      { return TK_COMENTARIO_LINHA; }

<<EOF>> { return ENDFILE; }

({LETTER}|{DIGIT})+ { fprintf(yyout, "ERROR(%s) ", yytext); return ERROR; }

{NEWLINE}   {linha++;}

{TAB}+ { }

[ ]* { }

.         { fprintf(yyout, "ERROR(%s) ", yytext); return ERROR; }

%%

TokenType getToken(void) { 

    TokenType currentToken;
    FILE *arq;
    char* nomeArq = "outputs/Tokens.txt";

    if (firstTime) {
        
        firstTime = FALSE;
        yyin = source;
        for (int i = 0; i < 5; i++)
            bzero(pilha[i], MAXLEXEMA);	
        
        arq = fopen(nomeArq,"w");
    }

    if (!firstTime){
        strcpy(ultimoLexema, lexema);
        
        arq = fopen(nomeArq, "a");
        if (arq == NULL) {
            perror("Erro ao abrir o arquivo"); // Mostra a mensagem de erro do sistema
            exit(EXIT_FAILURE); // Encerra o programa com código de erro
        }
    }
    
    currentToken = yylex();
    
    strncpy(lexema,yytext,MAXTOKENLEN);
    
    fprintf(stdout,"%d: ",linha);
    fprintf(arq,"%d: ",linha);
    printToken(currentToken, arq, lexema);
    fclose(arq);
    return currentToken;
}