//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "exe.h"
#include "CustomerManager.h"
#include "EmployeeManager.h"
#include "Bank.h"
#include "general.h"

void firstInit()
{//System data initialization
	int fileType;
	printf("Enter which file type you want to read the system from :\n");
	printf("1 - .txt file.\n");
	printf("2 - .bin file.\n");
	while (!scanf("%d", &fileType) || (fileType != 1 && fileType !=2))
	{
		printf("Please enter a correct value: ");
		flush();
	}
	flush();
	initBank(fileType);
	//printBankBranches();
	initCustomerManager(fileType);
	//printCustomerManager();
	initEmployeeManager(fileType);
	//printEmployeeManager();
}
void option1()
{//Adding new branch
	Branch b;
	initBranch(&b);
	addBranch(&b, -1);
	printBranch(&b);
}
void option2()
{//Show bank details and all branches
	printBankDetails();
	printBankBranches();
}
void option3()
{//Adding new customer
	Customer c;
	initCustomer(&c);
	addCustomer(&c, -1);
	printCustomer(&c);
	printf("\n");
}
void option4()
{//Showing employee list
	printCustomerManager();
}
void option5()
{//Adding new employee
	Employee e;
	int branchCode = initNewEmployee(&e);
	addEmployee(&e, -1, branchCode);
	printEmployee(&e);
}
void option6()
{//Showing employee list
	printEmployeeManager();
}
void option7()
{//Sort bank employees by selected sorting method
	printf("Right now the employees are sorted: %s\n", sortTitle[getSortType()]);
	printEmployeeManager();
	printf("Select sorting method:\n");
	sort_type sortType;
	sortType = getSortTypeFromUser();
	sortEmployeeArray(sortType);
	printf("Employee list after sorting %s: \n", sortTitle[sortType]);
	printEmployeeManager();
}
void option8()
{//Search bank employees by selected sorting method
	Employee* e = NULL;
	switch (getSortType())
	{
	case notSorted:
		printf("\n");
		printf("The search can't be completed, the array is yet to be sorted!\n");
		printf("Please select a sorting method in option 7 in the main menu!\n");
		printf("Returning to main menu...\n\n");
		break;
	case byName:
		printf("Please enter employee name (case sensative):\n");
		e = searchEmployee();
		if (e)
		{
			printf("The employee found:\n");
			printEmployee(e);
		}
		else
			printf("Employee not found\n");
		break;
	case byRole:
		printf("Please enter employee Role:\n");
		(void)searchEmployee();
		break;
	case bySalary:
		printf("Please enter employee salary:\n");
		e = searchEmployee();
		if (e)
		{
			printf("The employee found:\n");
			printEmployee(e);
		}
		else
			printf("Employee not found\n");
		break;
	}
}
void option9()
{//Update employee salary
	int id;
	double newSalary;
	Employee* e = NULL;
	printf("Enter employee ID : ");
	id = initInteger(1, 9);
	e = findEmployeeByNameOrID("", id);
	if (!e)
		printf("Employee not found");
	else
	{
		printf("Employee found:\n");
		printEmployee(e);
		printf("Enter new salary: ");
		while (!scanf("%lf", &newSalary))
		{
			printf("Inlvalid input, Please enter a number value\n");
			flush();
		}
		updateEmployeeSalary(newSalary, e);
		printf("\nSalary updated successfully!\n");
	}
}
void option10()
{//Show all bank accounts in system
	printBankAccounts();
}
void option11()
{//Show all employees in branch
	int code;
	printf("Enter branch code: ");
	code = initInteger(1, 3);
	Branch* branch = findBranchByCode(code);
	if (!branch)
	{
		printf("Branch not found\n");
	}
	else
	{
		printf("The branch found: ");
		printBranch(branch);
		if (branch->numOfEmployees == 0)
			printf("\nNo employees in branch\n");
		else
		{
			printf("The employees of the branch are:\n");
			printBranchEmployees(branch);
		}
	}
}
void option12()
{//remove stuff
	int select;
	printf("Choose what you want to delete:\n");
	printf("1 - Branch.\n");
	printf("2 - Customer.\n");
	printf("3 - Employee.\n");
	while (!scanf("%d", &select))
	{
		printf("Please enter an integer value (1-3)");
		flush();
	}
	int id;
	switch (select)
	{
	case 1:
		printf("Enter branch code: ");
		id = initInteger(1, 3);
		Branch* branch = findBranchByCode(id);
		if (!branch)
			printf("Branch not found\n");
		else
		{
			printf("The branch: ");
			printBranch(branch);
			if(removeBranch(branch))
				printf("\ndeleted succssesfully!\n");
			else
				printf("\nnot deleted!\n");
		}
		break;
	case 2:
		printf("Enter customer id: ");
		id = initInteger(1, 9);
		Customer* customer = findCustomerByID(id);
		if (!customer)
			printf("Customer not found\n");
		else
		{
			printf("The customer: ");
			printCustomer(customer);
			if(removeCustomer(customer))
				printf("\ndeleted succssesfully!\n");
			else
				printf("\nnot deleted!\n");
		}
		break;
	case 3:
		printf("Enter employee id: ");
		id = initInteger(1, 9);
		Employee* employee = findEmployeeByNameOrID("-", id);
		if (!employee)
			printf("Employee not found\n");
		else
		{
			printf("The employee: ");
			printEmployee(employee);
			if(removeEmployee(employee))
				printf("\ndeleted succssesfully!\n");
			else
				printf("\nnot deleted!\n");
		}
		break;
	default:
		printf("Wrong input, returning to main menu...\n");
		flush();
		break;
	}

}
void Exit()
{
	//free all memory allocations 
	freeCustomerList();
	freeBank();
	freeBankEmployeesArray();
}