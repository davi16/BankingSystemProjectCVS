//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __LISTS__
#define __LISTS__
#include "Customer.h"

//Linked list type 1 - singly linkedlist with void pointer
//Used in branch manager
typedef struct node1 {
	void* data;
	struct node1* next;
}NODE1;

typedef struct {
	NODE1 head;
	int data_size;
}LIST1;

//Linked list type 2 - doubly linked list without header
//Used for customer manager
typedef struct node2 {
	Customer data;
	struct node2* next;
	struct node2* prev;
}NODE2;


int initList1(LIST1* list);
NODE1* insertToList1(NODE1* node, const void* value, size_t data_size);
int deleteFromList1(NODE1* pNode);
int freeList1(LIST1* pList);
NODE1* findInList1(NODE1* pNode, void* Value);



int initList2(NODE2* list);
NODE2* createNode2(Customer data);
void insertToEndList2(NODE2* node, Customer data);
int deleteFromList2(NODE2* pNode);


#endif
