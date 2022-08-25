#ifndef SRC_STACK_STR_H_
#define SRC_STACK_STR_H_

struct node {
  struct node *next;
  char data;
  int prioritet;
};

struct node *init(char operator, int p);
struct node* push(char operator, int p, struct node *root);
struct node* pop(struct node* root);
char * transfer(char *str);
struct node* pars(struct node* root, char sym, int priority, char* polska, int *k);


#endif  //  SRC_STACK_STR_H_
