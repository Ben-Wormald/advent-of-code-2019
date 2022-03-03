#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./intcode.h"

#define IC_INPUT_MAX 1024

#define OP_ADD 1
#define OP_MULTIPLY 2
#define OP_HALT 99

char input[IC_INPUT_MAX];
char *token;

int opcodes[IC_INPUT_MAX];
int op_ptr, op_count, opcode;

void ic_init(char *input) {
  token = strtok(input, ",");
  op_ptr = 0;

  while (token != NULL) {
    opcodes[op_ptr++] = atoi(token);
    token = strtok(NULL, ",");
  }

  op_count = op_ptr;
  op_ptr = 0;
}

int ic_run(int should_print) {
  int op_1, op_2, op_3;


  if (should_print) {
    ic_print();
  }

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

    if (should_print) {
      ic_print();
    }

    op_ptr += 4;
  }

  return opcodes[0];
}

void ic_fix(int noun, int verb) {
  opcodes[1] = noun;
  opcodes[2] = verb;
}

void ic_print() {
  int i;
  for (i = 0; i < op_count; i++) {
    printf("%4d ", opcodes[i]);
  }
  printf("\n");
}
