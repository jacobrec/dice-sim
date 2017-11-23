#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "list.h"


List_t *createList(int dataSize) {
    List_t *l = malloc(sizeof(List_t));

    l->length   = 0;
    l->dataSize = dataSize;
    l->tail     = NULL;
    l->head     = NULL;
    return(l);
}

void push(List_t *list, const void *data) {
    Node_t *newNode = malloc(sizeof(Node_t));

    newNode->data = malloc(list->dataSize);
    memcpy(newNode->data, data, list->dataSize);

    if (list->length == 0) {
        list->tail = newNode;
        list->head = newNode;
    }
    else{
        newNode->previous = list->tail;
        list->tail->next  = newNode;
        list->tail        = newNode;
    }
    list->length++;
}

void *pop(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to pop\n");
    }
    else{
        Node_t *end;
        if (list->length == 1) {
            end        = list->tail;
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            end        = list->tail;
            list->tail = list->tail->previous;
        }
        list->length--;

        void *data = end->data;
        free(end);

        return(data);
    }
}

void *peek(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to peek\n");
    }
    else{
        return(list->tail->data);
    }
}

void insert(List_t *list, int index, const void *data) {
    Node_t *newNode = malloc(sizeof(Node_t));

    newNode->data = malloc(list->dataSize);
    memcpy(newNode->data, data, list->dataSize);

    if (list->length >= index && index >= 0) {
        if (index == 0 && list->length == 0) {
            list->tail = newNode;
            list->head = newNode;
        }
        else{
            if (index == 0) {
                newNode->next        = list->head;
                list->head->previous = newNode;
                list->head           = newNode;
            }
            else if (index == list->length) {
                newNode->previous = list->tail;
                list->tail->next  = newNode;
                list->tail        = newNode;
            }
            else {
                Node_t *prev = list->head;
                for (int i = 0; i < index - 1; i++) {
                    prev = prev->next;
                }

                newNode->previous = prev;
                newNode->next     = prev->next;

                prev->next->previous = newNode;
                prev->next           = newNode;
            }
        }
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
        free(newNode->data);
        free(newNode);
        return;
    }
    list->length++;
}

void *pull(List_t *list, int index) {
    if (list->length > index && index >= 0) {
        if (index == 0) {
            return(dequeue(list));
        }
        else if (index == list->length - 1) {
            return(pop(list));
        }
        else{
            Node_t *node = list->head;
            for (int i = 0; i < index; i++) {
                node = node->next;
            }

            node->next->previous = node->previous;
            node->previous->next = node->next;
            list->length--;
            void *data = node->data;
            free(node);

            return(data);
        }
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
    }
}

void *get(List_t *list, int index) {
    if (list->length > index && index >= 0) {
        Node_t *node = list->head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
        return(node->data);
    }
    else{
        fprintf(stderr, "Error: index out of bounds\n");
    }
}

void *dequeue(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to pop\n");
    }
    else{
        Node_t *end;
        if (list->length == 1) {
            end        = list->head;
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            end        = list->head;
            list->head = list->head->next;
        }
        list->length--;

        void *data = end->data;
        free(end);

        return(data);
    }
}

void *preview(List_t *list) {
    if (list->length == 0) {
        fprintf(stderr, "Error: no data to peek\n");
    }
    else{
        return(list->head->data);
    }
}

void destroyList(List_t *list) {
    while (list->length) {
        free(pop(list));
    }
}

void testList() {
    printf("##### Starting List test #####\n");
    List_t *l = createList(sizeof(int));
    printf("Create works\n");
    int *d = malloc(sizeof(int));
    for (int i = 0; i < 100; i++) {
        *d = i;
        push(l, d);
    }
    for (int i = 0; i < 100; i++) {
        d = pop(l);
        assert(*d == (99 - i));
    }
    printf("Push works\nPop Works\n");
    for (int i = 0; i < 10; i++) {
        *d = i;
        push(l, d);
        assert(*((int *)peek(l)) == i);
    }
    printf("Peek works\n");

    for (int i = 0; i < 5; i++) {
        d = pop(l);
        assert(*d == (9 - i));
    }
    for (int i = 0; i < 5; i++) {
        d = dequeue(l);
        assert(*d == i);
    }
    printf("Dequeue works\n");


    *d = 0; insert(l, 0, d);
    *d = 5; insert(l, 1, d);
    *d = 2; insert(l, 1, d);
    *d = 1; insert(l, 1, d);
    *d = 4; insert(l, 3, d);
    *d = 3; insert(l, 3, d);

    dequeue(l);
    *d = 0; insert(l, 0, d);


    for (int i = 0; i <= 5; i++) {
        d = dequeue(l);
        assert(*d == i);
    }

    printf("Insert works\n");

    for (int i = 0; i < 100; i++) {
        *d = i;
        push(l, d);
    }
    for (int i = 99; i > 0; i -= 2) {
        assert(*((int *)pull(l, i)) == i);
    }
    printf("Pull works\n");

    for (int i = 0; i < 50; i++) {
        assert(*((int *)get(l, i)) == (i * 2));
    }
    printf("Get works\n");

    for (int i = 0; i < 50; i++) {
        assert(*((int *)preview(l)) == (i * 2));
        dequeue(l);
    }
    printf("Preview works\n");



    for (int i = 0; i < 100000; i++) {
        *d = i;
        push(l, d);
    }
    destroyList(l);
    printf("Destroy works\n");
}
