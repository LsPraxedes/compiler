#ifndef _FLEX_H_
#define _FLEX_H_


#define MAXTOKENLEN 40

/* tokenString é o array que armazena o lexema de cada token */
/*tokenString virou lexema*/
extern char lexema[MAXTOKENLEN+1];
extern char id[MAXTOKENLEN+1];
extern char func[MAXTOKENLEN+1];


TokenType getToken(void);


#endif