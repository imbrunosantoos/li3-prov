#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct deque Deque;

Deque *create(void);

void push(Deque *deque, void *data);

void pushFront(Deque *deque, void *data);

void *pop(Deque *deque);

void *popFront(Deque *deque);

int size(Deque *deque); 

bool isEmpty(Deque *deque);

void reverse(Deque *deque); 

void printDeque(Deque *deque,void (*printFunc)(void *));

void destroy(Deque *deque);

#endif