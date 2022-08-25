#include "stack_n_list.h"
#include "stack_str.h"
#include "graph.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int operator_check(char *str, int n, int flag_next);
void spaces_fix(char *str);
int brackets(const char *str);
void unar_nul(char *str, int n);
int first_last_sym(char *str, int n);
int first_sym_x(char *str, int n);
void change(char *str, struct list *list);

int main() {
  char *s;
  int n = 0;
  s = malloc(sizeof(char));
  int flag = 1;
  while (flag) {
    n++;
    char* s1 = realloc(s, n * sizeof(char));
    if (s1 != NULL)
      s = s1;
    scanf("%c", &s[n - 1]);
    if (s[0] == '\n') {
      break;
    }
    if (s[n - 1] == '\n') {
      s[n - 1] = '\0';
      flag = 0;
    }
  }
  if (s[0] == '\n') { printf("syntax error");
  } else {
  char *s1 = realloc(s, 2 * n * sizeof(char));
  if (s1 != NULL)
      s = s1;
  spaces_fix(s);
  unar_nul(s, strlen(s));
  if (!(brackets(s)) && first_last_sym(s, strlen(s)) &&
      operator_check(s, strlen(s), 1)) {
    char *t = transfer(s);
    if (t[0] == ' ') {
      for (int i = 0; t[i] != '\0'; i++)
        t[i] = t[i + 1];
    }
    struct list *list = list_init(NULL, 0);
    struct list *start = list;

    change(t, list);
    print_fuction(start);
    list_destroy(start);
    free(t);
  } else {
    printf("syntax error");
  }
  }
  free(s);
  return 0;
}

void change(char *str, struct list *list) {
  char numbersx[11] = "1234567890";
  char operations[5] = "+-/*";
  char *token;
  token = strtok(str, " ");
  list->value = token;
  if (strchr(numbersx, token[0]) != NULL)
    list->type = NUMBER;
  else if (strchr(operations, token[0]) != NULL)
    list->type = OPERATION;
  else if (token[0] == 'x')
    list->type = VARIABLE;
  else
    list->type = FUNCTION;
  while (token != NULL) {
    if (strchr(numbersx, token[0]) != NULL) {
      list = list_add(list, token, NUMBER);
    } else if (strchr(operations, token[0]) != NULL) {
      list = list_add(list, token, OPERATION);
    } else if (token[0] == 'x') {
      list = list_add(list, token, VARIABLE);
    } else {
      list = list_add(list, token, FUNCTION);
    }
    token = strtok(NULL, " ");
  }
}

void unar_nul(char *str, int n) {
  if (str[0] == '-') {
    for (int j = n; j > 0; j--) {
      str[j] = str[j - 1];
    }
    n++;
    str[0] = '0';
    str[n] = '\0';
  }
  for (int i = 1; i < n; i++) {
    if (str[i] == '-' && str[i - 1] == '(') {
      for (int j = n + 1; j > i; j--)
        str[j] = str[j - 1];
      str[i] = '0';
      n++;
    }
  }
}

int first_last_sym(char *str, int n) {
  int flag = 1;
  char numbersx[12] = "1234567890x";
  if (str[0] == '+' || str[0] == '/' || str[0] == '*' || str[0] == '.')
    flag = 0;
  if (str[n - 1] == '+' || str[n - 1] == '/' || str[n - 1] == '*' ||
      str[n - 1] == '-')
    flag = 0;
  if (str[0] == 'x' && (strchr(numbersx, str[1]) != NULL || str[1] == '('))
    flag = 0;
  if (str[n - 1] == 'x' && n - 1 == 0 &&
      (strchr(numbersx, str[n - 2]) != NULL || str[n - 2] == ')'))
    flag = 0;
  if (str[0] == 'x' && 0 == n-1)
    flag = 1;
  return flag;
}

int operator_check(char *str, int n, int flag_next) {
  int flag = 1;
  char numbers[11] = "1234567890";
  char numbers_x[12] = "1234567890x";
  if (str[0] == '+')
    flag = 0;
  for (int i = 0; i < n && flag; i++) {
    if (str[i] == 's' && (str + i == strstr(str + i, "sqrt("))) {
      i = i + 3;
    } else if (str[i] == 's' && (str + i == strstr(str + i, "sin("))) {
      i = i + 2;
    } else if (str[i] == 'c' && (str + i == strstr(str + i, "cos("))) {
      i = i + 2;
    } else if  (str[i] == 'c' && (str + i == strstr(str + i, "ctg("))) {
      i = i + 2;
    } else if  (str[i] == 't' && (str + i == strstr(str + i, "tan("))) {
      i = i + 2;
    } else if (str[i] == 'l' && (str + i == strstr(str + i, "ln("))) {
      i = i + 1;
    } else if  ((strchr("+*/-", str[i]) != NULL && flag_next) || (str[i] == '(')) {
      flag = operator_check(str + i + 1, 1, 0);
    } else if  ((str[i] == ')' && flag_next) ||
               (strchr(numbers, str[i]) != NULL) ||
               (str[i] == '.' && ((str[i - 1] >= 48 && str[i - 1] <= 57) &&
                                  (str[i + 1] >= 48 && str[i + 1] <= 57)))) {
    } else if  (str[i] == 'x' && (i == 0 || i == n - 1)) {
    } else if (str[i] == 'x' && strchr(numbers_x, str[i + 1]) == NULL &&
               strchr(numbers_x, str[i - 1]) == NULL && str[i + 1] != '(' &&
               str[i - 1] != ')') {
    } else {
      flag = 0;
    }
  }
  return flag;
}

void spaces_fix(char *str) {
  char *str_space = strchr(str, ' ');
  while (str_space != NULL) {
    for (int i = 0; str_space[i] != '\0'; i++)
      str_space[i] = str_space[i + 1];
    str_space = strchr(str, ' ');
  }
}

int brackets(const char *str) {
  int i = 0;
  int x = 0;
  while (str[i] != '\0') {
    if (str[i] == '(')
      x++;
    if (str[i] == ')')
      x--;
    if (x < 0)
      return x;
    i++;
  }
  return x;
}
