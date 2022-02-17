#include <stdio.h>
#include "solution.h"

#define ARG_MAX 100

int main(int argc, char *argv[]) {
  int result;
  char input[ARG_MAX];
  FILE *fp;

  if (argc != 2) {
    printf("no day specified\n");
    return 1;
  }

  sprintf(input, "./input/%s", argv[1]);

  if ((fp = fopen(input, "r")) == NULL) {
    printf("error opening input file %s\n", input);
    return 1;
  }

  result = solve(fp);

  printf("%d\n", result);
  fclose(fp);
}
