#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/global.h"

#define MAX_LABELS 100
#define MAX_LABEL_LEN 32

typedef struct {
    char label[MAX_LABEL_LEN];
    int line;
} LabelInfo;

#define MAX_FUNCS 100

typedef struct {
    char name[MAX_LABEL_LEN];
    int line;
} FuncInfo;

FuncInfo funcTable[MAX_FUNCS];
int funcCount = 0;

// Chame esta função durante a 1ª passagem, ao encontrar FUNC
void adicionarFuncao(const char* name, int line) {
    if (funcCount < MAX_FUNCS) {
        strncpy(funcTable[funcCount].name, name, MAX_LABEL_LEN-1);
        funcTable[funcCount].name[MAX_LABEL_LEN-1] = '\0';
        funcTable[funcCount].line = line;
        funcCount++;
    }
}

int pesquisarFuncTable(const char* nome) {
    for (int i = 0; i < funcCount; i++) {
        if (strcmp(funcTable[i].name, nome) == 0) {
            return funcTable[i].line;
        }
    }
    return -1; // Não encontrado
}

// Imprime a tabela de funções
void printFuncTable() {
    printf("\nTABELA DE FUNÇÕES\n");
    printf("===============================\n");
    printf("| %-16s   | %-6s |\n", "Função", "Linha");
    printf("===============================\n");
    for (int i = 0; i < funcCount; i++) {
        printf("| %-16s | %-6d |\n", funcTable[i].name, funcTable[i].line);
    }
    printf("===============================\n");
}

// Lista de todas as operações identificadas nas quadruplas
const char *operacoes[] = {
    "LOAD", "FUNC", "ARG", "ALLOC", "ASSIGN", "SW", "ADDI", "LAB", "SLT",
    "IFF", "SUBI", "PARAM", "CALL", "RET", "END", "GOTO", "HALT"
};
const int num_operacoes = sizeof(operacoes) / sizeof(operacoes[0]);

// Função auxiliar para mapear t0, t1, ... para r3, r4, ...
const char* reg(const char* name, char* buf) {
    if (name[0] == 't' && name[1] >= '0' && name[1] <= '9') {
        int n = atoi(name + 1);
        sprintf(buf, "r%d", 3 + n);
        return buf;
    }
    if (strcmp(name, "$sp") == 0) return "r30";
    if (strcmp(name, "$fp") == 0) return "r29";
    if (strcmp(name, "$ra") == 0) return "r31";
    if (strcmp(name, "$v0") == 0) return "r28";
    if (strcmp(name, "$zero") == 0) return "r0";
    strcpy(buf, name);
    return buf;
}
void processaQuadruplas() {
    FILE *file = fopen("outputs/Quadruplas.txt", "r");
    if (!file) {
        printf("Failed to open Quadruplas.txt\n");
        exit(EXIT_FAILURE);
    }

    FILE *assembly_file;
    char* arq = "outputs/Assembly.txt";
    assembly_file = fopen(arq, "w");
    if (assembly_file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // 1ª passagem: registrar labels e funções (código existente)
    LabelInfo labels[MAX_LABELS];
    int label_count = 0;
    int temp_line_counter = 1;
    char line[256];

    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file)) {
        char temp_line[256];
        strcpy(temp_line, line);
        
        char *start = temp_line;
        if (*start == '(') start++;
        size_t len = strlen(start);
        if (len > 0 && start[len - 1] == ')') start[len - 1] = '\0';

        char instruction[64], p1[32];
        sscanf(start, "%63[^,], %31[^,]", instruction, p1);

        if (strcmp(instruction, "LAB") == 0) {
            strncpy(labels[label_count].label, p1, MAX_LABEL_LEN - 1);
            labels[label_count].label[MAX_LABEL_LEN-1] = '\0';
            labels[label_count].line = temp_line_counter;
            label_count++;
        }
        if (strcmp(instruction, "FUNC") == 0) {
             char func_name[32];
             sscanf(start, "%*[^,], %31[^,]", func_name);
             adicionarFuncao(func_name, temp_line_counter);
        }
        temp_line_counter++;
    }

    char ra1_buf[8], ra2_buf[8], ra3_buf[8];
    const char *ra1, *ra2, *ra3;
    int args = 0;
    int vars = 0;

    // 2ª passagem: processar instruções
    fseek(file, 0, SEEK_SET);
    
    // NOVO: Contador específico para as linhas de instrução do Assembly gerado.
    int assembly_line_counter = 1;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *start = line;
        if (*start == '(') start++;
        size_t len = strlen(start);
        if (len > 0 && start[len - 1] == ')') start[len - 1] = '\0';

        char op[32], a1[32], a2[32], a3[32];
        sscanf(start, "%31[^,], %31[^,], %31[^,], %31[^,]", op, a1, a2, a3);

        ra1 = reg(a1, ra1_buf);
        ra2 = reg(a2, ra2_buf);
        ra3 = reg(a3, ra3_buf);

        if (strcmp(op, "ASSIGN") == 0) {
            if (strcmp(a3, "-") == 0) {
                if (a2[0] >= '0' && a2[0] <= '9') {
                    printf("addi %s, r0, %s\n", ra1, a2);
                    fprintf(assembly_file, "addi %s, r0, %s\n", ra1, a2);
                } else {
                    printf("add %s, r0, %s,\n", ra2, ra1);
                    fprintf(assembly_file, "add %s, r0, %s\n", ra2, ra1);
                }
                assembly_line_counter++;
            }
        } else if (strcmp(op, "ALLOC") == 0) {
            printf("addi r30, r30, 1\n");
            fprintf(assembly_file, "addi r30, r30, 1\n");
            assembly_line_counter++;
        } else if (strcmp(op, "ADD") == 0) {
            printf("add %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "add %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SUB") == 0) {
            printf("sub %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "sub %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "MULT") == 0) {
            printf("mult %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "mult %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "DIV") == 0) {
            printf("div %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "div %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SLT") == 0) {
            printf("slt %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "slt %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SGT") == 0) {
            printf("sgt %s, %s, %s\n", ra2, ra3, ra1);
            fprintf(assembly_file, "sgt %s, %s, %s\n", ra2, ra3, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SLL") == 0) {
            printf("sll %s, %s, %s\n", ra2, ra3, a1);
            fprintf(assembly_file, "sll %s, %s, %s\n", ra2, ra3, a1);
            assembly_line_counter++;
        } else if (strcmp(op, "SRT") == 0) {
            printf("srt %s, %s, %s\n", ra2, ra3, a1);
            fprintf(assembly_file, "srt %s, %s, %s\n", ra2, ra3, a1);
            assembly_line_counter++;
        } else if (strcmp(op, "ADDI") == 0) {
            printf("addi %s, %s, %s\n", ra2, ra1, a3);
            fprintf(assembly_file, "addi %s, %s, %s\n", ra2, ra1, a3);
            assembly_line_counter++;
        } else if (strcmp(op, "SUBI") == 0) {
            printf("subi %s, %s, %s\n", ra2, ra1, a3);
            fprintf(assembly_file, "subi %s, %s, %s\n", ra2, ra1, a3);
            assembly_line_counter++;
        } else if (strcmp(op, "MULTI") == 0) {
            printf("multi %s, %s, %s\n", ra2, ra1, a3);
            fprintf(assembly_file, "multi %s, %s, %s\n", ra2, ra1, a3);
            assembly_line_counter++;
        } else if (strcmp(op, "DIVI") == 0) {
            printf("divi %s, %s, %s\n", ra2, ra1, a3);
            fprintf(assembly_file, "divi %s, %s, %s\n", ra2, ra1, a3);
            assembly_line_counter++;
        } else if (strcmp(op, "EQ") == 0) {
            if (atoi(a3) != 0) {
                printf("eqi %s, %s, %s\n", ra2, ra1, a3);
                fprintf(assembly_file, "eqi %s, %s, %s\n", ra2, ra1, a3);
            } else {
                printf("eq %s, %s, %s\n", ra2, ra1, ra3);
                fprintf(assembly_file, "eq %s, %s, %s\n", ra2, ra1, ra3);
            }
            assembly_line_counter++;
        } else if (strcmp(op, "NEQ") == 0) {
            if (atoi(a3) != 0) {
                printf("neqi %s, %s, %s\n", ra2, ra1, a3);
                fprintf(assembly_file, "neqi %s, %s, %s\n", ra2, ra1, a3);
            } else {
                printf("neq %s, %s, %s\n", ra2, ra1, ra3);
                fprintf(assembly_file, "neq %s, %s, %s\n", ra2, ra1, ra3);
            }
            assembly_line_counter++;
        } else if (strcmp(op, "SLTEQ") == 0) {
            printf("slt r3, %s, %s\n", ra3, ra2);
            fprintf(assembly_file, "slt r3, %s, %s\n", ra3, ra2);
            assembly_line_counter++;
            printf("ADDI %s, r0, 1\n", ra1);
            fprintf(assembly_file, "ADDI %s, r0, 1\n", ra1);
            assembly_line_counter++;
            printf("SUB %s, %s, r3\n", ra1, ra1);
            fprintf(assembly_file, "SUB %s, %s, r3\n", ra1, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SGTEQ") == 0) {
            printf("slt r3, %s, %s\n", ra2, ra3);
            fprintf(assembly_file, "slt r3, %s, %s\n", ra2, ra3);
            assembly_line_counter++;
            printf("ADDI %s, r0, 1\n", ra1);
            fprintf(assembly_file, "ADDI %s, r0, 1\n", ra1);
            assembly_line_counter++;
            printf("SUB %s, %s, r3\n", ra1, ra1);
            fprintf(assembly_file, "SUB %s, %s, r3\n", ra1, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "IFF") == 0) {
            printf("beq %s, r0, %s\n", ra1, a2);
            fprintf(assembly_file, "beq %s, r0, %s\n", ra1, a2);
            assembly_line_counter++;
        } else if (strcmp(op, "GOTO") == 0) {
            printf("jump %s\n", a1);
            fprintf(assembly_file, "jump %s\n", a1);
            assembly_line_counter++;
        } else if (strcmp(op, "LAB") == 0) {
            printf("%s:\n", a1);
            fprintf(assembly_file, "%s:\n", a1);
        } else if (strcmp(op, "LOAD") == 0) {
            if (strchr(a2, '[')) {
                char array[32], index[32];
                sscanf(a2, "%31[^[][%31[^]]", array, index);
                printf("add r3, %s, %s\n", reg(array, ra1_buf), reg(index, ra2_buf));
                fprintf(assembly_file, "add r3, %s, %s\n", reg(array, ra1_buf), reg(index, ra2_buf));
                assembly_line_counter++;
                printf("lw %s, 0(r3)\n", ra1);
                fprintf(assembly_file, "lw %s, 0(r3)\n", ra1);
                assembly_line_counter++;
            } else {
                printf("lw r29, %s, %d\n", ra1, vars - 1);
                fprintf(assembly_file, "lw r29, %s, %d\n", ra1, vars - 1);
                assembly_line_counter++;
            }
        } else if (strcmp(op, "SW") == 0) {
            if (strchr(a1, '[')) {
                char array[32], index[32];
                sscanf(a1, "%31[^[][%31[^]]", array, index);
                printf("add r3, %s, %s\n", reg(array, ra1_buf), reg(index, ra2_buf));
                fprintf(assembly_file, "add r3, %s, %s\n", reg(array, ra1_buf), reg(index, ra2_buf));
                assembly_line_counter++;
                printf("sw %s, 0(r3)\n", reg(a2, ra2_buf));
                fprintf(assembly_file, "sw %s, 0(r3)\n", reg(a2, ra2_buf));
                assembly_line_counter++;
            } else {
                printf("sw %s, r29, 0\n", reg(a2, ra2_buf));
                fprintf(assembly_file, "sw %s, r29, 0\n", reg(a2, ra2_buf));
                assembly_line_counter++;
            }
        } else if (strcmp(op, "FUNC") == 0) {
            printf("%s:\n", a2);
            fprintf(assembly_file, "%s:\n", a2);
            if (strcmp(a2, "main") != 0) {
                printf("sw r29, r31, 1\n");
                fprintf(assembly_file, "sw r29, r31, 1\n");
                assembly_line_counter++;
                printf("addi r30, r30, 1\n");
                fprintf(assembly_file, "addi r30, r30, 1\n");
                assembly_line_counter++;
            }
        } else if (strcmp(op, "PARAM") == 0 && strcmp(a2, "output") != 0) {
            printf("sw r29, r2%d, 0\n", args);
            fprintf(assembly_file, "sw r29, r2%d, 0\n", args);
            assembly_line_counter++;
            printf("addi r30, r30, 1\n");
            fprintf(assembly_file, "addi r30, r30, 1\n");
            assembly_line_counter++;
            args++;
        } else if (strcmp(op, "UNPARAM") == 0) {
            args--;
            printf("subi r30, r30, 1\n");
            fprintf(assembly_file, "subi r30, r30, 1\n");
            assembly_line_counter++;
            printf("lw r30, r2%d, 0\n", args);
            fprintf(assembly_file, "lw r30, r2%d, 0\n", args);
            assembly_line_counter++;
        } else if (strcmp(op, "CALL") == 0) {
            if (strcmp(a2, "input") == 0) {
                printf("input %s\n", ra1);
                fprintf(assembly_file, "input %s\n", ra1);
                assembly_line_counter++;
                vars++;
            } else if (strcmp(a2, "output") == 0) {
                printf("output r28\n");
                fprintf(assembly_file, "output r28\n");
                assembly_line_counter++;
            } else {
                printf("sw r30, r29, 0\n");
                fprintf(assembly_file, "sw r30, r29, 0\n");
                assembly_line_counter++;
                printf("addi r29, r30, 0\n");
                fprintf(assembly_file, "addi r29, r30, 0\n");
                assembly_line_counter++;
                printf("addi r30, r30, 1\n");
                fprintf(assembly_file, "addi r30, r30, 1\n");
                assembly_line_counter++;
                for (int i = 0; i < args; i++) {
                    printf("sw r29, r2%d, %d\n", i, 2 + i);
                    fprintf(assembly_file, "sw r29, r2%d, %d\n", i, 2 + i);
                    assembly_line_counter++;
                }
                printf("jal %d\n", pesquisarFuncTable(a2));
                fprintf(assembly_file, "jal %d\n", pesquisarFuncTable(a2));
                assembly_line_counter++;
                printf("addi r29, r30, 0\n");
                fprintf(assembly_file, "addi r29, r30, 0\n");
                assembly_line_counter++;
                printf("lw r29, r29, 0\n");
                fprintf(assembly_file, "lw r29, r29, 0\n");
                assembly_line_counter++;
            }
        } else if (strcmp(op, "RET") == 0) {
            printf("add r28, %s, r0\n", ra1);
            fprintf(assembly_file, "add r28, %s, r0\n", ra1);
            assembly_line_counter++;
            printf("jr r31\n");
            fprintf(assembly_file, "jr r31\n");
            assembly_line_counter++;
        } else if (strcmp(op, "HALT") == 0) {
            int halt_target_line = assembly_line_counter;
            printf("halt:\n");
            fprintf(assembly_file, "halt:\n");
            printf("jump %d\n", halt_target_line);
            fprintf(assembly_file, "jump %d\n", halt_target_line);
            assembly_line_counter++;
        }
    }
    printFuncTable();
    fclose(file);
    fclose(assembly_file);
}