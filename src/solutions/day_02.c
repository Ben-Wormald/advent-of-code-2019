#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../solution.h"
#include "../util/intcode.h"

int solve(FILE *fp) {
  char input[IC_INPUT_MAX];


  fgets(input, IC_INPUT_MAX, fp);

  ic_init(input);
  ic_fix(12, 2);

  return ic_run(0);
}
