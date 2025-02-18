%{

#define YYPARSER

#include "global.h"
#include "flex.h"
#include "util.h"

#define YYSTYPE NoArvore*
#define MAX_NOS 1000

static int yylex();

extern int linha;

int yyerror(char *message);

NoArvore AST;

char auxLexema[MAXLEXEMA];
PONTEIRONO nos[MAX_NOS];
int qntNos = 0;

%}

%start programa
%token TK_IF
%token TK_ELSE
%token TK_VIRGULA
%token TK_PONTO_VIRGULA
%token TK_ABRE_PARENTESES
%token TK_FECHA_PARENTESES
%token TK_ABRE_CHAVES
%token TK_FECHA_CHAVES
%token TK_ABRE_COLCHETES
%token TK_FECHA_COLCHETES
%left TK_MAIS
%left TK_MENOS
%left TK_MULTIPLICACAO
%left TK_DIVISAO
%left TK_MENOR
%left TK_MAIOR
%left TK_MENOR_IGUAL
%left TK_MAIOR_IGUAL
%token TK_ATRIBUICAO
%left  TK_IGUALDADE
%left  TK_DIFERENTE
%token TK_ABRE_COMENTARIO
%token TK_FECHA_COMENTARIO
%token TK_ID
%token TK_NUM
%token TK_INT
%token TK_RETORNO
%token TK_VOID
%token TK_WHILE
%token ERROR


%%

programa : declaracao_lista {
            AST = $1;
        };

declaracao_lista : declaracao_lista declaracao  {
                    if ($1 != NULL){
                        $$ = $1;
                        addIrmao($$, $2);
                    } 
                    else {
                        $$ = $2;
                    }
                    }
    | declaracao {$$ = $1;}
    ;

declaracao  : var_declaracao {$$ = $1;}
            | fun_declaracao {$$ = $1;}
            ;

var_declaracao  : tipo_especificador TK_ID TK_PONTO_VIRGULA {
                    $$ = $1;
                    $$->tipono = Statement;
                    $$->statement = DeclVarT;
                    $$->linha = linhas;

                    NoArvore* aux = novoNo();

                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                    addFilho($$, aux);

                    nos[qntNos] = aux;
                    qntNos++;
                }
                | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_NUM TK_FECHA_COLCHETES TK_PONTO_VIRGULA {
                    $$ = $1;
                    $$->tipono = Declaracao;
                    $$->statement = DeclVetorT;
                    $$->linha = linhas;

                    NoArvore* aux = novoNo();
                    NoArvore* aux2 = novoNo();
                    
                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                    nos[qntNos] = aux;
                    qntNos++;

                    strcpy(aux2->lexema, pilha[indPilha]);
                    indPilha--;
                    
                    addFilho($$, aux2);
                    addFilho($$, aux);

                    nos[qntNos] = aux2;
                    qntNos++;
                }
                ;

tipo_especificador
    : TK_INT
    | TK_VOID
    ;

fun_declaracao
    : tipo_especificador TK_ID TK_ABRE_PARENTESES params TK_FECHA_PARENTESES composto_decl
    ;

params
    : param_lista
    | TK_VOID
    ;

param_lista
    : param_lista TK_VIRGULA param
    | param
    ;

param
    : tipo_especificador TK_ID
    | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_FECHA_COLCHETES
    ;

composto_decl
    : TK_ABRE_CHAVES local_declaracoes statement_lista TK_FECHA_CHAVES
    ;

local_declaracoes
    : local_declaracoes var_declaracao
    | TK_VOID    /* cuidado: isso permite um 'void' literal no código */
    ;

statement_lista
    : statement_lista statement
    | TK_VOID     /* idem */
    ;

statement
    : expressao_decl
    | composto_decl
    | selecao_decl
    | iteracao_decl
    | retorno_decl
    ;

expressao_decl
    : expressao TK_PONTO_VIRGULA
    | TK_PONTO_VIRGULA
    ;

selecao_decl
    : TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement
    | TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement TK_ELSE statement
    ;

iteracao_decl   : TK_WHILE TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement {
                    $$ = novoNo();
                    strcpy($$->lexema, "WHILE");
                    $$->tipono = statement;
                    $$->linha = linhas;
                    $$->statement = WhileT;

                    addFilho($$, $3);
                    addFilho($$, $5);

                    nos[qntNos] = $$;
                    qntNos++;
                }
                ;

retorno_decl    : TK_RETORNO TK_PONTO_VIRGULA {
                    $$ = novoNo();
                    $$->tipono = Statement;
                    $$->linha = linhas;
                    $$->statement = RetornoVOIDT;
                    strcpy($$->lexema, "RetornoVOID");

                    nos[qntNos] = $$;
                    qntNos++;
                }
                | TK_RETORNO expressao TK_PONTO_VIRGULA {
                    $$ = novoNo();
                    $$->tipono = Statement;
                    $$->linha = linhas;
                    $$->statement = RetornoINTT;
                    strcpy($$->lexema, "RetornoINT");

                    addFilho($$, $2);

                    nos[qntNos] = $$;
                    qntNos++;
                }
                ;

expressao   : var TK_ATRIBUICAO expressao {
                $$ = novoNo();
                strcpy($$->lexema, "=");
                $$-tipono = Expressao;
                $$->linha = linhas;
                $$->expressao = AtribuicaoT;
            
                addFilho($$, $1);
                addFilho($$, $3);

                nos[qntNos] = $$;
                qntNos++;
            }
            | simples_expressao {
                $$ = $1;

            }
            ;

var : TK_ID {
        $$ = novoNo();
        $$->tipono = Expressao;
        $$->linha = linhas;
        $$->expressao = IdT;

        strcpy($$->lexema, pilha[indPilha]);

        indPilha--;
        nos[qntNos] = $$;
        qntNos++;

    }
    | TK_ID TK_ABRE_COLCHETES expressao TK_FECHA_COLCHETES {
        $$ = novoNo();
        $$->tipono = Expressao;
        $$->linha = linhas;
        $$->expressao = VetorParamT;

        strcpy($$->lexema, pilha[indPilha]);
        indPilha--;

        addFilho($$, $3);

        nos[qntNos] = $$;
        qntNos++;
    }
    ;

simples_expressao   : soma_expressao relacional soma_expressao {
                        $$ = $2;
                        $$->tipo = Expressao;
                        $$->linha = linhas;
                        $$->expressao = OperadorRelacionalT;

                        addFilho($$, $1);
                        addFilho($$, $3);
                    }
                    | soma_expressao {
                        $$ = $1;
                    }
                    ;

relacional  : TK_MENOR_IGUAL {
                $$ = novoNo();
                strcpy($$->lexema, "<=");

                nos[qntNos] = $$;
                qntNos++;
            }
            | TK_MENOR {
                $$ = novoNo();
                strcpy($$->lexema, "<");

                nos[qntNos] = $$;
                qntNos++;
            }
            | TK_MAIOR {
                $$ = novoNo();
                strcpy($$->lexema, ">");

                nos[qntNos] = $$;
                qntNos++;
            }
            | TK_MAIOR_IGUAL {
                $$ = novoNo();
                strcpy($$->lexema, ">=");

                nos[qntNos] = $$;
                qntNos++;
            }
            | TK_IGUALDADE {
                $$ = novoNo();
                strcpy($$->lexema, "==");

                nos[qntNos] = $$;
                qntNos++;
            }
            | TK_DIFERENTE {
                $$ = novoNo();
                strcpy($$->lexema, "!=");

                nos[qntNos] = $$;
                qntNos++;
            }
            ;

soma_expressao  : soma_expressao soma termo {
                    $$ = $2;
                    $$->tipono = Expressao;
                    $$->linha = linhas;
                    $$->expressao = OperandoT;

                    addFilho($$ = $1);
                    addFilho($$ = $3);
                }
                | termo {
                    $$ = $1;
                }
                ;

soma    : TK_MAIS {
            $$ = novoNo();
            strcpy($$->lexema, "+");

            nos[qntNos] = $$;
            qntNos++;
        }
        | TK_MENOS {
            $$ = novoNo();
            strcpy($$->lexema, "-");

            nos[qntNos] = $$;
            qntNos++;
        }
        ;

termo   : termo mult fator {
            $$ = $2;
            $$->tipono = Expressao;
            $$->linha = linhas;
            $$->expressao = OperandoT;

            addFilho($$, $1);
            addFilho($$, $3);
        }
        | fator {
            $$ = $1;
        }
        ;

mult    : TK_MULTIPLICACAO {
            $$ = novoNo();
            strcpy($$->lexema, "*");
        
            nos[qntNos] = $$;
            qntNos++;
        }
        | TK_DIVISAO {
            $$ = novoNo();
            strcpy($$->lexema, "/");

            nos[qntNos] = $$;
            qntNos++;
        }
        ;

fator   : TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES {
            $$ = $2;
        }
        | var {
            $$ = $1;
        }
        | ativacao {
            $$ = $1;
        }
        | TK_NUM {
            $$ = novoNO();
            $$->tipono = Expressao;
            $$->linha = linhas;
            $$->expressao = ContanteT;

            strcpy($$->lexema, pilha[indPilha]);
                        indPilha--;

                        nos[qntNos] = $$;
                        qntNos++;
        }
        ;

ativacao    : TK_ID TK_ABRE_PARENTESES args TK_FECHA_PARENTESES {
                $$ = $1;
                $$->tipono = Expressao;
                $$->linha = linhas;
                $$->expressao = FunCallT;
                addFilho($$, $3);
            }
            ;

args    : arg_lista {
            $$ = $1;
        }
        | TK_VOID {
            %empty {$$ = NULL;}
        }
        ;

arg_lista   : arg_lista TK_VIRGULA expressao {
                if($1 != NULL){
                    $$ = $1;
                    addIrmao($$, $3);
                } else {
                    $$ = $3;
                }
            }
            | expressao {
                $$ = $1;
            }
            ;

%%

int yyerror(char *message) {

    if (yychar == -2) return 0;

    Error = TRUE;

    if (yychar == ERROR)
        printf("Erro léxico na linha %d. Lexema: ", linha);
    else
        printf("Erro sintático na linha %d. Token: ", linha);


    switch (yychar) {
        case TK_IF: printf("%s\n", lexema); break;
        case TK_ELSE: printf("%s\n", lexema); break;
        case TK_VIRGULA: printf("%s\n", lexema); break;
        case TK_PONTO_VIRGULA: printf("%s\n", lexema); break;
        case TK_ABRE_PARENTESES: printf("%s\n", lexema); break;
        case TK_FECHA_PARENTESES: printf("%s\n", lexema); break;
        case TK_ABRE_CHAVES: printf("%s\n", lexema); break;
        case TK_FECHA_CHAVES: printf("%s\n", lexema); break;
        case TK_ABRE_COLCHETES: printf("%s\n", lexema); break;
        case TK_FECHA_COLCHETES: printf("%s\n", lexema); break;
        case TK_MAIS: printf("%s\n", lexema); break;
        case TK_MENOS: printf("%s\n", lexema); break;
        case TK_MULTIPLICACAO: printf("%s\n", lexema); break;
        case TK_DIVISAO: printf("%s\n", lexema); break;
        case TK_MENOR: printf("%s\n", lexema); break;
        case TK_MAIOR: printf("%s\n", lexema); break;
        case TK_MENOR_IGUAL: printf("%s\n", lexema); break;
        case TK_MAIOR_IGUAL: printf("%s\n", lexema); break;
        case TK_ATRIBUICAO: printf("%s\n", lexema); break;
        case TK_IGUALDADE: printf("%s\n", lexema); break;
        case TK_DIFERENTE: printf("%s\n", lexema); break;
        case TK_ABRE_COMENTARIO: printf("%s\n", lexema); break;
        case TK_FECHA_COMENTARIO: printf("%s\n", lexema); break;
        case TK_ID: printf("%s\n", lexema); break;
        case TK_NUM: printf("%s\n", lexema); break;
        case TK_INT: printf("%s\n", lexema); break;
        case TK_RETORNO: printf("%s\n", lexema); break;
        case TK_VOID: printf("%s\n", lexema); break;
        case TK_WHILE: printf("%s\n", lexema); break;
        case ERROR: printf("%s\n", lexema); break;
        default: printf("Token desconhecido: %d\n", yychar);
    }

    return 0;
}

static int yylex(void) {
    return getToken();
}