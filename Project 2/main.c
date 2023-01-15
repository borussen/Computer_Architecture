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

void HextoBin(char *hex, char *bin) {
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

int classify_R(struct R_type instruction, unsigned char *data_memory, int *registers, int pc) {
    // add
    if (strncmp(instruction.function, "100000", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] + registers[instruction.rt];
    }
    // addu
    else if (strncmp(instruction.function, "100001", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] + registers[instruction.rt];
    }
    // and
    else if (strncmp(instruction.function, "100100", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] & registers[instruction.rt];
    }
    // jr
    else if (strncmp(instruction.function, "001000", 6) == 0) {
        return (registers[instruction.rs] / 4);
    }
    // or
    else if (strncmp(instruction.function, "100101", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] | registers[instruction.rt];
    }
    // sll
    else if (strncmp(instruction.function, "000000", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rt] << instruction.shamt;
    }
    // slt
    else if (strncmp(instruction.function, "101010", 6) == 0) {
        if (registers[instruction.rs] < registers[instruction.rt]) {
            registers[instruction.rd] = 1;
        }
        else {
            registers[instruction.rd] = 0;
        }
    }
    // sltu
    else if (strncmp(instruction.function, "101011", 6) == 0) {
        if ((unsigned int) registers[instruction.rs] < (unsigned int) registers[instruction.rt]) {
            registers[instruction.rd] = 1;
        }
        else {
            registers[instruction.rd] = 0;
        }
    }
    // srl
    else if (strncmp(instruction.function, "000010", 6) == 0) {
        registers[instruction.rd] = (unsigned int) registers[instruction.rt] >> instruction.shamt;
    }
    // sub
    else if (strncmp(instruction.function, "100010", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] - registers[instruction.rt];
    }
    // subu
    else if (strncmp(instruction.function, "100011", 6) == 0) {
        registers[instruction.rd] = registers[instruction.rs] - registers[instruction.rt];
    }
    // syscall
    else if (strncmp(instruction.function, "001100", 6) == 0) {
        if (registers[2] == 1) {
            printf("%d", registers[4]);
        }
        else if (registers[2] == 4) {
            int i = 0;
            while (1) {
                printf("%c", data_memory[registers[4] - 0x10000000 + i]);
                if (data_memory[registers[4] - 0x10000000 + i] == 0x00 || data_memory[registers[4] - 0x10000000 + i] == 0xFF) {
                    break;
                }
                i++;
            }
        }
        else if (registers[2] == 5) {
            scanf("%d", &registers[2]);
        }
        else {
            printf("unknown instruction\n");
            return -1;
        }
    }
    // remaining r-type instructions
    else {
        printf("unknown instruction\n");
        return -1;
    }
    registers[0] = 0;
    return pc + 1;
}

int classify_I(struct I_type instruction, unsigned char *data_memory, int *registers, int pc) {
    // addi
    if (strncmp(instruction.op, "001000", 6) == 0) {
        registers[instruction.rt] = registers[instruction.rs] + instruction.immediate;
    }
    // addiu
    else if (strncmp(instruction.op, "001001", 6) == 0) {
        registers[instruction.rt] = registers[instruction.rs] + instruction.immediate;
    }
    // andi
    else if (strncmp(instruction.op, "001100", 6) == 0) {
        if (instruction.immediate < 0) {
            instruction.immediate += 65536;
        }
        registers[instruction.rt] = registers[instruction.rs] & instruction.immediate;
    }
    // beq
    else if (strncmp(instruction.op, "000100", 6) == 0) {
        if (registers[instruction.rs] == registers[instruction.rt]) {
            return (pc + 1) + instruction.immediate;
        }
    }
    // bne
    else if (strncmp(instruction.op, "000101", 6) == 0) {
        if (registers[instruction.rs] != registers[instruction.rt]) {
            return (pc + 1) + instruction.immediate;
        }
    }
    // lui
    else if (strncmp(instruction.op, "001111", 6) == 0) {
        registers[instruction.rt] = instruction.immediate;
        registers[instruction.rt] = registers[instruction.rt] << 16;
    }
    // lw
    else if (strncmp(instruction.op, "100011", 6) == 0) {
        registers[instruction.rt] = ((data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000)] % 256) << 24)
                                     + ((data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 1] % 256) << 16)
                                     + ((data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 2] % 256) << 8)
                                     + (data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 3] % 256);
    }
    // ori
    else if (strncmp(instruction.op, "001101", 6) == 0) {
        registers[instruction.rt] = registers[instruction.rs] | instruction.immediate;
    }
    // slti
    else if (strncmp(instruction.op, "001010", 6) == 0) {
        if (registers[instruction.rs] < instruction.immediate) {
            registers[instruction.rt] = 1;
        }
        else {
            registers[instruction.rt] = 0;
        }
    }
    // sltiu
    else if (strncmp(instruction.op, "001011", 6) == 0) {
        if ((unsigned int) registers[instruction.rs] < (unsigned int) instruction.immediate) {
            registers[instruction.rt] = 1;
        }
        else {
            registers[instruction.rt] = 0;
        }
    }
    // sw
    else if (strncmp(instruction.op, "101011", 6) == 0) {
        data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000)] = (registers[instruction.rt] >> 24) % 256;
        data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 1] = (registers[instruction.rt] >> 16) % 256;
        data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 2] = (registers[instruction.rt] >> 8) % 256;
        data_memory[(registers[instruction.rs] + instruction.immediate - 0x10000000) + 3] = (registers[instruction.rt]) % 256;
    }
    // remaining i-type instructions
    else {
        printf("unknown instruction\n");
        return -1;
    }
    registers[0] = 0;
    return pc + 1;
}

int classify_J(struct J_type instruction, int *registers, int pc) {
    // j
    if (strncmp(instruction.op, "000010", 6) == 0) {
        return instruction.target;
    }
    // jal
    else if (strncmp(instruction.op, "000011", 6) == 0) {
        registers[31] = (pc + 1) * 4;
        return instruction.target;
    }
    // remaining j-type instructions
    else {
        printf("unknown instruction\n");
        return -1;
    }
}


int main(int argc, char **argv) {

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "USAGE: EXECUTABLE N INSTRUCTION_BINARY_FILE DATA_BINARY_FILE(OPTIONAL)\n");
        return 1;
    }

    int pc = 0;
    int *registers = (int*)calloc(32, sizeof(int));
    int *instruction_memory = (int*)malloc(sizeof(int) * 16384);
    unsigned char *data_memory = (unsigned char*)malloc(sizeof(char) * 65536);

    for (int i = 0; i < 16384; i++) {
        instruction_memory[i] = 0xFFFFFFFF;
    }
    for (int i = 0; i < 65536; i++) {
        data_memory[i] = 0xFF;
    }

    int N = atoi(argv[1]);
    FILE *inst = fopen(argv[2], "rb");
    if (inst == NULL) {
        fprintf(stderr, "ERROR: WRONG INSTRUCTION FILE NAME\n");
        return 1;
    }

    fseek(inst, 0, SEEK_END);
    int size = ftell(inst);
    fseek(inst, 0, SEEK_SET);

    int *array = (int*)malloc(size);
    memset(array, 0, size);

    fread(array, sizeof(int), size / sizeof(int), inst);

    fclose(inst);

    for (int i = 0; i < size / sizeof(int); i++) {
        instruction_memory[i] = swapEndian(array[i]);
    }

    if (argc == 4) {
        FILE *data = fopen(argv[3], "rb");

        if (data == NULL) {
            fprintf(stderr, "ERROR: WRONG DATA FILE NAME\n");
            return 1;
        }

        fseek(data, 0, SEEK_END);
        size = ftell(data);
        fseek(data, 0, SEEK_SET);

        unsigned char* array = (unsigned char*)malloc(size);
        memset(array, 0, size);

        fread(array, sizeof(char), size / sizeof(char), data);

        for (int i = 0; i < size / sizeof(char); i++) {
            data_memory[i] = array[i];
        }

        fclose(data);
    }

    for (int i = 0; i < N; i++) {

        char hexadecimal[9] = "";
        sprintf(hexadecimal, "%08x", instruction_memory[pc]);
        char binary[33] = "";
        HextoBin(hexadecimal, binary);

        int temp = pc;

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

            pc = classify_R(rInstruction, data_memory, registers, pc);
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

            pc = classify_I(iInstruction, data_memory, registers, pc);
        }
        else if (strncmp(binary, "00001", 5) == 0) {
            J_type jInstruction = { 0, };
            char target[27] = "";

            strncpy(jInstruction.op, binary, 6);

            strncpy(target, binary + 6, 26);
            jInstruction.target = strtol(target, NULL, 2);

            pc = classify_J(jInstruction, registers, pc);
        }
        else {
            printf("unknown instruction\n");
            pc = -1;
        }

        if (pc == -1) {
            pc = temp + 1;
            break;
        }
    }

    for (int i = 0; i < 32; i++) {
        printf("$%d: 0x%08x\n", i, registers[i]);
    }
    printf("PC: 0x%08x\n", pc * 4);

    free(registers);
    free(instruction_memory);
    free(data_memory);
    free(array);

    return 0;
}