#define _CRT_SECURE_NO_WARNINGS

/* 2016314786 김호진*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct R_type {
    char op[7];
    int rs;
    int rt;
    int rd;
    int shamt;
    char function[7];
} R_type;

typedef struct I_type {
    char op[7];
    int rs;
    int rt;
    int immediate;
} I_type;

typedef struct J_type {
    char op[7];
    int target;
} J_type;

int swapEndian(int num) {
    int val = ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
    return val;
}

void HextoBin(char* hex, char* bin) {
    for (int i = 0; i < 8; i++) {
        switch (hex[i]) {
        case '0':
            strcat(bin, "0000");
            break;
        case '1':
            strcat(bin, "0001");
            break;
        case '2':
            strcat(bin, "0010");
            break;
        case '3':
            strcat(bin, "0011");
            break;
        case '4':
            strcat(bin, "0100");
            break;
        case '5':
            strcat(bin, "0101");
            break;
        case '6':
            strcat(bin, "0110");
            break;
        case '7':
            strcat(bin, "0111");
            break;
        case '8':
            strcat(bin, "1000");
            break;
        case '9':
            strcat(bin, "1001");
            break;
        case 'a':
        case 'A':
            strcat(bin, "1010");
            break;
        case 'b':
        case 'B':
            strcat(bin, "1011");
            break;
        case 'c':
        case 'C':
            strcat(bin, "1100");
            break;
        case 'd':
        case 'D':
            strcat(bin, "1101");
            break;
        case 'e':
        case 'E':
            strcat(bin, "1110");
            break;
        case 'f':
        case 'F':
            strcat(bin, "1111");
            break;
        default:
            printf("ERROR\n");
        }
    }
}

void classify_R(struct R_type instruction, char* hexadecimal, int num) {
    if (strncmp(instruction.function, "100000", 6) == 0) {
        printf("inst %d: %s add $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "100001", 6) == 0) {
        printf("inst %d: %s addu $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "100100", 6) == 0) {
        printf("inst %d: %s and $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "011010", 6) == 0) {
        printf("inst %d: %s div $%d, $%d\n", num, hexadecimal, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "011011", 6) == 0) {
        printf("inst %d: %s divu $%d, $%d\n", num, hexadecimal, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "001001", 6) == 0) {
        printf("inst %d: %s jalr $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs);
    }
    else if (strncmp(instruction.function, "001000", 6) == 0) {
        printf("inst %d: %s jr $%d\n", num, hexadecimal, instruction.rs);
    }
    else if (strncmp(instruction.function, "010000", 6) == 0) {
        printf("inst %d: %s mfhi $%d\n", num, hexadecimal, instruction.rd);
    }
    else if (strncmp(instruction.function, "010010", 6) == 0) {
        printf("inst %d: %s mflo $%d\n", num, hexadecimal, instruction.rd);
    }
    else if (strncmp(instruction.function, "010001", 6) == 0) {
        printf("inst %d: %s mthi $%d\n", num, hexadecimal, instruction.rs);
    }
    else if (strncmp(instruction.function, "010011", 6) == 0) {
        printf("inst %d: %s mtlo $%d\n", num, hexadecimal, instruction.rs);
    }
    else if (strncmp(instruction.function, "011000", 6) == 0) {
        printf("inst %d: %s mult $%d, $%d\n", num, hexadecimal, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "011001", 6) == 0) {
        printf("inst %d: %s multu $%d, $%d\n", num, hexadecimal, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "100111", 6) == 0) {
        printf("inst %d: %s nor $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "100101", 6) == 0) {
        printf("inst %d: %s or $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "000000", 6) == 0) {
        printf("inst %d: %s sll $%d, $%d, %d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.shamt);
    }
    else if (strncmp(instruction.function, "000100", 6) == 0) {
        printf("inst %d: %s sllv $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.rs);
    }
    else if (strncmp(instruction.function, "101010", 6) == 0) {
        printf("inst %d: %s slt $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "101011", 6) == 0) {
        printf("inst %d: %s sltu $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "000011", 6) == 0) {
        printf("inst %d: %s sra $%d, $%d, %d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.shamt);
    }
    else if (strncmp(instruction.function, "000111", 6) == 0) {
        printf("inst %d: %s srav $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.rs);
    }
    else if (strncmp(instruction.function, "000010", 6) == 0) {
        printf("inst %d: %s srl $%d, $%d, %d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.shamt);
    }
    else if (strncmp(instruction.function, "000110", 6) == 0) {
        printf("inst %d: %s srlv $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rt, instruction.rs);
    }
    else if (strncmp(instruction.function, "100010", 6) == 0) {
        printf("inst %d: %s sub $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "100011", 6) == 0) {
        printf("inst %d: %s subu $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else if (strncmp(instruction.function, "001100", 6) == 0) {
        printf("inst %d: %s syscall\n", num, hexadecimal);
    }
    else if (strncmp(instruction.function, "100110", 6) == 0) {
        printf("inst %d: %s xor $%d, $%d, $%d\n", num, hexadecimal, instruction.rd, instruction.rs, instruction.rt);
    }
    else {
        printf("inst %d: %s unknown instruction\n", num, hexadecimal);
    }
}

void classify_I(struct I_type instruction, char* hexadecimal, int num) {
    if (strncmp(instruction.op, "001000", 6) == 0) {
        printf("inst %d: %s addi $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "001001", 6) == 0) {
        printf("inst %d: %s addiu $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "001100", 6) == 0) {
        printf("inst %d: %s andi $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "000100", 6) == 0) {
        printf("inst %d: %s beq $%d, $%d, %d\n", num, hexadecimal, instruction.rs, instruction.rt, instruction.immediate);
    }
    else if (strncmp(instruction.op, "000101", 6) == 0) {
        printf("inst %d: %s bne $%d, $%d, %d\n", num, hexadecimal, instruction.rs, instruction.rt, instruction.immediate);
    }
    else if (strncmp(instruction.op, "100000", 6) == 0) {
        printf("inst %d: %s lb $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "100100", 6) == 0) {
        printf("inst %d: %s lbu $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "100001", 6) == 0) {
        printf("inst %d: %s lh $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "100101", 6) == 0) {
        printf("inst %d: %s lhu $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "001111", 6) == 0) {
        printf("inst %d: %s lui $%d, %d\n", num, hexadecimal, instruction.rt, instruction.immediate);
    }
    else if (strncmp(instruction.op, "100011", 6) == 0) {
        printf("inst %d: %s lw $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "001101", 6) == 0) {
        printf("inst %d: %s ori $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "101000", 6) == 0) {
        printf("inst %d: %s sb $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "001010", 6) == 0) {
        printf("inst %d: %s slti $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "001011", 6) == 0) {
        printf("inst %d: %s sltiu $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else if (strncmp(instruction.op, "101001", 6) == 0) {
        printf("inst %d: %s sh $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "101011", 6) == 0) {
        printf("inst %d: %s sw $%d, %d($%d)\n", num, hexadecimal, instruction.rt, instruction.immediate, instruction.rs);
    }
    else if (strncmp(instruction.op, "001110", 6) == 0) {
        printf("inst %d: %s xori $%d, $%d, %d\n", num, hexadecimal, instruction.rt, instruction.rs, instruction.immediate);
    }
    else {
        printf("inst %d: %s unknown instruction\n", num, hexadecimal);
    }
}

void classify_J(struct J_type instruction, char* hexadecimal, int num) {
    if (strncmp(instruction.op, "000010", 6) == 0) {
        printf("inst %d: %s j %d\n", num, hexadecimal, instruction.target);
    }
    else if (strncmp(instruction.op, "000011", 6) == 0) {
        printf("inst %d: %s jal %d\n", num, hexadecimal, instruction.target);
    }
    else {
        printf("inst %d: %s unknown instruction\n", num, hexadecimal);
    }
}

int main(int argc, char** argv) {
   
    if (argc != 2) {
        fprintf(stderr, "USAGE: EXECUTABLE INPUT_FILE_NAME\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "rb");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: WRONG INPUT FILE NAME\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int* array = (int*)malloc(size);
    memset(array, 0, size);

    fread(array, sizeof(int), size / sizeof(int), fp);

    for (int i = 0; i < size / sizeof(int); i++) {
        array[i] = swapEndian(array[i]);

        char hexadecimal[9] = "";
        sprintf(hexadecimal, "%08x", array[i]);

        char binary[33] = "";
        HextoBin(hexadecimal, binary);

        if (strncmp(binary, "000000", 6) == 0) {
            R_type rInstruction = { 0, };
            char reg[6] = "";
            
            strncpy(rInstruction.op, binary, 6);

            strncpy(reg, binary + 6, 5);
            rInstruction.rs = strtol(reg, NULL, 2);

            strncpy(reg, binary + 11, 5);
            rInstruction.rt = strtol(reg, NULL, 2);

            strncpy(reg, binary + 16, 5);
            rInstruction.rd = strtol(reg, NULL, 2);

            strncpy(reg, binary + 21, 5);
            rInstruction.shamt = strtol(reg, NULL, 2);

            strncpy(rInstruction.function, binary + 26, 6);

            classify_R(rInstruction, hexadecimal, i);
        }
        else if ((strncmp(binary, "00001", 5) != 0) && (strncmp(binary, "0100", 4) != 0)) {
            I_type iInstruction = { 0, };
            char reg[6] = "";
            char immediate[17] = "";

            strncpy(iInstruction.op, binary, 6);

            strncpy(reg, binary + 6, 5);
            iInstruction.rs = strtol(reg, NULL, 2);

            strncpy(reg, binary + 11, 5);
            iInstruction.rt = strtol(reg, NULL, 2);

            strncpy(immediate, binary + 16, 16);
            iInstruction.immediate = strtol(immediate, NULL, 2);
            if (iInstruction.immediate >= 32768) {
                iInstruction.immediate -= 65536;
            }

            classify_I(iInstruction, hexadecimal, i);
        }
        else if (strncmp(binary, "00001", 5) == 0) {
            J_type jInstruction = { 0, };
            char target[27] = "";
            
            strncpy(jInstruction.op, binary, 6);

            strncpy(target, binary + 6, 26);
            jInstruction.target = strtol(target, NULL, 2);
            
            classify_J(jInstruction, hexadecimal, i);
        }
        else {
            printf("inst %d: %s unknown instruction\n", i, hexadecimal);
        }
    }

    free(array);

    return 0;
}