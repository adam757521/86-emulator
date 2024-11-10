#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

BYTE prefixes[] = {
    0x66,
    0x67,
};

BYTE opcodes[] = {0x50, 0x58};

bool isInArray(BYTE array[], BYTE toCheck, int size);

#define OPERAND_SIZE_PREFIX 0x66
#define ADDRESS_SIZE_PREFIX 0x67

#define PUSH_OPCODE 0x50
#define POP_OPCODE 0x58

// testing code for my implementation for the basic instruction map

int main(void)
{
    // this program pushes eax and pops ax
    BYTE program[] = {0x50, 0x66, 0x58};
    int ip = 0;

    BYTE currentInstructionFlag = 0x0;

    while (ip < sizeof(program))
    {
        if (isInArray(prefixes, program[ip], sizeof(prefixes)))
        {
            currentInstructionFlag = program[ip];
            ip++;
        }

        if (isInArray(opcodes, program[ip], sizeof(opcodes)))
        {
            switch (program[ip])
            {
            case PUSH_OPCODE:
                printf("Pushing r%d\n", currentInstructionFlag == OPERAND_SIZE_PREFIX ? 16 : 32);
                break;
            case POP_OPCODE:
                printf("Popping r%d\n", currentInstructionFlag == OPERAND_SIZE_PREFIX ? 16 : 32);
                break;
            default:
                break;
            }
        }

        ip++;
    }

    return 0;
}

// basic binary search for speed (not necessary)
bool isInArray(BYTE array[], BYTE toCheck, int size)
{
    int start = 0;
    int end = size - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (array[mid] == toCheck)
        {
            return true;
        }
        else if (array[mid] < toCheck)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    return false;
}