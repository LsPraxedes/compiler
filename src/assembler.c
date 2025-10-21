#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/global.h"
#include "../headers/quadruplas.h"


#define MAX_LABELS 100
#define MAX_LABEL_LEN 8

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
    "IFF", "SUBI", "PARAM", "CALL", "RET", "", "GOTO", "HALT"
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
    assembly_file = fopen(arq, "w+");
    if (assembly_file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    fprintf(assembly_file, "jump 1   ");
    // 1ª passagem: registrar labels e funções (código existente)
    LabelInfo labels[MAX_LABELS];
    int label_count = 0;
    int temp_line_counter = 1;
    char line[256];

    char ra1_buf[8], ra2_buf[8], ra3_buf[8];
    const char *ra1, *ra2, *ra3;
    char *param[3];
    char *args[3];
    param[0] = (char*)malloc(12 * sizeof(char));
    param[1] = (char*)malloc(12 * sizeof(char));
    param[2] = (char*)malloc(12 * sizeof(char)); 
    args[0] = (char*)malloc(12 * sizeof(char));
    args[1] = (char*)malloc(12 * sizeof(char));
    args[2] = (char*)malloc(12 * sizeof(char));
    int localargs = 0;
    int localparam = 0;


    int vars = 0;
    char localvars[3][10];
    int localvars_count = 0;
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
                    printf("addi r0, %s, %s\n", ra1, a2);
                    fprintf(assembly_file, "addi r0, %s, %s\n", ra1, a2);
                } else {
                    printf("add r0, %s, %s\n", ra2, ra1);
                    fprintf(assembly_file, "add r0, %s, %s\n", ra2, ra1);
                }
                assembly_line_counter++;
            }
        } else if (strcmp(op, "ALLOC") == 0) {
            printf("addi r30, r30, 1\n");
            fprintf(assembly_file, "addi r30, r30, 1\n");
            strcpy(localvars[localvars_count++], a1);
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
            if (isdigit(a3[0])!= 0) {
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
            printf("addi %s, r0, 1\n", ra1);
            fprintf(assembly_file, "addi %s, r0, 1\n", ra1);
            assembly_line_counter++;
            printf("sub %s, %s, r3\n", ra1, ra1);
            fprintf(assembly_file, "sub %s, %s, r3\n", ra1, ra1);
            assembly_line_counter++;
        } else if (strcmp(op, "SGTEQ") == 0) {
            printf("slt r3, %s, %s\n", ra2, ra3);
            fprintf(assembly_file, "slt r3, %s, %s\n", ra2, ra3);
            assembly_line_counter++;
            printf("addi %s, r0, 1\n", ra1);
            fprintf(assembly_file, "addi %s, r0, 1\n", ra1);
            assembly_line_counter++;
            printf("sub %s, %s, r3\n", ra1, ra1);
            fprintf(assembly_file, "sub %s, %s, r3\n", ra1, ra1);
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
            strcpy(labels[label_count].label, a1);
            labels[label_count].line = assembly_line_counter;
            label_count++;
            printf("%s:\n", a1);
        } else if (strcmp(op, "ARG")==0){
            printf("addi r30, r30, 1\n");
            fprintf(assembly_file, "addi r30, r30, 1\n");
            localargs++;
            strcpy(localvars[localvars_count++], a2);
            printf("%d %s\n", localvars_count, localvars[localvars_count-1]);
            assembly_line_counter++;
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
                if(strcmp(a3, "main")!=0){
                    for(int i=0;i<localvars_count;i++){
                        if(strcmp(a2, localvars[i])==0){
                            printf("%d %s\n", localvars_count, localvars[localvars_count]);
                            printf("lw r29, %s, %d\n", ra1, 2+i);
                            fprintf(assembly_file, "lw r29, %s, %d\n", ra1, 2+i);
                            assembly_line_counter++;
                            break;
                        }
                    }
                } else {
                    vars++;
                    printf("lw r29, %s, %d\n", ra1, vars - 1);
                    fprintf(assembly_file, "lw r29, %s, %d\n", ra1, vars - 1);
                    assembly_line_counter++;
                }
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
                for(int i=0;i<localvars_count;i++){
                    if(strcmp(a1, localvars[i])==0){
                        printf("sw r29, %s, %d\n", ra2, 2+i);
                        fprintf(assembly_file, "sw r29, %s, %d\n", ra2, 2+i);
                        assembly_line_counter++;
                        break;
                    }
                }
            }
        } else if (strcmp(op, "FUNC") == 0) {
            printf("%s:\n", a2);
            adicionarFuncao(a2, assembly_line_counter);
            if (strcmp(a2, "main") != 0) {
                localargs=0;
                for(int i=0;i<localvars_count;i++){
                    strcpy(localvars[i], "");
                }
                localvars_count=0;
                printf("sw r29, r31, 1\n");
                fprintf(assembly_file, "sw r29, r31, 1\n");
                assembly_line_counter++;
                printf("addi r30, r30, 1\n");
                fprintf(assembly_file, "addi r30, r30, 1\n");
                assembly_line_counter++;
            }
            else{
                for(int i=0;i<localvars_count;i++){
                    strcpy(localvars[i], "");
                }
                localvars_count=0;
                long pos = ftell(assembly_file);
                fseek(assembly_file, 0L, SEEK_SET);
                fprintf(assembly_file, "jump %d\n", pesquisarFuncTable(a2));
                fseek(assembly_file, pos, SEEK_SET);
            }
        } else if (strcmp(op, "PARAM") == 0 && strcmp(a2, "output") != 0) {
            strcpy(param[localparam], ra1); // Armazena o número do registrador
            printf("sw r30, %s, 0\n", param[localparam]);
            fprintf(assembly_file, "sw r30, %s, 0\n", param[localparam]);
            assembly_line_counter++;
            printf("addi r30, r30, 1\n");
            fprintf(assembly_file, "addi r30, r30, 1\n");
            assembly_line_counter++;
            localparam++;
        } else if (strcmp(op, "UNPARAM") == 0) {
            localparam--;
            printf("subi r30, r30, 1\n");
            fprintf(assembly_file, "subi r30, r30, 1\n");
            assembly_line_counter++;
            printf("lw r30, %s, 0\n", param[localparam]);
            fprintf(assembly_file, "lw r30, %s, 0\n", param[localparam]);
            assembly_line_counter++;
        } else if (strcmp(op, "CALL") == 0) {
            if (strcmp(a2, "input") == 0) {
                printf("input %s\n", ra1);
                fprintf(assembly_file, "input %s\n", ra1);
                assembly_line_counter++;
            } else if (strcmp(a2, "output") == 0) {
                printf("output %s\n", ra1);
                fprintf(assembly_file, "output %s\n", ra1);
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
                for (int i = 0; i < localparam;i++) {
                    printf("sw r29, %s, %d\n", param[i], 2+i);
                    fprintf(assembly_file, "sw r29, %s, %d\n", param[i], 2+i);
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
        } else if (strcmp(op, "RET0") == 0) {
            printf("add r28, r0, r28\n");
            fprintf(assembly_file, "add r28, r0, r28\n");
            assembly_line_counter++;

        } else if (strcmp(op, "RET1") == 0) {
            printf("add %s, r0, r28\n", ra1);
            fprintf(assembly_file, "add %s, r0, r28\n", ra1);
            assembly_line_counter++;

        } else if(strcmp(op, "END")==0 && strcmp(a1, "main")!=0){
            printf("lw 29, r31, 1\n");
            fprintf(assembly_file, "lw 29, r31, 1\n");
            assembly_line_counter++;
            printf("jr r31\n");
            fprintf(assembly_file, "jr r31\n");
            assembly_line_counter++;            // ...existing code...
                    line[strcspn(line, "\n")] = 0;
                    char *start = line;
                    if (*start == '(') start++;
                    // trim leading spaces
                    while (*start && isspace((unsigned char)*start)) start++;
                    // trim trailing spaces (antes do ')')
                    size_t len = strlen(start);
                    while (len > 0 && isspace((unsigned char)start[len-1])) { start[--len] = '\0'; }
                    if (len > 0 && start[len-1] == ')') start[len-1] = '\0';
            
                    // inicializa buffers para evitar reuso de valores antigos
                    op[0] = a1[0] = a2[0] = a3[0] = '\0';
            
                    // extrai campos e verifica quantos foram lidos
                    int fields = sscanf(start, "%31[^,], %31[^,], %31[^,], %31[^,]", op, a1, a2, a3);
                    if (fields <= 0) continue; // linha vazia ou inválida — pula
            
                    // ...existing code...
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

    // Após escrever todo o arquivo:
    rewind(assembly_file);
    FILE *temp_file = fopen("outputs/Assembly_temp.txt", "w");
    int current_line = 1;
    while (fgets(line, sizeof(line), assembly_file)) {
        char out_line[256];
        int replaced = 0;
        // Procura por jump/beq com label
        for (int i = 0; i < label_count; i++) {
            char search[32];
            sprintf(search, "jump %s", labels[i].label);
            if (strstr(line, search)) {
                sprintf(out_line, "jump %d\n", labels[i].line);
                fputs(out_line, temp_file);
                replaced = 1;
                break;
            }
            sprintf(search, "beq ");
            if (strstr(line, search) && strstr(line, labels[i].label)) {
                // Exemplo: beq r4, r0, L0
                char *label_pos = strstr(line, labels[i].label);
                int prefix_len = label_pos - line;
                strncpy(out_line, line, prefix_len);
                out_line[prefix_len] = '\0';
                sprintf(out_line + prefix_len, "%d\n", labels[i].line);
                fputs(out_line, temp_file);
                replaced = 1;
                break;
            }
            sprintf(search, "bne ");
            if (strstr(line, search) && strstr(line, labels[i].label)) {
                // Exemplo: beq r4, r0, L0
                char *label_pos = strstr(line, labels[i].label);
                int prefix_len = label_pos - line;
                strncpy(out_line, line, prefix_len);
                out_line[prefix_len] = '\0';
                sprintf(out_line + prefix_len, "%d\n", labels[i].line);
                fputs(out_line, temp_file);
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            fputs(line, temp_file);
        }
        current_line++;
    }
    fclose(temp_file);
    fclose(assembly_file);
    fclose(file);
    // Renomeia o arquivo temporário para o final
    remove("outputs/Assembly.txt");
    rename("outputs/Assembly_temp.txt", "outputs/Assembly.txt");
}