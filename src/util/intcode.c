#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./intcode.h"

#define OP_ADD 1
#define OP_MULTIPLY 2
#define OP_HALT 99

int memory[IC_INPUT_MAX];
int i_ptr, i_count;

void ic_init(char *input_original) {
  char input[IC_INPUT_MAX];
  char *token;

  strcpy(input, input_original);

  token = strtok(input, ",");
  i_ptr = 0;

  while (token != NULL) {
    memory[i_ptr++] = atoi(token);
    token = strtok(NULL, ",");
  }

  i_count = i_ptr;
  i_ptr = 0;
}

int ic_run(int should_print) {
  int opcode, operand_1, operand_2, operand_3;


  if (should_print) {
    ic_print();
  }

  while ((opcode = memory[i_ptr]) != OP_HALT) {
    operand_1 = memory[i_ptr + 1];
    operand_2 = memory[i_ptr + 2];
    operand_3 = memory[i_ptr + 3];

    if (opcode == OP_ADD) {
      memory[operand_3] = memory[operand_1] + memory[operand_2];
    }
    else if (opcode == OP_MULTIPLY) {
      memory[operand_3] = memory[operand_1] * memory[operand_2];
    }
    else {
      printf("bad opcode %d at %d!", opcode, i_ptr);
      return 0;
    }

    if (should_print) {
      ic_print();
    }

    i_ptr += 4;
  }

  return memory[0];
}

void ic_fix(int noun, int verb) {
  memory[1] = noun;
  memory[2] = verb;
}

void ic_print() {
  int i;
  for (i = 0; i < i_count; i++) {
    printf("%4d ", memory[i]);
  }
  printf("\n");
}
