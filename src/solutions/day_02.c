#include <stdio.h>
#include "../solution.h"
#include "../util/intcode.h"

#define TARGET_RESULT 19690720

int solve_part_one(FILE *fp) {
  char input[IC_INPUT_MAX];


  fgets(input, IC_INPUT_MAX, fp);

  ic_init(input);
  ic_fix(12, 2);

  return ic_run(0);
}

int solve(FILE *fp) {
  char input[IC_INPUT_MAX];
  int noun, verb, result;


  fgets(input, IC_INPUT_MAX, fp);

  for (noun = 0; noun < 100; noun++) {
    for (verb = 0; verb < 100; verb++) {
      ic_init(input);
      ic_fix(noun, verb);

      result = ic_run(0);

      if (result == TARGET_RESULT) {
        return 100 * noun + verb;
      }
    }
  }

  return 0;
}
