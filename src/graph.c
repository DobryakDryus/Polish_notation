#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "math_operations.h"
#include "stack_n_list.h"
#include "graph.h"

int print_fuction(struct list *tokens) {
    int flag = 1;
  double y_points[X_SIZE] = {0};
  int counter = 0;
  for (double step = 0; step < SCREEN_X_LENGTH; step += SCREEN_X_STEP) {
    y_points[counter] = operations(tokens, step, &flag);
    if (flag == 0) {
        y_points[counter] = -255;
        flag = 1;
    }
    counter++;
  }
  int screen_cord_y;
  for (int y = Y_SIZE - 1; y >= 0; y--) {
    for (int x = 0; x < X_SIZE; x++) {
      screen_cord_y = (y_points[x] + 1) * Y_SIZE / 2;
      if ((int)round(screen_cord_y) == Y_SIZE - y) {
        printf("*");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  return 1;
}
