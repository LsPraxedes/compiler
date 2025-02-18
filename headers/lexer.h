#ifndef _FLEX_H_
#define _FLEX_H_

#define MAXTOKENLEN 40

extern char lexema[MAXTOKENLEN+1];
extern char ultimoLexema[MAXTOKENLEN+1];

TokenType getToken(void);


#endif