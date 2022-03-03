#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../solution.h"

#define LINE_MAX 2048

typedef struct point Point;
struct point {
  int x;
  int y;
};

typedef struct segment Segment;
struct segment {
  Point start;
  Point end;
};

int build_wire(char *line, Segment *wire);
Point get_new_point(Point *current_pt, char *delta);
int test_intersection(Segment *seg_a, Segment *seg_b);
Point get_intersection(Segment *seg_a, Segment *seg_b);
int manhattan_distance(Point *pt);

int solve(FILE *fp) {
  char line[LINE_MAX];
  char *delta;
  int lines;
  Segment wire_a[LINE_MAX];
  Segment wire_b[LINE_MAX];
  Segment *wire;
  Segment new_segment;
  int wire_a_len, wire_b_len, wire_a_ptr, wire_b_ptr, intersects, distance, closest;
  Point intersection;


  fgets(line, LINE_MAX, fp);
  wire_a_len = build_wire(line, wire_a);

  fgets(line, LINE_MAX, fp);
  wire_b_len = build_wire(line, wire_b);

  closest = -1;

  for (wire_a_ptr = 0; wire_a_ptr < wire_a_len; wire_a_ptr++) {
    for (wire_b_ptr = 0; wire_b_ptr < wire_b_len; wire_b_ptr++) {
      intersects = test_intersection(&wire_a[wire_a_ptr], &wire_b[wire_b_ptr]);

      if (intersects) {
        intersection = get_intersection(&wire_a[wire_a_ptr], &wire_b[wire_b_ptr]);
        distance = manhattan_distance(&intersection);

        if (distance < closest || closest == -1) {
          closest = distance;
        }
      }
    }
  }

  return closest;
}

int build_wire(char *line, Segment *wire) {
  int wire_ptr;
  char *delta;
  Point current_pt, new_pt;


  wire_ptr = 0;
  current_pt = (Point) { 0, 0 };

  delta = strtok(line, ",");

  while (delta != NULL) {
    new_pt = get_new_point(&current_pt, delta);

    wire[wire_ptr++] = (Segment) {
      (Point) { current_pt.x, current_pt.y },
      (Point) { new_pt.x, new_pt.y }
    };

    current_pt = new_pt;

    delta = strtok(NULL, ",");
  }

  return wire_ptr;
}

Point get_new_point(Point *current_pt, char *delta) {
  char direction;
  int magnitude, x, y;


  x = current_pt->x;
  y = current_pt->y;
  direction = *(delta++);
  magnitude = atoi(delta);

  if (direction == 'U') {
    y += magnitude;
  }
  if (direction == 'D') {
    y -= magnitude;
  }
  if (direction == 'L') {
    x -= magnitude;
  }
  if (direction == 'R') {
    x += magnitude;
  }

  return (Point) { x, y };
}

int test_intersection(Segment *seg_a, Segment *seg_b) {
  int orthogonal_x, orthogonal_y, between_x, between_y;


  if (seg_a->start.x == 0 && seg_b->start.x == 0) {
    return 0;
  }

  orthogonal_x = seg_a->start.x == seg_a->end.x && seg_b->start.y == seg_b->end.y;
  orthogonal_y = seg_a->start.y == seg_a->end.y && seg_b->start.x == seg_b->end.x;

  if (orthogonal_x) {
    between_x = (seg_a->start.x >= seg_b->start.x && seg_a->start.x <= seg_b->end.x)
      || (seg_a->start.x <= seg_b->start.x && seg_a->start.x >= seg_b->end.x);

    between_y = (seg_b->start.y >= seg_a->start.y && seg_b->start.y <= seg_a->end.y)
      || (seg_b->start.y <= seg_a->start.y && seg_b->start.y >= seg_a->end.y);

    if (between_x && between_y) {
      return 1;
    }
  }

  if (orthogonal_y) {
    between_x = (seg_b->start.x >= seg_a->start.x && seg_b->start.x <= seg_a->end.x)
      || (seg_b->start.x <= seg_a->start.x && seg_b->start.x >= seg_a->end.x);

    between_y = (seg_a->start.y >= seg_b->start.y && seg_a->start.y <= seg_b->end.y)
      || (seg_a->start.y <= seg_b->start.y && seg_a->start.y >= seg_b->end.y);

    if (between_x && between_y) {
      return 1;
    }
  }

  return 0;
}

Point get_intersection(Segment *seg_a, Segment *seg_b) {
  if (seg_a->start.x == seg_a->end.x) {
    return (Point) {
      seg_a->start.x, seg_b->start.y
    };
  }
  else {
    return (Point) {
      seg_b->start.x, seg_a->start.y
    };
  }
}

int manhattan_distance(Point *pt) {
  return abs(pt->x) + abs(pt->y);
}
