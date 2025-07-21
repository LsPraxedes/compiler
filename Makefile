# Compilador e flags
CC = gcc
CFLAGS = -g
LEX = flex
YACC = bison -d

# Diretórios
SRC_DIR = src
FLEX_DIR = FLEX
YACC_DIR = YACC

# Arquivos
LEXER = $(FLEX_DIR)/lexer.l
LEXER_C = $(FLEX_DIR)/lex.yy.c

PARSER = $(YACC_DIR)/parser.y
PARSER_C = $(YACC_DIR)/parser.tab.c
PARSER_H = $(YACC_DIR)/parser.tab.h

SRC_FILES = main.c $(SRC_DIR)/util.c $(SRC_DIR)/tabelaSimbolos.c $(SRC_DIR)/codigoIntermediario.c $(SRC_DIR)/quadruplas.c  $(SRC_DIR)/assembler.c $(SRC_DIR)/binario.c
OBJ_FILES = $(LEXER_C) $(PARSER_C) $(SRC_FILES)

# Executável final
EXEC = compilador

all: $(EXEC)

# Geração do parser com Bison
$(PARSER_C) $(PARSER_H): $(PARSER)
	$(YACC) -o $(PARSER_C) $(PARSER)

# Geração do analisador léxico com Flex
$(LEXER_C): $(LEXER) $(PARSER_H)
	$(LEX) -o $(LEXER_C) $(LEXER)

# Compilação do compilador
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ_FILES) -lfl

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC) $(LEXER_C) $(PARSER_C) $(PARSER_H)
