//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Lists.h"
#include "Branch.h"

int initList1(LIST1* list)
{
	if (list == NULL) return 0;
	list->head.next = NULL;
	return 1;
}

NODE1* insertToList1(NODE1* node, const void* value, size_t data_size)
{
	NODE1* temp = (NODE1*)malloc(sizeof(NODE1));
	if (!node) return NULL;
	if (temp) {
		temp->data = malloc(data_size);
		if (temp->data)
		{
			memcpy(temp->data, value, data_size);
			temp->next = node->next;
			node->next = temp;
		}
	}
	return temp;
}

int deleteFromList1(NODE1* pNode)
{
	NODE1* temp = NULL;
	if (!pNode || !(temp = pNode->next)) return 0;
	pNode->next = temp->next;
	free(temp->data);
	free(temp);
	return 1;
}

int freeList1(LIST1* pList)
{
	NODE1* temp;
	int cont = 1;
	if (!pList) return 0;
	temp = &(pList->head);
	while (cont)
		cont = deleteFromList1(temp);
	return 1;
}

NODE1* findInList1(NODE1* pNode, void* Value)
{
	NODE1* temp = pNode;
	while (temp != NULL)
	{
		if (temp->data == Value)
			return temp;
		temp = temp->next;
	}
	return NULL;
}


int initList2(NODE2* list)
{
	if (list == NULL) return 0;
	list->next = NULL;
	list->prev = NULL;
	return 1;
}

NODE2* createNode2(Customer data)
{
	NODE2* newNode = (NODE2*)malloc(sizeof(NODE2));
	if (newNode)
	{
		newNode->data = data;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	return newNode;
}

void insertToEndList2(NODE2* node, Customer data)
{
	NODE2* newNode = createNode2(data);
	if (node != NULL) {
		node->next = newNode;
		newNode->prev = node;
	}
}

int deleteFromList2(NODE2* pNode)
{
	NODE2* temp = NULL;
	if (!pNode || !(temp = pNode->next)) return 0;
	pNode->next = temp->next;
	if (temp->next)
		temp->next->prev = pNode;
	free(temp);
	return 1;
}
