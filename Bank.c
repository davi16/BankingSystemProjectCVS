//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Bank.h"
#include "Lists.h"
#include "general.h"

void initBank(int fileType)
{
	ourBank.bank_code = 1;
	ourBank.name = "United David Kristina Bank";
	initList1(&ourBank.branchList);
	Branch b;
	FILE* f = NULL;
	switch (fileType)
	{
	case 1:
		if (f = fopen("branches.txt", "r"))
			if (&b)
				continueBankInit(f, &b, fileType);
		else
			FILEOPENINGERROR("branches");
		break;
	case 2:
		if (f = fopen("branches.bin", "rb"))
			if (&b)
				continueBankInit(f, &b, fileType);
		else
			FILEOPENINGERROR("branches");
		break;
	}
}

void continueBankInit(FILE* f, Branch* b, int fileType)
{
	switch (fileType)
	{
	case 1:
		while (!feof(f))
		{
			if (!readBranchFromFile(f, b, fileType))
			{
				fclose(f);
				STRUCTREADINGERROR("branch");
				break;
			}
			else
				addBranch(b, 0);
		}
		break;
	case 2:
		while (fread(&b->code, sizeof(int), 1, f))
		{
			if (!readBranchFromFile(f, b, fileType))
			{
				fclose(f);
				STRUCTREADINGERROR("branch");
				break;
			}
			else
				addBranch(b, 0);
		}
		break;
	}
	fclose(f);
	printf("Branches initialized successfully from file!\n\n");
}

void printBankBranches()
{
	if (!&ourBank.branchList)
	{
		printf("No branches");
		return;
	}
	printf("The bank branches are:\n");
	NODE1* temp = &ourBank.branchList.head;
	while (temp->next != NULL)
	{
		printBranch(temp->next->data);
		printf("\n");
		temp = temp->next;
	}
}
int addBranch(const Branch* branch, int fileType)
{
	if (!&ourBank.branchList)
	{
		return 0;
	}
	NODE1* temp = &ourBank.branchList.head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = insertToList1(temp, branch, sizeof(Branch));
	ourBank.numOfBranches++;
	FILE* f;
	if (fileType != 0) {
		if (f = fopen("branches.txt", "a"))
			printBranchDataToFile(f, branch, 1);
		else
			ADDINGTOFILEERROR("branch");
		if (f = fopen("branches.bin", "ab"))
			printBranchDataToFile(f, branch, 2);
		else
			ADDINGTOFILEERROR("branch");
	}
	return 1;
}


Branch* findEmployeeBranch(const Employee* employee)
{
	NODE1* found = NULL;
	NODE1* temp = &ourBank.branchList.head;
	while (temp->next != NULL)
	{
		if (findEmployeeInBranch(temp->next->data, employee))
		{
			return temp->next->data;
		}
		temp = temp->next;
	}
	return NULL;
}

int removeBranch(const Branch* branch)
{
	Branch b = *branch;
	NODE1* temp = &ourBank.branchList.head;
	int deleted = 0;
	FILE* f1 = fopen("branches.txt", "w");
	FILE* f2 = fopen("branches.bin", "wb");
	if (f1)
	{
		if (f2)
		{
			temp = &ourBank.branchList.head;
			while (temp->next != NULL)
			{
				if (!isSameBranch((Branch*)temp->next->data, &b))
				{
					printBranchDataToFile(f1, (Branch*)temp->next->data, 1);
					printBranchDataToFile(f2, (Branch*)temp->next->data, 2);
					temp = temp->next;
				}
				else
					deleted = deleteFromList1(temp);
				
			}
			fclose(f1);
			fclose(f2);
		}
		else
			DELETINGFROMFILEERROR("branch");
	}
	else
		DELETINGFROMFILEERROR("branch");
	if (deleted == 0) 
		return 0;
	return 1;
}


Branch* findBranchByCode(const int code)
{
	Branch* branch = NULL;
	if (!&ourBank.branchList)
	{
		return 0;
	}
	NODE1* temp = &ourBank.branchList.head;
	while (temp->next != NULL)
	{
		branch = (Branch*)temp->next->data;
		if (branch->code == code)
			return branch;
		temp = temp->next;
	}
	return NULL;
}

void printBankDetails()
{
	printf("Bank code: %d\n", ourBank.bank_code);
	printf("Bank name: %s\n", ourBank.name);
}

void freeEmployeeArraysInBranches()
{
	Branch* pB = NULL;
	if (!&ourBank.branchList)
	{
		return;
	}
	NODE1* temp = &ourBank.branchList.head;
	while (temp->next != NULL)
	{
		pB = temp->next->data;
		freeEmployeesInArray(pB);
		free(pB->employees);
		temp = temp->next;
	}
}

void freeBank()
{
	freeEmployeeArraysInBranches();
	freeList1(&ourBank.branchList);
}