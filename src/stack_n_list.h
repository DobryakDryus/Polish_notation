#ifndef SRC_STACK_N_LIST_H_
#define SRC_STACK_N_LIST_H_

#include <stdlib.h>



struct list {
  char* value;
  int type;
  struct list *next;
};



struct list *list_init(char *value, int type);
struct list *list_add(struct list *elem, char *value, int type);
void list_destroy(struct list *root);

struct stack {
  double data;
  struct stack *next;
};

struct stack *stack_init(double value);
struct stack *stack_push(double value, struct stack *root);
struct stack *stack_pop(struct stack *root);
void stack_destroy(struct stack *root);

enum {
  NUMBER,
  OPERATION,
  VARIABLE,
  FUNCTION
};



#endif  //  SRC_STACK_N_LIST_H_
