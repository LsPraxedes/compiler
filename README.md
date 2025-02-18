# Compilador - Gramática e Tokens

Este repositório contém a implementação de um compilador para a linguagem C- (c menos) utilizando Flex e Bison. Abaixo estão a gramática utilizada e os lexemas/tokens aceitos.

## Gramática

```
programa -> declaracao_lista

declaracao-lista -> declaracao-lista declaracao | declaracao

declaracao -> var-declaracao | fun-declaracao

var-declaracao -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;

tipo-especificador -> int | void

fun-declaracao -> tipo-especificador ID ( params ) composto-decl

params -> param-list | void

param-lista -> param-lista, param | param

param -> tipo-especificador ID | tipo-especificador ID []

composto-decl -> { local-declaracoes statement-lista }

local-declaracoes -> local-declaracoes var-declaracao | vazio

statement-list -> statement-lista statement | vazio

statement -> expressao-decl | composto-decl | selecao-decl | iteracao-decl | retorno-decl

expressao-decl -> expressao ; | ;

selecao-decl -> if (expressao) statement | if (expressao) statement else statement

iteracao-decl -> while (expressao) statement

retorno-decl -> return ; | return expressao ;

expressao -> var = expressao | simples-expressao

var -> ID | ID [ expressao ]

simples-expressao -> soma-expressao relacional soma-expressao | soma-expressao

relacional -> <= | < | > | >= | == | !=

soma-expressao -> soma-expressao soma termo | termo

soma -> + | -

termo -> termo mult fator | fator

mult -> * | /

fator -> ( expressao ) | var | ativacao | NUM

ativacao -> ID ( args )

args -> arg-lista | vazio

arg-lista -> arg-lista, expressao | expressao
```

## Lexemas/Tokens Aceitos

```
if
else
,
;
(
)
{
}
[
]
+
-
*
/
<
>
<=
>=
=
==
!=
/*
*/
ID
NUM
int
return
void
while
ERROR
ENDFILE
```

## Como Executar

Para compilar utilize o comando abaixo:

```sh
make
```

Para rodar o compilador use o comando:

```sh
./compilador {arquivoEntrada}
```

Para limpar os arquivos gerados:

```sh
make clean
```