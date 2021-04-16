#include "stack.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void movebetween(Stack *u, Stack *v) {
  if ((stack_peek(v) == 0)
      || (!(stack_peek(u) == 0) && (stack_peek(u) < stack_peek(v)))) {
    printf("Move disk %d from peg %c to peg %c\n", stack_peek(u), u->name,
        v->name);
    stack_push(v, stack_pop(u));
  } else {
    printf("Move disk %d from peg %c to peg %c\n", stack_peek(v), v->name,
        u->name);
    stack_push(u, stack_pop(v));
  }
  return;
}

void ssolve(int numdisks) {
  // Create stacks
  Stack *a = stack_create(numdisks, 'A');
  Stack *b = stack_create(numdisks, 'B');
  Stack *c = stack_create(numdisks, 'C');

  // Push disks to stack A
  for (int d = numdisks; d > 0; d--) {
    stack_push(a, d);
  }

  if (numdisks % 2 == 0) {
    // If numdisks is even...
    while (1) {
      // Move disk between A and C
      movebetween(a, c);
      // Move disk between A and B
      movebetween(a, b);
      // Move disk between B and C
      movebetween(b, c);
      // Since number of moves is multiple of 3,
      // after every 3 moves, check if finished
      if (stack_empty(a) && stack_empty(c)) {
        break;
      }
    }
  } else {
    // If numdisks is odd...
    while (1) {
      // Move disk between A and B
      movebetween(a, b);
      // Since number of moves minus 1 is multiple of 3,
      // check here if finished
      if (stack_empty(a) && stack_empty(c)) {
        break;
      }
      // Move disk between A and C
      movebetween(a, c);
      // Move disk between B and C
      movebetween(b, c);
    }
  }

  // Delete stacks
  stack_delete(a);
  stack_delete(b);
  stack_delete(c);

  return;
}

void rsolve(int n, char start, char end, char help) {
  if (n == 1) {
    printf("Move disk %d from peg %c to peg %c\n", n, start, end);
    return;
  }
  rsolve(n - 1, start, help, end);
  printf("Move disk %d from peg %c to peg %c\n", n, start, end);
  rsolve(n - 1, help, end, start);
}

int main(int argc, char **argv) {

  // Intitialize
  int opt = 0;
  bool sgiven = false;
  bool rgiven = false;
  int numdisks = 5;

  // Use getopt to parse command-line arguments
  while ((opt = getopt(argc, argv, "srn:")) != -1) {
    switch (opt) {
    case 's':
      sgiven = true;
      break;
    case 'r':
      rgiven = true;
      break;
    case 'n':
      numdisks = atoi(optarg);
      break;
    }
  }

  if (sgiven) {
    // Print Header
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");

    // Solve
    ssolve(numdisks);

    // Print number of moves
    printf("\nNumber of moves: %d\n\n", (1 << numdisks) - 1);
  }
  if (rgiven) {
    // Print Header
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");

    // Solve
    rsolve(numdisks, 'A', 'B', 'C');

    // Print number of moves
    printf("\nNumber of moves: %d\n\n", (1 << numdisks) - 1);
  }

  return 0;
}
