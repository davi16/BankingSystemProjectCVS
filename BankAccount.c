//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "BankAccount.h"
#include "Bank.h"
#include "general.h"


void initBankAccount(BankAccount* account)
{
	printf("Enter bank account number: ");
	account->number = initInteger(4, 8);
	addBranchToAccount(account);
}

int readBankAccountFromFile(FILE* f, BankAccount* account, int fileType)
{
	int branchCode = 0;
	switch (fileType)
	{
	case 1:
		if (fscanf(f, "%d", &account->number) != 1)
			return 0;
		if (fscanf(f, "%d", &branchCode) != 1)
			return 0;
		break;
	case 2:
		if (fread(&account->number, sizeof(int), 1, f) != 1)
			return 0;
		if (fread(&branchCode, sizeof(int), 1, f) != 1)
			return 0;
		break;
	}
	if (branchCode)
		account->branch = findBranchByCode(branchCode);
	return 1;
}

void addBranchToAccount(BankAccount* account)
{
	printf("Pick a branch:\n");
	printBankBranches();
	printf("Enter branch code: ");
	int code = initInteger(1, 3);
	account->branch = findBranchByCode(code);
	while (account->branch == NULL)
	{
		printf("Branch not found, Enter branch code again: ");
		code = initInteger(1, 3);
		account->branch = findBranchByCode(code);
	}
}

void printBankAccountDataToFile(FILE* f, const BankAccount* account, int fileType)
{
	switch (fileType)
	{
	case 1:
		fprintf(f, "%ld\n", account->number);
		break;
	case 2:
		fwrite(&account->number, sizeof(int), 1, f);
		break;
	}
	printBranchDataToFile(f, account->branch, fileType);
}

void printBankAccount(const void* account)
{
	BankAccount* b = (BankAccount*)account;
	printf("Number: %d, ", b->number);
	printBranch(b->branch);
}
