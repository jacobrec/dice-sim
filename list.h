#ifndef LIST_H_
#define LIST_H_


typedef struct node{
    struct node* next;
    struct node* previous;
    void* data;
} Node_t;

typedef struct {
    int length;
    int dataSize;
    Node_t* head;
    Node_t* tail;
} List_t;

List_t* createList(int dataSize);

void push(List_t* list,const void* data);
void* pop(List_t* list);
void* peek(List_t* list);

void insert(List_t* list, int index, const void* data);
void* pull(List_t* list, int index);
void* get(List_t* list, int index);

void* dequeue(List_t* list);
void* preview(List_t* list);

void destroyList(List_t* list);

void testList();

#endif
