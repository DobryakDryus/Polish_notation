#include "stack_str.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node *init(char operator, int p) {
  struct node *tmp = malloc(sizeof(struct node));
  tmp->data = operator;
  tmp->prioritet = p;
  tmp->next = NULL;
  return (tmp);
}

struct node *push(char operator, int p, struct node *root) {
  struct node *tmp = malloc(sizeof(struct node));
  tmp->data = operator;
  tmp->prioritet = p;
  tmp->next = root;
  return tmp;
}

struct node *pop(struct node *root) {
  struct node *tmp = root;
  root = root->next;
  free(tmp);
  return root;
}

char *transfer(char *str) {
  int i = 0;
  int num_flag = 0;
  int k = 0;
  char *num_x = "1234567890x";
  char *polska = malloc(strlen(str) * 3 * sizeof(char));
  char *bin_fir = "+-";
  char *bin_sec = "*/";
  struct node *root = NULL;
  while (str[i] != '\0') {
    if (strchr(num_x, str[i]) != NULL && !num_flag) {
      polska[k++] = ' ';
      polska[k++] = str[i];
      num_flag = 1;
    } else if ((strchr(num_x, str[i]) != NULL || str[i] == '.') && num_flag) {
      polska[k++] = str[i];
    } else if (strchr(bin_fir, str[i]) != NULL) {
      root = pars(root, str[i], 1, polska, &k);
      num_flag = 0;
    } else if (strchr(bin_sec, str[i]) != NULL) {
      root = pars(root, str[i], 2, polska, &k);
      num_flag = 0;
    } else if (str + i == strstr(str + i, "sin")) {
      root = pars(root, 's', 3, polska, &k);
      num_flag = 0;
      i = i + 2;
    } else if (str + i == strstr(str + i, "sqrt")) {
      root = pars(root, 'q', 3, polska, &k);
      num_flag = 0;
      i = i + 3;
    } else if (str + i == strstr(str + i, "cos")) {
      root = pars(root, 'c', 3, polska, &k);
      num_flag = 0;
      i = i + 2;
    } else if (str + i == strstr(str + i, "ctg")) {
      root = pars(root, 'g', 3, polska, &k);
      num_flag = 0;
      i = i + 2;
    } else if (str + i == strstr(str + i, "tan")) {
      root = pars(root, 't', 3, polska, &k);
      num_flag = 0;
      i = i + 2;
    } else if (str + i == strstr(str + i, "ln")) {
      root = pars(root, 'l', 3, polska, &k);
      num_flag = 0;
      i++;
    } else if (str[i] == '(') {
      num_flag = 0;
      root = pars(root, str[i], 0, polska, &k);
    } else if (str[i] == ')') {
      num_flag = 0;
      while (root->data != '(') {
        polska[k++] = ' ';
        polska[k++] = root->data;
        root = pop(root);
      }
      root = pop(root);
      if (root && root->prioritet == 3) {
        polska[k++] = ' ';
        polska[k++] = root->data;
        root = pop(root);
      }
    }
    i++;
  }
  while (root) {
    polska[k++] = ' ';
    polska[k++] = root->data;
    root = pop(root);
  }
  free(root);
  polska[k] = '\0';
  return polska;
}

struct node *pars(struct node *root, char sym, int priority, char *polska,
                  int *k) {
  if (!root) {
    root = init(sym, priority);
  } else {
    root = push(sym, priority, root);
    struct node *tmp = root;
    if (sym != '(') {
      while ((tmp->next) && (tmp->next->data != '(')) {
        if (priority <= (tmp->next->prioritet)) {
          polska[(*k)++] = ' ';
          polska[(*k)++] = tmp->next->data;
          tmp->next = pop(tmp->next);
        } else {
          tmp = tmp->next;
        }
      }
    }
  }
  return root;
}
