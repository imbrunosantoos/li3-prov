#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "deque.h"


Deque *create(void) {
    Deque *deque = malloc(sizeof(Deque));
    if (deque == NULL) return NULL;

    deque -> head = NULL;
    deque -> tail = NULL;
    deque -> size = 0;

    return deque;
}

void destroy(Deque *deque){
    No *atual = deque->head;
    
    while(atual != NULL){
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(deque);
    
}

void push(Deque *deque, void *data){
    No *novo = malloc(sizeof(No));
    if(novo == NULL) return;
    
    novo->prev = deque->tail;
    novo->data = data;
    novo->prox = NULL;

    if(deque->head == NULL){
        deque->head = novo;
    } else {
        deque->tail->prox = novo;
    }
    deque->size++;
    deque->tail = novo;
}


void pushFront(Deque *deque, void *data){
    No *novo = malloc(sizeof(No));
    if(novo == NULL)return;

    novo->prev = NULL;
    novo->data = data;
    novo->prox = deque->head;

    if(deque->head == NULL){
        deque->tail = novo;
    } else {
        deque->head->prev = novo;
    }
    deque->size++;
    deque->head = novo;
}

void *pop(Deque *deque){
    if(deque->tail == NULL){
        return NULL;
    }

    No *novo = deque->tail->prev;
    void *valor = deque->tail->data;

    if(deque->head == deque->tail){

        free(deque->tail);
        deque->size--;
        deque->head = NULL;
        deque->tail = NULL;
        return valor;
    }
    else {
        free(deque->tail);
        deque->tail = novo;
        novo->prox = NULL;
        deque->size--;
        return valor;
    }
}

void *popFront(Deque *deque){
    if(deque->head == NULL){
        return NULL;
    }

    No *novo = deque->head->prox;
    void *valor = deque->head->data;

    if(deque->head == deque->tail){
        free(deque->head);
        deque->size--;
        deque->head = NULL;
        deque->tail = NULL;
        return valor;
    } else{
        free(deque->head);
        novo->prev = NULL;
        deque->head = novo;
        deque->size--;
        return valor;
    }
}

int size(Deque *deque){
    return deque->size;
}

bool isEmpty(Deque *deque){
    if (deque->head == NULL){
        return true;
    }
    else{
        return false;
    }
}

void printDeque(Deque *deque, void (*printFunc)(void *)){
    No *temp = deque->head;

    while(temp != NULL){
        printFunc(temp->data);
        temp = temp->prox;
    }
}


void reverse(Deque *deque){
    No *temp = deque->head;

    while(temp != NULL){
            No *proximo = temp->prox;
            temp->prox=temp->prev;
            temp->prev = proximo;
            temp = proximo;
        }
        No *novoh = deque->head;

        deque->head = deque->tail;
        deque->tail= novoh;
    }
