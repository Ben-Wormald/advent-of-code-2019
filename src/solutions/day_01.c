#include <stdio.h>
#include <stdlib.h>
#include "../solution.h"

#define LINE_MAX 100

int get_fuel(int);

int solve_part_one(FILE *fp) {
  int total_fuel, fuel, mass;
  char line[LINE_MAX];

  while (fgets(line, LINE_MAX, fp) != NULL) {
    mass = atoi(line);
    fuel = mass / 3 -2;
    total_fuel += fuel;
  }
  return total_fuel;
}

int solve(FILE *fp) {
  int total_fuel, fuel, mass;
  char line[LINE_MAX];

  while (fgets(line, LINE_MAX, fp) != NULL) {
    fuel = atoi(line);

    while ((fuel = get_fuel(fuel)) > 0) {
      total_fuel += fuel;
    }
  }
  return total_fuel;
}

int get_fuel(int mass) {
  int fuel;

  fuel = mass / 3 - 2;
  return fuel >= 0 ? fuel : 0;
}
