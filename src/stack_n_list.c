#include <stdio.h>
#include <stdlib.h>

#include "stack_n_list.h"

struct list *list_init(char *value, int type) {
  struct list *head;
  head = (struct list *)malloc(sizeof(struct list));
  head->value = value;
  head->type = type;
  head->next = NULL;
  return (head);
}

struct list *list_add(struct list *elem, char *value, int type) {
  struct list *tmp, *p;
  tmp = (struct list *)malloc(sizeof(struct list));
  p = elem->next;
  elem->next = tmp;
  tmp->value = value;
  tmp->type = type;
  tmp->next = p;
  return (tmp);
}

void list_destroy(struct list *root) {
  struct list *tmp;
  while (root != NULL) {
    tmp = root->next;
    free(root);
    root = tmp;
  }
}

//////

struct stack *stack_init(double value) {
  struct stack *head = (struct stack *)malloc(sizeof(struct stack));
  head->data = value;
  head->next = NULL;
  return (head);
}

struct stack *stack_push(double value, struct stack *root) {
  struct stack *NewSt = (struct stack *)malloc(sizeof(struct stack));
  NewSt->next = root;
  NewSt->data = value;
  return NewSt;
}

struct stack *stack_pop(struct stack *root) {
  struct stack *PrSt = root->next;
  free(root);
  return PrSt;
}

void stack_destroy(struct stack *root) {
  struct stack *PrSt;
  while (root != NULL) {
    PrSt = root->next;
    free(root);
    root = PrSt;
  }
}
