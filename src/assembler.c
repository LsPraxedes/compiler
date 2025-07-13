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

    // 1ª passagem: registrar labels
    LabelInfo labels[MAX_LABELS];
    int label_count = 0;
    int line_counter = 1;
    char line[256];

    // Salvar posição dos labels
    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file)) {
        char *start = line;
        if (*start == '(') start++;
        size_t len = strlen(start);
        if (len > 0 && start[len - 1] == ')') start[len - 1] = '\0';

        char instruction[64];
        char *comma = strchr(start, ',');
        if (comma) {
            size_t ilen = comma - start;
            strncpy(instruction, start, ilen);
            instruction[ilen] = '\0';
        } else {
            strncpy(instruction, start, sizeof(instruction) - 1);
            instruction[sizeof(instruction) - 1] = '\0';
        }

        if (strcmp(instruction, "LAB") == 0) {
            // Pega o nome do label
            char *label_start = comma + 2; // pula ", "
            char *label_end = strchr(label_start, ',');
            size_t labellen = label_end ? (size_t)(label_end - label_start) : strlen(label_start);
            strncpy(labels[label_count].label, label_start, labellen);
            labels[label_count].label[labellen] = '\0';
            labels[label_count].line = line_counter;
            label_count++;
        }
        line_counter++;
    }

    char ra1_buf[8], ra2_buf[8], ra3_buf[8];
    const char *ra1;
    const char *ra2;
    const char *ra3;
    int args=0;
    int vars=0;

    // 2ª passagem: processar instruções
    fseek(file, 0, SEEK_SET);
    line_counter = 1;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *start = line;
        if (*start == '(') start++;
        size_t len = strlen(start);
        if (len > 0 && start[len - 1] == ')') start[len - 1] = '\0';

        char op[32], a1[32], a2[32], a3[32];
        sscanf(start, "%31[^,], %31[^,], %31[^,], %31[^,]", op, a1, a2, a3);

        ra1 = reg(a1, ra1_buf);
        //printf("%s\n", ra1);
        ra2 = reg(a2, ra2_buf);
        ra3 = reg(a3, ra3_buf);
        printf("%s:\n", op);
        // Transformações conforme solicitado
        if (strcmp(op, "ASSIGN") == 0) {
            if (strcmp(a3, "-") == 0) {
                // ASSIGN, rd, rs, -
                if (a2[0] >= '0' && a2[0] <= '9') // valor imediato
                    printf("%03d: addi %s, r0, %s\n", line_counter, ra1, a2);
                else
                    printf("%03d: add %s, %s, r0\n", line_counter, ra1, ra2);
            }
        } else if (strcmp(op, "ALLOC") == 0) {
            printf("%03d: addi r30, r30, 1\n", line_counter); // r30 = $sp
        } else if (strcmp(op, "ADDI") == 0) {
            printf("%03d: addi %s, %s, %s\n", line_counter, ra1, ra2, a3);
        } else if (strcmp(op, "SUB") == 0) {
            printf("%03d: sub %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        } else if (strcmp(op, "SLT") == 0) {
            printf("%03d: slt %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        } else if (strcmp(op, "MULT") == 0) {
            printf("%03d: mult %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        } else if (strcmp(op, "DIV") == 0) {
            printf("%03d: div %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        }else if (strcmp(op, "SLT") == 0) {
            printf("%03d: slt %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        }else if (strcmp(op, "EQ") == 0) {
            // EQ, rd, rs, rt  => sub r3, rs, rt / beq r3, r0, label_true / addi rd, r0, 0 / jump label_end / label_true: addi rd, r0, 1 / label_end:
            // Para simplificação, vamos usar: sub r3, rs, rt / slt r4, r0, r3 / slt r5, r3, r0 / or r6, r4, r5 / xori rd, r6, 1
            printf("%03d: sub r3, %s, %s\n", line_counter, ra2, ra3); // r3 = rs - rt
            printf("%03d: slt r4, r0, r3\n", line_counter);                  // r4 = (r3 > 0)
            printf("%03d: slt r5, r3, r0\n", line_counter);                  // r5 = (r3 < 0)
            printf("%03d: or r6, r4, r5\n", line_counter);                   // r6 = (r3 != 0)
            printf("%03d: ADDI %s, r0, 1\n", line_counter, ra1);         // rd = 1
            printf("%03d: SUB %s, %s, r6\n", line_counter, ra1, ra1);// rd = 1 - (r3 != 0)
        } else if (strcmp(op, "NEQ") == 0) {
            // NEQ, rd, rs, rt => sub r3, rs, rt / slt r4, r0, r3 / slt r5, r3, r0 / or rd, r4, r5
            printf("%03d: sub r3, %s, %s\n", line_counter, ra2, ra3);
            printf("%03d: slt r4, r0, r3\n", line_counter);
            printf("%03d: slt r5, r3, r0\n", line_counter);
            printf("%03d: or %s, r4, r5\n", line_counter, ra1);
        } else if (strcmp(op, "SLTEQ") == 0) {
            // SLTEQ, rd, rs, rt => slt r3, rt, rs / ADDI rd, r0, 1 / SUB rd, rd, r3
            printf("%03d: slt r3, %s, %s\n", line_counter, ra3, ra2);
            printf("%03d: ADDI %s, r0, 1\n", line_counter, ra1);
            printf("%03d: SUB %s, %s, r3\n", line_counter, ra1, ra1);
        } else if (strcmp(op, "SGT") == 0) {
            // SGT, rd, rs, rt => slt rd, rt, rs
            printf("%03d: sgt %s, %s, %s\n", line_counter, ra1, ra2, ra3);
        } else if (strcmp(op, "SGTEQ") == 0) {
            // SGTEQ, rd, rs, rt => slt r3, rs, rt / ADDI rd, r0, 1 / SUB rd, rd, r3
            printf("%03d: slt r3, %s, %s\n", line_counter, ra2, ra3);
            printf("%03d: ADDI %s, r0, 1\n", line_counter, ra1);
            printf("%03d: SUB %s, %s, r3\n", line_counter, ra1, ra1);
        } else if (strcmp(op, "IFF") == 0) {
            printf("%03d: beq %s, r0, %s\n", line_counter, ra1, a2);
        } else if (strcmp(op, "GOTO") == 0) {
            printf("%03d: jump %s\n", line_counter, a1);
        } else if (strcmp(op, "LAB") == 0) {
            printf("%03d: %s:\n", line_counter, a1);
        } else if (strcmp(op, "LOAD") == 0) {
            if (strchr(a2, '[')) {
                // LOAD, rd, array[rs], -
                char array[32], index[32];
                sscanf(a2, "%31[^[][%31[^]]", array, index);
                printf("%03d: add r3, %s, %s\n", line_counter, reg(array, ra1_buf), reg(index, ra2_buf)); // r3 como temporário
                printf("%03d: lw %s, 0(r3)\n", line_counter, ra1);
            } else {
                // LOAD, rd, var, -
                printf("%03d: lw %s, 0(r29)\n", line_counter, ra1); // r29 = $fp
            }
        } else if (strcmp(op, "SW") == 0) {
            if (strchr(a1, '[')) {
                // SW, array[rt], rs, -
                char array[32], index[32];
                sscanf(a1, "%31[^[][%31[^]]", array, index);
                printf("%03d: add r3, %s, %s\n", line_counter, reg(array, ra1_buf), reg(index,ra2_buf)); // r3 como temporário
                printf("%03d: sw %s, 0(r3)\n", line_counter, reg(a2, ra2_buf));
            } else {
                // SW, var, rs, -
                printf("%03d: sw %s, 0(r29)\n", line_counter,reg(a2, ra2_buf));
            }
        } else if (strcmp(op, "FUNC") == 0) {
            if(strcmp(a2, "main") != 0){
                adicionarFuncao(a2, line_counter);
                printf("%03d: %s:\n", line_counter, a2);
                printf("%03d: sw r29, 1(r31)\n", line_counter); // r30 = $sp
                printf("%03d: addi r30, r30, 1\n", line_counter);
            }
            else {
                printf("%03d: main:\n", line_counter);
            }
        } else if (strcmp(op, "PARAM") == 0 && strcmp(a2, "output") != 0) {
            printf("%03d: sw r29, %d(r2%d)\n", line_counter, args,args); // r30 = $sp
            printf("%03d: addi r30, r30, 1\n", line_counter);
            args++;
        } else if (strcmp(op, "UNPARAM") == 0) {
            args--;
            printf("%03d: addi r30, r30, -1\n", line_counter);
            printf("%03d: lw r30, 0(r2%d)\n", line_counter,args); // r30 = $sp;
        } else if (strcmp(op, "CALL") == 0) {
            if(strcmp(a2, "input") == 0) {
                printf("%03d: input %s\n", line_counter, ra1);
                vars++;
            } else if(strcmp(a2, "output") == 0) {
                printf("%03d: output %s\n", line_counter, ra1);
            }else{
                printf("%03d: sw r30, 0(r29)\n", line_counter); // r30 = $sp
                printf("%03d: addi r29, r30, 0\n", line_counter);
                printf("%03d: addi r30, r30, 1\n", line_counter); // r30 = $sp
                for(int i = 0; i < args; i++) {
                    printf("%03d: sw r2%d, %d(r29)\n", line_counter, i, 2+i); // r2 = $a0, $a1, $a2, ...
                }
                printf("%03d: jal %d\n", line_counter, pesquisarFuncTable(a2));
                printf("%03d: addi r29, r30, 0\n", line_counter);
                printf("%03d: lw r29, 0(r29)\n", line_counter); // r28 = $v0
            }
        } else if (strcmp(op, "RET") == 0) {
            printf("%03d: add r28, %s, r0\n", line_counter, ra1);
            printf("%03d: jr r31\n", line_counter); // r31 = $ra
        } else if (strcmp(op, "HALT") == 0) {
            printf("%03d: halt: \n%03d: jump halt\n", line_counter,line_counter);
        }
        line_counter++;
    }
    printFuncTable();
    fclose(file);
}