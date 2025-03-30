#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* L = (List*) malloc(sizeof(List));
    L->current = 0;
    L->head = 0;
    L->tail = 0;
    return L;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL; 
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL; 
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) {
        return NULL; 
    }
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) {
        return NULL; 
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = createNode(data);
    newNode->next = list->head;
    newNode->prev = NULL;

    if (list->head != NULL) list->head->prev = newNode; 
    else list->tail = newNode;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = createNode(data);
    newNode->next = NULL; 
    newNode->prev = list->tail;

    if (list->tail != NULL) list->tail->next = newNode;
    else list->head = newNode;
    list->tail = newNode;
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return;

    Node * newNode = createNode(data);
    newNode->next = list->current->next;
    newNode->prev = list->current;
    if (list->current->next != NULL) list->current->next->prev = newNode;
    else list->tail = newNode;
    list->current->next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    void* dato = list->current->data;
    Node *aux1 = list->current->prev;
    Node *aux2 = list->current->next;

    if (list->current == list->head)
    {
        aux1->next = aux2;
        aux1->prev = NULL;
    }
    else aux1->prev = aux1;
    
    if (list->current == list->head)
    {
        aux1->next = NULL;
        aux1->prev = aux1;
    }
    else aux1->next = aux1;

    free(list->current);

    list->current = NULL;
    
    return dato;
}


void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}