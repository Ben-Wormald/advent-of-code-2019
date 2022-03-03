#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../solution.h"

#define INPUT_MAX 1000

#define OP_ADD 1
#define OP_MULTIPLY 2
#define OP_HALT 99

void print_opcodes(int opcodes[], int op_count);
void fix_program(int opcodes[]);

int solve(FILE *fp) {
  char input[INPUT_MAX];
  char *token;

  int opcodes[INPUT_MAX];
  int op_ptr, op_count, opcode, op_1, op_2, op_3;


  fgets(input, INPUT_MAX, fp);

  token = strtok(input, ",");
  op_ptr = 0;

  while (token != NULL) {
    opcodes[op_ptr++] = atoi(token);
    token = strtok(NULL, ",");
  }

  fix_program(opcodes);

  op_count = op_ptr;
  op_ptr = 0;

  // print_opcodes(opcodes, op_count);

  while ((opcode = opcodes[op_ptr]) != OP_HALT) {
    op_1 = opcodes[op_ptr + 1];
    op_2 = opcodes[op_ptr + 2];
    op_3 = opcodes[op_ptr + 3];

    if (opcode == OP_ADD) {
      opcodes[op_3] = opcodes[op_1] + opcodes[op_2];
    }
    else if (opcode == OP_MULTIPLY) {
      opcodes[op_3] = opcodes[op_1] * opcodes[op_2];
    }
    else {
      printf("bad opcode %d at %d!", opcode, op_ptr);
      return -1;
    }

    // print_opcodes(opcodes, op_count);

    op_ptr += 4;
  }

  return opcodes[0];
}

void fix_program(int opcodes[]) {
  opcodes[1] = 12;
  opcodes[2] = 2;
}

void print_opcodes(int opcodes[], int op_count) {
  int i;
  for (i = 0; i < op_count; i++) {
    printf("%4d ", opcodes[i]);
  }
  printf("\n");
}
