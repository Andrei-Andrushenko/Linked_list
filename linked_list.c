#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// В узле списка хранится само значение value и указатель на следующий узел.
// Эту структуру пользователи списка не должны видеть, так как она относится к внутренней реализации.
typedef struct Node_ {
  int value; // само значение, которое хранит узел
  struct Node_ *next; // указатель на следующий узел
} Node;

// Пользовательская структура, которая скрывает механизм хранения данных.
struct List {
  Node *head; // указатель на голову списка
  Node *tail; // указатель на хвост списка
  // если нужно, то добавьте дополнительные поля
};

List *NewList() {
    List* list=malloc(sizeof(List));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

void DestroyList(List* this) {
    Node* tmp=this->head;
    while (tmp!=NULL) {
        tmp=tmp->next;
        free(this->head);
        this->head=tmp;
    }
    this->tail=NULL;
    free(this);
}

void Append(List *this, int value) {
    if (this->head==NULL) {
        Node* tmp=malloc(sizeof(Node));
        tmp->value=value;
        tmp->next=NULL;
        this->head=tmp;
        this->tail=tmp;
        return;
    }
    Node* tmp=malloc(sizeof(Node));
    tmp->value=value;
    tmp->next=NULL;
    (this->tail)->next=tmp;
    this->tail=tmp;
}
void Prepend(List *this, int value) {
    if (this->head==NULL) {
        Node* tmp=malloc(sizeof(Node));
        tmp->value=value;
        tmp->next=NULL;
        this->head=tmp;
        this->tail=tmp;
        return;
    }
    Node* tmp=malloc(sizeof(Node));
    tmp->value=value;
    tmp->next=this->head;
    this->head=tmp;
}
void AppendAll(List *this, const List *that) {
    for (int i=0; i<Length(that); i++) {
        Append(this, GetAt(that, i));
    }
}

void InsertAt(List *this, int index, int value) {
    if (index+1>Length(this)) {
        printf("ERROR: segmentation fault");
        exit(-1);
    }
    int c=0;
    Node* ptr=this->head;
    while (c!=index) {
        ptr=ptr->next;
        c++;
    }
    Node* tmp=malloc(sizeof(Node));
    tmp->value=value;
    tmp->next=ptr->next;
    ptr->next=tmp;
}

void RemoveAt(List *this, int index) {
    if (index==0) {
        Dequeue(this);
        return;
    }
    Node* tmp=this->head;
    Node* ptr=NULL;
    int c=0;
    while (c!=index) {
        if (c==index-1) {
            ptr=tmp;
        }
        tmp=tmp->next;
        c++;
    }
    ptr->next=tmp->next;
    tmp->next=NULL;
    free(tmp);
}
void RemoveAll(List *this) {
    Node* tmp=this->head;
    while (tmp!=NULL) {
        tmp=tmp->next;
        free(this->head);
        this->head=tmp;
    }
    this->tail=NULL;
}

int Pop(List *this) {
    Node* ptr=this->head;
    for (int i=0; i<Length(this)-1; i++) {
        this->tail=ptr;
        ptr=ptr->next;
    }
    this->tail->next=NULL;
    int a=ptr->value;
    free(ptr);
    return a;
}
int Dequeue(List *this) {
    Node* tmp=this->head;
    this->head=this->head->next;
    tmp->next=NULL;
    int a=tmp->value;
    free(tmp);
    return a;
}

int Length(const List *this) {
    int c=0;
    Node* tmp=this->head;
    while (tmp!=NULL) {
        tmp=tmp->next;
        c++;
    }
    return c;
}
int GetAt(const List *this, int index) {
    if (index+1>Length(this)) {
        printf("ERROR: segmentation fault");
        exit(-1);
    }
    int c=0;
    Node* tmp=this->head;
    while (c!=index) {
        tmp=tmp->next;
        c++;
    }
    return tmp->value;
}