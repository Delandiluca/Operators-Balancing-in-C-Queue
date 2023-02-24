#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Queue {
  int init;
  int end;
  int size;
  char *object;
} Queue; 


int isFull(Queue p);
int isEmpty(Queue p);
void createEmptyQueue(Queue *p, int size);
int isOpenOperator(char c);
int isCloseOperator(char c); 
void push(Queue *p, char elem);
char pop(Queue *p);
char peek(Queue *p);
void printQueue(Queue *p);
int validateOperator(char *op, Queue *p);


void createEmptyQueue(Queue *p, int size) {
  p->init = 0;
  p->end = -1;
  p->size = size;
  p->object = (char *)malloc(size * sizeof(char));
}

int isEmpty(Queue p) {
  return ((p.init <= -1) || (p.init > p.end));
}

int isFull(Queue p) {
  return (p.end == (MAX_SIZE - 1));
}

void push(Queue *p, char elem) {
  if (!isFull(*p)) {
    p->end++;
    p->object[p->end] = elem;
  } else {
    puts("\nError: Stack Overflow");
    exit(1);
  }
}

char pop(Queue *p) {
  if (!isEmpty(*p)) {
    char element = p->object[p->init];
    p->init++;
    return element;
  } else {
    puts("\nError: Stack Underflow");
    exit(1);
  }
}

char peek(Queue *p) { 
  return p->object[p->init];
}

void printQueue(Queue *p) {
  if (!isEmpty(*p)) {
    for (int i = 0; p->init <= i <= p->end; i++) {
      printf("\nCaracter %c ", p->object[i]);
    }
  } else {
    puts("\nError: Stack Empty");
    exit(1);
  }
}

int isOpenOperator(char c) {
  return (c == '(' || c == '{' || c == '[' || c == '<');
}

int isCloseOperator(char c) {
  return (c == ')' || c == '}' || c == ']' || c == '>');
}

int validateOperator(char *op, Queue *p) { 
  int i;
  for (i = 0; i < strlen(op); i++) {
    if (isOpenOperator(op[i])) {
      push(p, op[i]);
    } else if (isCloseOperator(op[i])) {
      if (!isEmpty(*p)) {
        char popped = pop(p);
        if ((op[i] == ')' && popped != '(') ||
            (op[i] == '}' && popped != '{') ||
            (op[i] == ']' && popped != '[') ||
            (op[i] == '>' && popped != '<')) {
          return 0;
        }
      } else {
        return 0;
      }
    }
  }
  return isEmpty(*p);
}

int main(void) {

  Queue queue;

  while (1) {
    createEmptyQueue(&queue, MAX_SIZE);

    char operators[MAX_SIZE];
    puts("\nInsira a operação: ");
    scanf("%s", operators);

    printf("\nOperação %s",
           (validateOperator(operators, &queue)) ? "Válida" : "Inválida");
  }

  return 0;
}
