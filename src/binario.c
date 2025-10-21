#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função CORRIGIDA: preenche um buffer fornecido com a string binária.
void to_binary(char* buffer, long value, int bits) {
    int is_negative = (value < 0);
    unsigned long abs_value = is_negative ? -value : value;
    unsigned long mask = 1UL << (bits - 1);

    for (int i = 0; i < bits; i++) {
        buffer[i] = (abs_value & mask) ? '1' : '0';
        mask >>= 1;
    }
    // Se negativo, força o bit de sinal (primeiro bit) para 1
    if (is_negative)
        buffer[0] = '1';

    buffer[bits] = '\0';
}

// Função para extrair o número de um registrador (ex: "r12" -> 12)
int get_reg_num(const char* reg_str) {
    if (reg_str == NULL || reg_str[0] != 'r') {
        return 0;
    }
    return atoi(reg_str + 1);
}

void processaAssembly() {
    FILE *file_in = fopen("outputs/Assembly.txt", "r");
    if (file_in == NULL) {
        perror("Erro ao abrir o arquivo outputs/Assembly.txt");
        exit(EXIT_FAILURE);
    }
    // Adicionado: Abrir o arquivo de saída para escrita
    FILE *file_out = fopen("outputs/Binario.txt", "w");
    if (file_out == NULL) {
        perror("Erro ao criar o arquivo outputs/Binario.txt");
        fclose(file_in); // Fecha o arquivo de entrada antes de sair
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file_in)) {
        line[strcspn(line, "\n\r")] = 0;

        if (strlen(line) == 0) continue;
        
        char original_line[256];
        strcpy(original_line, line);

        if (strchr(line, ':') != NULL) {
            if (strncmp(line, "halt:", 5) == 0) {
                // Formatação para HALT com espaço
                printf("%-25s -> 11111100000000000000000000000000\n", "halt:");
                fprintf(file_out,"11111100000000000000000000000000\n");
            } else {
                //printf("%s\n", original_line); // Imprime o label
                //fprintf(file_out, "%s\n", original_line);
            }
            continue;
        }

        char *op = strtok(line, " ,\t");
        if (!op) continue;

        char *p1 = strtok(NULL, " ,\t");
        char *p2 = strtok(NULL, " ,\t");
        char *p3 = strtok(NULL, " ,\t");

        char opcode[7], rs[6], rt[6], rd[6], shamt[6], funct[7], imm[17], addr[27];
        char final_binary[45] = {0}; // Aumentado o tamanho para comportar os espaços

        // --- TIPO R --- (op fonte1, fonte2, destino)
        if (strcmp(op, "add") == 0 || strcmp(op, "sub") == 0 || strcmp(op, "mult") == 0 ||
            strcmp(op, "div") == 0 || strcmp(op, "slt") == 0 || strcmp(op, "sgt") == 0 ||
            strcmp(op, "sll") == 0 || strcmp(op, "srl") == 0 || strcmp(op, "eq") == 0 || strcmp(op, "neq") == 0) {
            
            if (strcmp(op, "add") == 0) strcpy(opcode, "000000");
            else if (strcmp(op, "sub") == 0) strcpy(opcode, "000001");
            else if (strcmp(op, "mult") == 0) strcpy(opcode, "000010");
            else if (strcmp(op, "div") == 0) strcpy(opcode, "000011");
            else if (strcmp(op, "slt") == 0) strcpy(opcode, "001000");
            else if (strcmp(op, "sgt") == 0) strcpy(opcode, "001001");
            else if (strcmp(op, "sll") == 0) strcpy(opcode, "001010");
            else if (strcmp(op, "srl") == 0) strcpy(opcode, "001011");
            else if (strcmp(op, "eq") == 0) strcpy(opcode, "011001");
            else if (strcmp(op, "neq") == 0) strcpy(opcode, "011010");
            
            to_binary(rs, get_reg_num(p1), 5);
            to_binary(rt, get_reg_num(p2), 5);
            to_binary(rd, get_reg_num(p3), 5);
            strcpy(shamt, "00000");
            strcpy(funct, "000000");
            // Adicionado espaços no formato
            sprintf(final_binary, "%s%s%s%s%s%s", opcode, rs, rt, rd, shamt, funct);
        }
        // --- TIPO I --- (op fonte/base, destino/fonte, imediato)
        else if (strcmp(op, "addi") == 0 || strcmp(op, "subi") == 0 || strcmp(op, "multi") == 0 || 
                strcmp(op, "divi") == 0 || strcmp(op, "beq") == 0 || strcmp(op, "bne") == 0 || 
                strcmp(op, "lw") == 0 || strcmp(op, "sw") == 0 || strcmp(op, "eqi") == 0 || strcmp(op, "neqi") == 0) {

            if (strcmp(op, "addi") == 0) strcpy(opcode, "001100");
            else if (strcmp(op, "subi") == 0) strcpy(opcode, "001101");
            else if (strcmp(op, "multi") == 0) strcpy(opcode, "001110");
            else if (strcmp(op, "divi") == 0) strcpy(opcode, "001111");
            else if (strcmp(op, "beq") == 0) strcpy(opcode, "010000");
            else if (strcmp(op, "bne") == 0) strcpy(opcode, "010001");
            else if (strcmp(op, "lw") == 0) strcpy(opcode, "010010");
            else if (strcmp(op, "sw") == 0) strcpy(opcode, "010011");
            else if (strcmp(op, "eqi") == 0) strcpy(opcode, "011011");
            else if (strcmp(op, "neqi") == 0) strcpy(opcode, "011100");

            to_binary(rs, get_reg_num(p1), 5);
            to_binary(rt, get_reg_num(p2), 5);
            to_binary(imm, atoi(p3), 16);
            // Adicionado espaços no formato
            sprintf(final_binary, "%s%s%s%s", opcode, rs, rt, imm);
        }
        // --- TIPO J ---
        else if (strcmp(op, "jump") == 0) {
            strcpy(opcode, "010100");
            to_binary(addr, p1 ? atoi(p1) : 0, 26);
            // Adicionado espaço no formato
            sprintf(final_binary, "%s%s", opcode, addr);
        }
        else if (strcmp(op, "jal") == 0) {
            strcpy(opcode, "010110");
            to_binary(addr, p1 ? atoi(p1) : 0, 26);
            // Adicionado espaço no formato
            sprintf(final_binary, "%s%s", opcode, addr);
        }
        else if (strcmp(op, "jr") == 0) {
            strcpy(opcode, "010101");
            to_binary(rs, get_reg_num(p1), 5);
            // Adicionado espaços para clareza, seguindo o formato Tipo R
            sprintf(final_binary, "%s%s000000000000000000000", opcode, rs);
        }
        // --- TIPO U & Custom ---
        else if (strcmp(op, "input") == 0) {
            strcpy(opcode, "010111");
            to_binary(rt, get_reg_num(p1), 5); // Destino é rt
            // Adicionado espaços para clareza
            sprintf(final_binary, "%s%s000000000000000000000", opcode, rt);
        }
        else if (strcmp(op, "output") == 0) {
            strcpy(opcode, "011000");
            to_binary(rs, get_reg_num(p1), 5); // Fonte é rs
            // Adicionado espaços para clareza
            sprintf(final_binary, "%s%s000000000000000000000", opcode, rs);
        }
        
        printf("%-25s -> %s\n", original_line, final_binary);
        fprintf(file_out, "%s\n", final_binary); // Escreve a linha convertida no arquivo
    }

    fclose(file_in);
    fclose(file_out); // Adicionado: Fechar o arquivo de saída
}