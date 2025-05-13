//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Employee.h"
#include "general.h"
#include "Bank.h"
//done

const char* roleName[NumRoles] = { "Employee", "Manager", "Team Leader" , "Shift Manager" };

int initNewEmployee(Employee* e)
{
	int branchCode;
	printf("Enter employee branch code: ");
	while (!scanf("%d", &branchCode))
	{
		printf("Inlvalid input, Please enter a number value\n");
		flush();
	}
	HumanData eData;
	initHumanData(&eData, 'e');
	e->emploData = eData;
	e->role = getRoleFromUser();
	printf("Enter employee salary: ");
	while (!scanf("%lf", &e->salary))
	{
		printf("Inlvalid input, Please enter a number value\n");
		flush();
	}
	flush();
	addEmployeeToBranch(e, findBranchByCode(branchCode));
	return branchCode;
}


int readEmployeeFromFile(FILE* f, Employee* e, int fileType)
{
	char roleString[SIZE];
	switch (fileType)
	{
	case 1:
		if (!readHumanDataFromFile(f, &e->emploData, fileType))
			return 0;
		if (fscanf(f, "%lf", &e->salary) != 1)
			return 0;
		fileFlush(f);
		if (!fgets(roleString, sizeof(roleString), f))
			return 0;
		break;
	case 2:
		if (fread(&e->salary, sizeof(double), 1, f) != 1)
			return 0;
		if (fread(roleString, sizeof(roleString), 1, f) != 1)
			return 0;
		break;
	}
	roleString[strcspn(roleString, "\n")] = 0;
	for (int i = 0; i < NumRoles; ++i)
	{
		if (strcmp(roleString, roleName[i]) == 0)
			e->role = (employee_role)i;
	}
	return 1;
}

employee_role getRoleFromUser()
{
	int i, t;
	printf("Enter employee role\n");
	do {
		for (i = 0; i < NumRoles; i++)
			printf("Enter %d for %s\n", i, roleName[i]);
		(void)scanf("%d", &t);
		while (getchar() != '\n') {};
	} while (t < 0 || t >= NumRoles);
	return (employee_role)t;
}

void printEmployee(const void* employee)
{
	const Employee* e = (const Employee*)employee;
	printHumanData(&e->emploData);
	printf("Role: %s, Salary: %0.1f.\n\n", roleName[e->role], e->salary);
}

void printEmployeeDataToFile(FILE* f, const Employee* employee, int branchCode, int state)
{
	printHumanDataToFile(f, &employee->emploData, state);
	switch (state)
	{
	case 1:
		fprintf(f, "%f\n", employee->salary);
		fprintf(f, "%s\n", roleName[employee->role]);
		fprintf(f, "%ld", branchCode);
		break;
	case 2:
		fwrite(&employee->salary, sizeof(double), 1, f);
		fwrite(roleName[employee->role], SIZE, 1, f);
		fwrite(&branchCode, sizeof(int), 1, f);
		break;
	}
}

int isEmployeeName(const Employee* e, const char name[])
{
	if (compareTwoStringsNoCaseSensetive(e->emploData.name, name))
		return 1;
	return 0;
}

int isEmployeeID(const Employee* e, const int id)
{
	if (e->emploData.id == id)
		return 1;
	return 0;
}

int isSameEmployee(const Employee* e1, const Employee* e2)
{
	if (e1->emploData.id != e2->emploData.id)
		return 0;
	if (!compareTwoStringsNoCaseSensetive(e1->emploData.name, e2->emploData.name))
		return 0;
	return 1;
}

void updateEmployeeSalary(const double salary, Employee* e)
{
	e->salary = salary;
}

void freeEmployee(const void* e)
{
	Employee* eP = (Employee*)e;
	free(eP);
}