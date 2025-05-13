//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __CUSTOMERMANGER__
#define __CUSTOMERMANGER__
#include "Lists.h"

typedef struct
{
	NODE2 customerList;//Doubly Linked list
	int numOfCustomers;
}CustomerManager;

static CustomerManager bankCustomers;

void initCustomerManager(int fileType);
void continueCustomerInit(FILE* f, Customer* c, int fileType);
void printCustomerManager();
void printBankAccounts();
int addCustomer(const Customer* customer, int fileType);
int removeCustomer(const Customer* customer);
Customer* findCustomerByID(const int id);
void freeCustomerList();


#endif
