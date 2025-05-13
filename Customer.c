//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "general.h"
#include "Customer.h"

void initCustomer(Customer* c)
{
	initHumanData(&c->customerData , 'c');
	printf("Join date: ");
	initDate(&c->dateOfJoin);
	c->account = (BankAccount*)malloc(sizeof(BankAccount));
	if (c->account)
		initBankAccount(c->account);

}

int readCustomerFromFile(FILE* f, Customer* c, int fileType)
{
	switch (fileType)
	{
	case 1:
		if (!readHumanDataFromFile(f, &c->customerData, fileType))
			return 0;
		if (!readDateFromFile(f, &c->dateOfJoin))
			return 0;
		break;
	case 2:
		if (fread(&c->dateOfJoin, sizeof(Date), 1, f) != 1)
			return 0;
		break;
	}
	c->account = (BankAccount*)malloc(sizeof(BankAccount));
	if (c->account)
		if (!readBankAccountFromFile(f, c->account, fileType))
			return 0;

	return 1;
}

void printCustomerDataToFile(FILE* f, const Customer* customer, int fileType)
{
	printHumanDataToFile(f, &customer->customerData, fileType);
	printDateDataToFile(f, &customer->dateOfJoin, fileType);
	switch (fileType) {
	case 1:
		fprintf(f, "%ld\n%ld", customer->account->number, customer->account->branch->code);
		break;
	case 2:
		fwrite(&customer->account->number, sizeof(int), 1, f);
		fwrite(&customer->account->branch->code, sizeof(int), 1, f);
		break;
	}
}

void printCustomer(const void* customer)
{
	const Customer* c = (const Customer*)customer;
	printHumanData(&c->customerData);
	printf(", Date of join: ");
	printDate(&c->dateOfJoin);
	printf("\nBank account: ");
	printBankAccount(c->account);
}


int isSameCustomer(const Customer* c1, const Customer* c2)
{
	if (c1->customerData.id != c2->customerData.id)
		return 0;
	return 1;
}



void freeBankAccountFromCustomer(void* c)
{
	Customer* cP = (Customer*)c;
	free(cP->account);
}