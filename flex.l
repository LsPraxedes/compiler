%{

    #include "global.h"
    #include "flex.h"
    #include "util.h"

    char lexema[MAXTOKENLEN+1];
    char ultimoLexema[MAXTOKENLEN+1];

    extern int yylex(void);


    static int firstTime = TRUE;
    int indPilha = -1;
    char pilha[4][MAXLEXEMA];
%}

%option noyywrap

TAB [\t]
NEWLINE [\n]
LETTER [a-zA-Z]
DIGIT [0-9]

%%

"if"      { fprintf(yyout, "TK_IF "); return TK_IF; }
"else"    { fprintf(yyout, "TK_ELSE "); return TK_ELSE; }
"int"     { fprintf(yyout, "TK_INT "); return TK_INT; }
"return"  { fprintf(yyout, "TK_RETORNO "); return TK_RETORNO; }
"void"    { fprintf(yyout, "TK_VOID "); return TK_VOID; }
"while"   { fprintf(yyout, "TK_WHILE "); return TK_WHILE; }

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

<<EOF>> { return ENDFILE; }

({LETTER}|{DIGIT})+ { fprintf(yyout, "ERROR(%s) ", yytext); return ERROR; }

{NEWLINE}   {linha++;}

{TAB}+ { }

[ ]* { }

.         { fprintf(yyout, "ERROR(%s) ", yytext); return ERROR; }

%%

TokenType getToken(void) { 

    TokenType currentToken;
    
    if (firstTime) {
        
        firstTime = FALSE;
        yyin = source;

        for (int i = 0; i < 5; i++)
            bzero(pilha[i], MAXLEXEMA);	
    }

    if (!firstTime)
        strcpy(ultimoLexema, lexema);
    
    currentToken = yylex();
    
    strncpy(lexema,yytext,MAXTOKENLEN);
    
    fprintf(stdout,"\t%d: ",linha);
    printToken(currentToken,lexema);

    return currentToken;
}