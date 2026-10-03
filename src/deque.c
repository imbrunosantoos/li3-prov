#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"

typedef struct no {
    void *data;
    struct no *prev;
    struct no *next;
} No;

struct deque {
    No *head;
    No *tail;
    int tamanho;
    bool reversed;
};

Deque *create(void) {
    Deque *deque = malloc(sizeof(Deque));
    if (deque == NULL) return NULL; 

    deque -> head = NULL;
    deque -> tail = NULL;
    deque -> tamanho = 0;
    deque -> reversed = false;

    return deque;
}

static void insereHead(Deque *deque, void *data) {
    No *novo = malloc(sizeof(No));
    novo->data = data;

    if (deque->head == NULL) {
        novo->next = NULL;
        novo->prev = NULL;
        deque->head = novo;
        deque->tail = novo;
    } else {
        novo->next = deque->head;
        novo->prev = NULL;
        deque->head->prev = novo;
        deque->head = novo;
    }
    deque->tamanho++;
}

static void insereTail(Deque *deque, void *data) {
    No *novo = malloc(sizeof(No));
    novo->data = data;

    if (deque->tail == NULL) {
        novo->next = NULL;
        novo->prev = NULL;
        deque->head = novo;
        deque->tail = novo;
    } else {
        deque->tail->next = novo;
        novo->prev = deque->tail;
        novo->next = NULL;
        deque->tail = novo;
    }
    deque->tamanho++;
}

void pushFront(Deque *deque, void *data) {
    if (deque->reversed)
        insereTail(deque, data);
    else
        insereHead(deque, data);
}

void push(Deque *deque, void *data) {
    if (deque->reversed)
        insereHead(deque, data);
    else
        insereTail(deque, data);
}


static void *retiraHead (Deque *deque) {

    if (!(deque -> head == NULL)){
        void *valor = deque -> head -> data;
        if (deque -> tamanho == 1){
            free (deque -> head);
            deque -> head = NULL;
            deque -> tail = NULL;
        }
        else {
            No *proximo = deque -> head -> next;
            proximo -> prev = NULL;
            free (deque -> head);
            deque -> head = proximo;
        }
        deque -> tamanho --;
        return valor;
    }
    else return NULL;

}

static void *retiraTail (Deque *deque){
    if (!(deque->tail == NULL)){
        void *valor = deque -> tail -> data;

        if (deque -> tamanho == 1){
            free (deque -> tail);
            deque -> head = NULL;
            deque -> tail = NULL;
        }
        else{
            No *anterior = deque->tail->prev;
            anterior -> next = NULL;
            free(deque -> tail);
            deque -> tail = anterior;
        }
        deque -> tamanho --;
        return valor;
    }else return NULL;

}

void *pop(Deque *deque){
     if (deque -> reversed)
        return retiraHead (deque);
    else
        return retiraTail (deque);
    
}

void *popFront(Deque *deque){
    if (deque -> reversed)
        return retiraTail (deque);
    else
        return retiraHead (deque);
}

int size(Deque *deque){
    return deque -> tamanho;
}

bool isEmpty(Deque *deque){
    return deque -> tamanho == 0;
}


void destroy(Deque *deque){
    No *atual = deque -> head;
    while (atual != NULL){
        No *proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    free(deque);
}

void reverse(Deque *deque){
   deque -> reversed = !(deque -> reversed);
} 

void printDeque(Deque *deque,void (*printFunc)(void *)){
    if (deque -> head != NULL){
        if (deque -> reversed){
            No *atual = deque -> tail;
            while (atual != NULL){
                printFunc (atual -> data);
                atual = atual -> prev;
            }
        }
        else{
            No *atual = deque -> head;
            while (atual != NULL){
                printFunc (atual -> data);
                atual = atual -> next;
            }

        }
    }
        
}



