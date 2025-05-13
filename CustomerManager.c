//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "general.h"
#include "CustomerManager.h"

void initCustomerManager(int fileType)
{
	initList2(&bankCustomers.customerList);
	Customer c;
	FILE* f;
	switch (fileType)
	{
	case 1:
		if (f = fopen("customers.txt", "r"))
		{
			if (&c)
				continueCustomerInit(f, &c, fileType);
		}
		else
		{
			FILEOPENINGERROR("customers");
		}
		break;
	case 2:
		if (f = fopen("customers.bin", "rb"))
		{
			if (&c)
				continueCustomerInit(f, &c, fileType);
		}
		else
		{
			FILEOPENINGERROR("customers");
		}
		break;
	}
}

void continueCustomerInit(FILE* f, Customer* c, int fileType)
{
	switch (fileType)
	{
	case 1:
		while (!feof(f))
		{
			if (!readCustomerFromFile(f, c, fileType))
			{
				fclose(f);
				STRUCTREADINGERROR("customer");
				break;
			}
			else
				addCustomer(c, 0);
		}
		break;
	case 2:
		while (fread(&c->customerData, sizeof(HumanData), 1, f))
		{
			if (!readCustomerFromFile(f, c, fileType))
			{
				fclose(f);
				STRUCTREADINGERROR("customer");
				break;
			}
			else
				addCustomer(c, 0);
		}
		break;
	}
	fclose(f);
	printf("Customers initialized successfully from file!\n\n");
}

void printCustomerManager()
{
	if (bankCustomers.numOfCustomers == 0)
	{
		printf("No customers");
		return;
	}
	printf("The bank customers are:\n");
	NODE2* temp = &bankCustomers.customerList;
	while (temp->next != NULL)
	{
		printCustomer(&temp->next->data);
		printf("\n");
		temp = temp->next;
	}
}

void printBankAccounts()
{
	if (!&bankCustomers.customerList)
	{
		printf("No customers");
		return;
	}
	printf("The bank accounts are:\n");
	NODE2* temp = &bankCustomers.customerList;
	while (temp->next != NULL)
	{
		printBankAccount(temp->next->data.account);
		printf("\n");
		temp = temp->next;
	}
}

int addCustomer(const Customer* customer, int fileType)
{
	if (!&bankCustomers.customerList)
	{
		return 0;
	}
	NODE2* temp = &bankCustomers.customerList;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	insertToEndList2(temp, *customer);
	bankCustomers.numOfCustomers++;
	FILE* f;
	if (fileType != 0) {
		if (f = fopen("customers.txt", "a"))
			printCustomerDataToFile(f, customer, 1);
		else
			ADDINGTOFILEERROR("customer");
		if (f = fopen("customers.bin", "ab"))
			printCustomerDataToFile(f, customer, 2);
		else
			ADDINGTOFILEERROR("customer");
	}
	return 1;
}


int removeCustomer(const Customer* customer)
{
	
	NODE2* temp = &bankCustomers.customerList;
	int deleted = 0;
	FILE* f1 = fopen("customers.txt", "w");
	FILE* f2 = fopen("customers.bin", "wb");
	if (f1)
	{
		if (f2)
		{
			temp = &bankCustomers.customerList;
			while (temp->next != NULL)
			{
				if (!isSameCustomer(&temp->next->data, customer))
				{
					printCustomerDataToFile(f1, &temp->next->data, 1);
					printCustomerDataToFile(f2, &temp->next->data, 2);
				}
				else
				{
					freeBankAccountFromCustomer(&temp->next->data);
					deleted = deleteFromList2(temp);
				}
				temp = temp->next;
			}
			fclose(f1);
			fclose(f2);
		}
		else
			DELETINGFROMFILEERROR("customer");
	}
	else
		DELETINGFROMFILEERROR("customer");
	if (deleted == 0) {
		return 0;
	}
	return 1;
}


Customer* findCustomerByID(const int id)
{
	Customer* pC = NULL;
	if (!&bankCustomers.customerList)
	{
		return 0;
	}
	NODE2* temp = &bankCustomers.customerList;
	while (temp->next != NULL)
	{
		pC = &temp->next->data;
		if (pC->customerData.id == id)
			return pC;
		temp = temp->next;
	}
	return NULL;
}

void freeCustomerList()
{
	NODE2* temp = &bankCustomers.customerList;
	while (temp->next != NULL)
	{
		freeBankAccountFromCustomer(&temp->next->data);
		deleteFromList2(temp);
	}
}