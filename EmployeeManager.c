//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "EmployeeManager.h"
#include "general.h"
#include "Bank.h"

const char* sortTitle[NumOfSort] = { "Not Sorted", "By Name", "By Role", "By Salary" };

void initEmployeeManager(int fileType)
{
	bankEmployees.numOfEmployees = 0;
	bankEmployees.sortBy = notSorted;
	Employee e;
	FILE* f;
	switch (fileType)
	{
	case 1:
		if (f = fopen("employees.txt", "r"))
			if (&e)
				continueEmployeeInit(f, &e, fileType);
		else
			FILEOPENINGERROR("employees");
		break;
	case 2:
		if (f = fopen("employees.bin", "rb"))
			if (&e)
				continueEmployeeInit(f, &e, fileType);
		else
			FILEOPENINGERROR("employees");
		break;
	}
}

void continueEmployeeInit(FILE* f, Employee* e, int fileType)
{
	bankEmployees.employees = (Employee*)calloc(bankEmployees.numOfEmployees, sizeof(Employee));
	if (!bankEmployees.employees)
	{
		fclose(f);
		printf("Error initializing employee array!\n");
		return;
	}
	else
	{
		int branchCode = 0;
		switch (fileType)
		{
		case 1:
			while (!feof(f))
			{
				if (!readEmployeeFromFile(f, e, fileType))
				{
					fclose(f);
					STRUCTREADINGERROR("employee");
					break;
				}
				if (fscanf(f, "%d", &branchCode) != 1)
					return;
				if (branchCode)
				{
					addEmployee(e, 0, branchCode);
					Employee* pE = findEmployeeByNameOrID("", e->emploData.id);
					Branch* pB = findBranchByCode(branchCode);
					addEmployeeToBranch(pE, pB);
				}
			}
			break;
		case 2:
			while (fread(&e->emploData, sizeof(HumanData), 1, f))
			{
				if (!readEmployeeFromFile(f, e, fileType))
				{
					fclose(f);
					STRUCTREADINGERROR("employee");
					break;
				}
				if (fread(&branchCode, sizeof(int), 1, f) != 1)
					return;
				if (branchCode)
				{
					addEmployee(e, 0, branchCode);
					Employee* pE = findEmployeeByNameOrID("", e->emploData.id);
					Branch* pB = findBranchByCode(branchCode);
					addEmployeeToBranch(pE, pB);
				}
			}
			break;
		}
		fclose(f);
		printf("Employees initialized successfully from file!\n\n");
	}
}

void printEmployeeManager()
{
	if (bankEmployees.numOfEmployees == 0)
	{
		printf("No employees");
		return;
	}
	printf("The employees of the bank are:\n");
	generalFunction(bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), printEmployee);
}


int addEmployee(const Employee* e, int fileType, int branchCode)
{
	Employee* arr =
		(Employee*)realloc(bankEmployees.employees, (bankEmployees.numOfEmployees + 1) * sizeof(Employee));
	if (arr)
	{
		bankEmployees.employees = arr;
		bankEmployees.employees[bankEmployees.numOfEmployees] = *e;
		bankEmployees.numOfEmployees++;
		FILE* f;
		if (fileType != 0)
		{
			if (f = fopen("employees.txt", "a"))
				printEmployeeDataToFile(f, e, branchCode, 1);
			else
				ADDINGTOFILEERROR("employee");
			if (f = fopen("employees.bin", "ab"))
				printEmployeeDataToFile(f, e, branchCode, 2);
			else
				ADDINGTOFILEERROR("employee");
		}
		return 1;
	}
	return 0;
}

int removeEmployee(const Employee* employee)
{
	FILE* f1 = fopen("employees.txt", "w");
	FILE* f2 = fopen("employees.bin", "wb");
	Employee* temp = NULL;
	Branch* b = NULL;
	int index = 0;
	if (f1)
	{
		if (f2)
		{
			for (int i = 0; i < bankEmployees.numOfEmployees; ++i)
			{
				temp = &bankEmployees.employees[i];
				if (!isSameEmployee(employee, temp))
				{
					b = findEmployeeBranch(temp);
					printEmployeeDataToFile(f1, temp, b->code, 1);
					printEmployeeDataToFile(f2, temp, b->code, 2);
				}
				else
					index = i;
			}
			fclose(f1);
			fclose(f2);
		}
		else
			DELETINGFROMFILEERROR("employee");
	}
	else
		DELETINGFROMFILEERROR("employee");
	b = findEmployeeBranch(employee);
	deleteEmployeeFromBranch(employee, b);
	for (int i = index; i < bankEmployees.numOfEmployees - 1; i++)
	{
		bankEmployees.employees[i] = bankEmployees.employees[i + 1];
	}
	bankEmployees.numOfEmployees--;
	Employee* arr = (Employee*)realloc(bankEmployees.employees, (bankEmployees.numOfEmployees) * sizeof(Employee));
	if (arr)
	{
		bankEmployees.employees = arr;
		return 1;
	}
	return 0;
}



Employee* findEmployeeByNameOrID(const char name[], const int id)
{
	for (int i = 0; i < bankEmployees.numOfEmployees; ++i)
	{
		if (isEmployeeName(&bankEmployees.employees[i], name) || isEmployeeID(&bankEmployees.employees[i], id))
			return &bankEmployees.employees[i];
	}
	return NULL;
}


void sortEmployeeArray(sort_type sortType)
{
	switch (sortType)
	{
	case byName:
		qsort(bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeByName);
		bankEmployees.sortBy = byName;
		break;
	case byRole:
		qsort(bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeByRole);
		bankEmployees.sortBy = byRole;
		break;
	case bySalary:
		qsort(bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeBySalary);
		bankEmployees.sortBy = bySalary;
		break;
	}
}
sort_type getSortTypeFromUser()
{
	int i, t;
	printf("Enter sorting type\n");
	do {
		for (i = 0; i < NumOfSort; i++)
			printf("Enter %d for %s\n", i, sortTitle[i]);
		(void)scanf("%d", &t);
		flush();
	} while (t < 0 || t >= NumOfSort);
	return (sort_type)t;
}
int compareEmployeeByName(const void* employee1, const void* employee2)
{
	const Employee* e1 = (const Employee*)employee1;
	const Employee* e2 = (const Employee*)employee2;
	return strcmp(e1->emploData.name, e2->emploData.name);
}
int compareEmployeeByRole(const void* employee1, const void* employee2)
{
	const Employee* e1 = (const Employee*)employee1;
	const Employee* e2 = (const Employee*)employee2;
	return strcmp(sortTitle[e1->role], sortTitle[e2->role]);
}
int compareEmployeeBySalary(const void* employee1, const void* employee2)
{
	const Employee* e1 = (const Employee*)employee1;
	const Employee* e2 = (const Employee*)employee2;
	if (e1->salary < e2->salary) return -1;
	else if (e1->salary > e2->salary) return 1;
	else return 0;
}

Employee* searchEmployee()
{
	Employee temp;
	switch (bankEmployees.sortBy)
	{
	case byName:
		initString(temp.emploData.name, sizeof(temp.emploData.name));
		return bsearch(&temp, bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeByName);
	case byRole:
		temp.role = getRoleFromUser();
		Employee* first = bsearch(&temp, bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeByRole);
		for (int i = 0; i < bankEmployees.numOfEmployees; i++)
		{
			if (bankEmployees.employees[i].role == first->role)
			{
				printEmployee(&bankEmployees.employees[i]);
			}
		}
		return NULL;
	case bySalary:
		while (!scanf("%lf", &temp.salary))
		{
			printf("Inlvalid input, Please enter a number value\n");
			flush();
		}
		flush();
		return bsearch(&temp, bankEmployees.employees, bankEmployees.numOfEmployees, sizeof(Employee), compareEmployeeBySalary);
	}
	return NULL;
}

sort_type getSortType()
{
	return bankEmployees.sortBy;
}

void freeBankEmployeesArray()
{
	free(bankEmployees.employees);
}