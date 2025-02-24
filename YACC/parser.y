%{
    #define YYPARSER

    #include "../headers/global.h"
    #include "../headers/lexer.h"
    #include "../headers/util.h"

    #define YYSTYPE NoArvore*
    #define MAX_NOS 1000

    static int yylex();
    extern int linha;

    int yyparse(void);
    int yyerror(char *message);

    void printArvore(NoArvore* raiz, int num);

    NoArvore* AST;
%}

%start programa
%expect 1
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
%token ENDFILE


%%

programa    : declaracao_lista {
                AST = $1;
            }
            ;

declaracao_lista    : declaracao_lista declaracao  {
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

declaracao  : var_declaracao {
                $$ = $1;
            }
            | fun_declaracao {
                $$ = $1;
            }
            ;

var_declaracao  : tipo_especificador TK_ID TK_PONTO_VIRGULA {
                    $$ = $1;
                    $$->tipono = Statement;
                    $$->statement = DeclVarT;
                    $$->linha = linha;

                    NoArvore* aux = novoNo();

                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                    addFilho($$, aux);

                    
                }
                | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_NUM TK_FECHA_COLCHETES TK_PONTO_VIRGULA {
                    $$ = $1;
                    $$->tipono = Statement;
                    $$->statement = DeclVetorT;
                    $$->linha = linha;

                    NoArvore* aux = novoNo();
                    NoArvore* aux2 = novoNo();
                    
                    strcpy(aux->lexema, pilha[indPilha]);
                    indPilha--;

                   

                    strcpy(aux2->lexema, pilha[indPilha]);
                    indPilha--;
                    
                    addFilho($$, aux2);
                    addFilho($$, aux);

                    
                }
                ;

tipo_especificador  : TK_INT {
                        $$ = novoNo();
                        strcpy($$->lexema, "INT");
                        $$->linha = linha;

                        
                    }
                    | TK_VOID {
                        $$ = novoNo();
                        strcpy($$->lexema, "VOID");
                        $$->linha = linha;

                        
                    }
                    ;

fun_declaracao  : tipo_especificador fun_id TK_ABRE_PARENTESES params TK_FECHA_PARENTESES composto_decl {
                    $$ = $1;

                    addFilho($$, $4);
                    addFilho($$, $2);
                    addFilho($2, $6);
                    
                    $$->tipono = Statement;
                    $$->statement = DeclFuncT;
                }
                ;

fun_id  : TK_ID {
            $$ = novoNo();
                        
            strcpy($$->lexema, pilha[indPilha]);
            indPilha--;

            $$->linha = linha;

            
        }

params  : %empty {
            $$ = novoNo();
        }
        |
        param_lista {
            $$ = $1;
        }
        | TK_VOID {
            $$ = novoNo();
            $$->tipono = Statement;
            $$->linha = linha;
            $$->statement = ParametroVOIDT;
            strcpy($$->lexema, "VOID");

            
        }
        ;

param_lista : param_lista TK_VIRGULA param {
                if($1 != NULL){
                    $$ = $1;
                    addIrmao($$, $3);
                }
                else{
                    $$ = $3;
                }	
            }
            | param {
                $$ = $1;
            }
            ;

param   : tipo_especificador TK_ID {
            $$ = $1;
            $$->tipono = Statement;
            $$->linha = linha;
            $$->statement = VarParametroT;

            NoArvore* aux = novoNo();

            strcpy(aux->lexema, pilha[indPilha]);
            indPilha--;
        
            addFilho($$, aux);

            
        }
        | tipo_especificador TK_ID TK_ABRE_COLCHETES TK_FECHA_COLCHETES {
            $$ = $1;
            $$->tipono = Statement;
            $$->linha = linha;
            $$->statement = VetorParametroT;
            NoArvore* aux = novoNo();


            strcpy(aux->lexema, pilha[indPilha]);
            indPilha--;

            addFilho($$, aux);		

            
        }
        ;

composto_decl   : TK_ABRE_CHAVES local_declaracoes statement_lista TK_FECHA_CHAVES {
                    if($2 != NULL) {
                        $$ = $2;
                        addIrmao($$, $3);
                    } else {
                        $$ = $3;
                    }
                }
                ;

local_declaracoes   : local_declaracoes var_declaracao {
                        if($1 != NULL) {
                            $$ = $1;
                            addIrmao($$, $2);
                        } else {
                            $$ = $2;
                        }
                    }
                    | %empty {
                        $$ = NULL;
                    }
                    ;

statement_lista : statement_lista statement {
                    if($1 != NULL) {
                        $$ = $1;
                        addIrmao($$, $2);
                    } else {
                        $$ = $2;
                    }
                }
                | %empty {
                    $$ = NULL;
                }
                ;

statement   : expressao_decl {
                $$ = $1;
            }
            | composto_decl {
                $$ = $1;
            }
            | selecao_decl {
                $$ = $1;
            }
            | iteracao_decl {
                $$ = $1;
            }
            | retorno_decl {
                $$ = $1;
            }
            ;

expressao_decl  : expressao TK_PONTO_VIRGULA {
                    $$ = $1;
                }
                | TK_PONTO_VIRGULA {
                    $$ = NULL;
                }
                ;

selecao_decl    : TK_IF TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement fatoracao{
                    $$ = novoNo();
                    strcpy($$->lexema, "IF");
                    $$->tipono = Statement;
                    $$->linha = linha;
                    $$->statement = IfT;

                    addFilho($$, $5);		
                    addFilho($$, $3);
                    if($6 != NULL){
                        addFilho($$, $6);
                    }

                    
                }
                ;

fatoracao   : TK_ELSE statement {
                $$ = $2;
            }
            | %empty {
                $$ = NULL;
            }
            ;

iteracao_decl   : TK_WHILE TK_ABRE_PARENTESES expressao TK_FECHA_PARENTESES statement {
                    $$ = novoNo();
                    strcpy($$->lexema, "WHILE");
                    $$->tipono = Statement;
                    $$->linha = linha;
                    $$->statement = WhileT;

                    addFilho($$, $3);
                    addFilho($$, $5);

                    
                }
                ;

retorno_decl    : TK_RETORNO TK_PONTO_VIRGULA {
                    $$ = novoNo();
                    $$->tipono = Statement;
                    $$->linha = linha;
                    $$->statement = RetornoVOIDT;
                    strcpy($$->lexema, "RetornoVOID");

                    
                }
                | TK_RETORNO expressao TK_PONTO_VIRGULA {
                    $$ = novoNo();
                    $$->tipono = Statement;
                    $$->linha = linha;
                    $$->statement = RetornoINTT;
                    strcpy($$->lexema, "RetornoINT");

                    addFilho($$, $2);

                    
                }
                ;

expressao   : var TK_ATRIBUICAO expressao {
                $$ = novoNo();
                strcpy($$->lexema, "=");
                $$->tipono = Expressao;
                $$->linha = linha;
                $$->expressao = AtribuicaoT;
            
                addFilho($$, $1);
                addFilho($$, $3);

                
            }
            | simples_expressao {
                $$ = $1;

            }
            ;

var : TK_ID {
        $$ = novoNo();
        $$->tipono = Expressao;
        $$->linha = linha;
        $$->expressao = IdT;

        strcpy($$->lexema, pilha[indPilha]);

        indPilha--;
        

    }
    | TK_ID TK_ABRE_COLCHETES expressao TK_FECHA_COLCHETES {
        $$ = novoNo();
        $$->tipono = Expressao;
        $$->linha = linha;
        $$->expressao = VetorParamT;

        strcpy($$->lexema, pilha[indPilha]);
        indPilha--;

        addFilho($$, $3);

        
    }
    ;

simples_expressao   : soma_expressao relacional soma_expressao {
                        $$ = $2;
                        $$->tipono = Expressao;
                        $$->linha = linha;
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

                
            }
            | TK_MENOR {
                $$ = novoNo();
                strcpy($$->lexema, "<");

                
            }
            | TK_MAIOR {
                $$ = novoNo();
                strcpy($$->lexema, ">");

                
            }
            | TK_MAIOR_IGUAL {
                $$ = novoNo();
                strcpy($$->lexema, ">=");

                
            }
            | TK_IGUALDADE {
                $$ = novoNo();
                strcpy($$->lexema, "==");

                
            }
            | TK_DIFERENTE {
                $$ = novoNo();
                strcpy($$->lexema, "!=");

                
            }
            ;

soma_expressao  : soma_expressao soma termo {
                    $$ = $2;
                    $$->tipono = Expressao;
                    $$->linha = linha;
                    $$->expressao = OperandoT;

                    addFilho($$, $1);
                    addFilho($$, $3);
                }
                | termo {
                    $$ = $1;
                }
                ;

soma    : TK_MAIS {
            $$ = novoNo();
            strcpy($$->lexema, "+");

            
        }
        | TK_MENOS {
            $$ = novoNo();
            strcpy($$->lexema, "-");

            
        }
        ;

termo   : termo mult fator {
            $$ = $2;
            $$->tipono = Expressao;
            $$->linha = linha;
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
        
            
        }
        | TK_DIVISAO {
            $$ = novoNo();
            strcpy($$->lexema, "/");

            
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
            $$ = novoNo();
            $$->tipono = Expressao;
            $$->linha = linha;
            $$->expressao = ConstanteT;

            strcpy($$->lexema, pilha[indPilha]);
            indPilha--;

                        
        }
        ;

ativacao    : fun_id TK_ABRE_PARENTESES args TK_FECHA_PARENTESES {
                $$ = $1;
                $$->tipono = Expressao;
                $$->linha = linha;
                $$->expressao = FunCallT;
                addFilho($$, $3);
            }
            ;

args    : arg_lista {
            $$ = $1;
        }
        | %empty {
            $$ = NULL;
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

    if (yychar == -2) 
        return 0;

    Error = TRUE;

    if (yychar == ERROR)
        printf("Erro léxico na linha %d. Lexema: ", linha);
    else
        printf("Erro sintático na linha %d. Token: ", linha-1);

    switch (yychar) {

        case TK_IF: printf("%s\n", ultimoLexema); break;
        case TK_ELSE: printf("%s\n", ultimoLexema); break;
        case TK_VIRGULA: printf("%s\n", ultimoLexema); break;
        case TK_PONTO_VIRGULA: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_PARENTESES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_PARENTESES: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_CHAVES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_CHAVES: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_COLCHETES: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_COLCHETES: printf("%s\n", ultimoLexema); break;
        case TK_MAIS: printf("%s\n", ultimoLexema); break;
        case TK_MENOS: printf("%s\n", ultimoLexema); break;
        case TK_MULTIPLICACAO: printf("%s\n", ultimoLexema); break;
        case TK_DIVISAO: printf("%s\n", ultimoLexema); break;
        case TK_MENOR: printf("%s\n", ultimoLexema); break;
        case TK_MAIOR: printf("%s\n", ultimoLexema); break;
        case TK_MENOR_IGUAL: printf("%s\n", ultimoLexema); break;
        case TK_MAIOR_IGUAL: printf("%s\n", ultimoLexema); break;
        case TK_ATRIBUICAO: printf("%s\n", ultimoLexema); break;
        case TK_IGUALDADE: printf("%s\n", ultimoLexema); break;
        case TK_DIFERENTE: printf("%s\n", ultimoLexema); break;
        case TK_ABRE_COMENTARIO: printf("%s\n", ultimoLexema); break;
        case TK_FECHA_COMENTARIO: printf("%s\n", ultimoLexema); break;
        case TK_ID: printf("%s\n", ultimoLexema); break;
        case TK_NUM: printf("%s\n", ultimoLexema); break;
        case TK_INT: printf("%s\n", ultimoLexema); break;
        case TK_RETORNO: printf("%s\n", ultimoLexema); break;
        case TK_VOID: printf("%s\n", ultimoLexema); break;
        case TK_WHILE: printf("%s\n", ultimoLexema); break;
        case ERROR: printf("%s\n", ultimoLexema); break;
        case ENDFILE: printf("\n"); break;

        default: printf("Token desconhecido: %d\n", yychar);
    }

    return 0;
}

static int yylex(void) {
    return getToken();
}

NoArvore* parse(void) {
    yyparse();
    return AST;
}