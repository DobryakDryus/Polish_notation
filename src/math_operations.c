#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math_operations.h"
#include "stack_n_list.h"

double operations(struct list *list, double x, int *flag) {
  *flag = 1;
  struct stack *stack = stack_init(0);
  while (list) {
    if (list->type == OPERATION) {
      switch (list->value[0]) {
      case '+':
        stack->next->data = stack->next->data + stack->data;
        stack = stack_pop(stack);
        break;

      case '-':
        stack->next->data = stack->next->data - stack->data;
        stack = stack_pop(stack);
        break;

      case '*':
        stack->next->data = stack->next->data * stack->data;
        stack = stack_pop(stack);
        break;

      case '/':
        if (stack->data != 0) {
          stack->next->data = stack->next->data / stack->data;
          stack = stack_pop(stack);
        } else {
          *flag = 0;
        }
        break;
      default:
        break;
      }
    } else if (list->type == NUMBER) {
      stack = stack_push(atof(list->value), stack);

    } else if (list->type == VARIABLE) {
      stack = stack_push(x, stack);

    } else if (list->value[0] == SIN) {
      stack->data = sin(stack->data);
    } else if (list->value[0] == COS) {
      stack->data = cos(stack->data);
    } else if (list->value[0] == TAN) {
      if (cos(stack->data) != 0) {
        stack->data = tan(stack->data);
      } else {
        *flag = 0;
      }
    } else if (list->value[0] == CTG) {
      if (sin(stack->data) != 0) {
        stack->data = cos(stack->data) / sin(stack->data);
      } else {
        *flag = 0;
      }
    } else if (list->value[0] == SQRT) {
      if (stack->data >= 0) {
        stack->data = sqrt(stack->data);
      } else {
        *flag = 0;
      }
    } else if (list->value[0] == LN) {
      if (stack->data > 0) {
        stack->data = log(stack->data);
      } else {
        *flag = 0;
      }
    }
    list = list->next;
  }
  double result = stack->data;
  stack_destroy(stack);
  return result;
}
