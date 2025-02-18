#ifndef _UTIL_H_
#define _UTIL_H_

void printToken( TokenType, const char* );

NoArvore* novoNo ();
NoArvore* addFilho(NoArvore*, NoArvore*);
NoArvore* addIrmao(NoArvore*, NoArvore*);
NoArvore* parse(void);

void printArvore(NoArvore*, int);

#endif