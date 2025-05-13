//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Bank.h"
#include "general.h"
#include "EmployeeManager.h"


void initBranch(Branch* branch)
{
	printf("Enter branch code: ");
	branch->code = initInteger(1, 3);
	while (findBranchByCode(branch->code))
	{
		printf("Branch code already exist, Try again: ");
		branch->code = initInteger(1, 3);
	}
	printf("Enter branch name: ");
	branch->name = initDynamicString();
	printf("Enter branch address: ");
	initAddress(&branch->address);
	branch->employees = initEmployeesArray(branch);

}

Employee** initEmployeesArray(Branch* b)
{
	b->numOfEmployees = 0;

	//inits dynamic array of pointers to Employees
	b->employees = (Employee**)malloc(b->numOfEmployees * sizeof(Employee*));
	if (b->employees)
		return b->employees;
	else
	{
		printf("Allocation didn't succeed");
		return NULL;
	}

}
int readBranchFromFile(FILE* f, Branch* b, int fileType)
{
	char nameTemp[MAX_LENGTH];
	int nameLength;
	switch (fileType)
	{
	case 1:
		if (fscanf(f, "%d", &b->code) != 1)
			return 0;
		fileFlush(f);
		if (!fgets(nameTemp, sizeof(nameTemp), f))
			return 0;
		nameTemp[strcspn(nameTemp, "\n")] = 0;
		b->name = _strdup(nameTemp);
		if (!readAddressFromFile(f, &b->address))
			return 0;
		break;
	case 2:
		if (fread(&nameLength, sizeof(int), 1, f) != 1)
			return 0;
		b->name = (char*)malloc(nameLength * sizeof(char));
		if (b->name)
			if (fread(b->name, sizeof(char), nameLength, f) != nameLength)
				return 0;
		if (fread(&b->address, sizeof(Address), 1, f) != 1)
			return 0;
		break;
	}
	b->employees = initEmployeesArray(b);
	return 1;
}

void printBranchDataToFile(FILE* f, const Branch* branch, int fileType)
{
	switch (fileType) {
	case 1:
		fprintf(f, "\n%ld\n%s\n", branch->code, branch->name);
		printAddressDataToFile(f, &branch->address, fileType);
		break;
	case 2:
		fwrite(&branch->code, sizeof(int), 1, f);
		int len;
		len = (int)strlen(branch->name) + 1;
		fwrite(&len, sizeof(int), 1, f);
		fwrite(branch->name, sizeof(char), len, f);
		printAddressDataToFile(f, &branch->address, fileType);
		break;
	}
}

int findEmployeeInBranch(const Branch* branch, const Employee* employee)
{
	for (int i = 0; i < branch->numOfEmployees; i++)
	{
		if (isSameEmployee(branch->employees[i], employee))
		{
			return 1;
		}
	}
	return 0;
}

void printBranch(const void* branch)
{
	Branch* b = (Branch*)branch;
	printf("Code: %d, Name: %s, ", b->code, b->name);
	printAddress(&b->address);
}

void addEmployeeToBranch(const Employee* e, Branch* b)
{
	b->numOfEmployees++;
	Employee** temp = (Employee**)realloc(b->employees, b->numOfEmployees * sizeof(Employee*));
	if (temp && b->numOfEmployees > 0)
	{
		b->employees = temp;
		b->employees[b->numOfEmployees - 1] = (Employee*)malloc(1 * sizeof(Employee));
		if (b->employees[b->numOfEmployees - 1])
			memcpy(b->employees[b->numOfEmployees - 1], e, sizeof(Employee));
	}
}

void deleteEmployeeFromBranch(const Employee* e, Branch* b)
{
	int index = 0;
	for (int i = 0; i < b->numOfEmployees; ++i)
	{
		if (isSameEmployee(b->employees[i], e))
			index = i;
	}
	for (int j = index; j < b->numOfEmployees - 1; ++j)
		b->employees[j] = b->employees[j + 1];
	b->numOfEmployees--;
	Employee** temp = (Employee**)realloc(b->employees, b->numOfEmployees * sizeof(Employee*));
	if (temp)
		b->employees = temp;
}

void printBranchEmployees(const Branch* b)
{
	for (int i = 0; i < b->numOfEmployees; ++i)
	{
		generalFunction(b->employees[i], 1, sizeof(Employee), printEmployee);
	}
}

int isSameBranch(const Branch* b1, const Branch* b2)
{
	if (strcmp(b1->name, b2->name) != 0)
		return 0;
	if (b1->code != b2->code)
		return 0;
	return 1;
}

void freeEmployeesInArray(Branch* pB)
{
	for (int i = 0; i < pB->numOfEmployees; ++i)
	{
		generalFunction(pB->employees[i], 1, sizeof(Employee), freeEmployee);
	}
	free(pB->name);
}