//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "HumanDetails.h"
#include "BankAccount.h"


typedef struct
{
	HumanData customerData;
	Date dateOfJoin;
	BankAccount* account;
}Customer;

void initCustomer(Customer* c);
int readCustomerFromFile(FILE* f, Customer* c, int fileType);
void printCustomer(const void* customer);
void printCustomerDataToFile(FILE* f, const Customer* customer, int fileType);
int isSameCustomer(const Customer* c1, const Customer* c2);
void freeBankAccountFromCustomer(void* c);

#endif
