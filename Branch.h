//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __BRANCH__
#define __BRANCH__
#include "Address.h"
#include "Employee.h"

typedef struct
{
	int code;
	//nameLength is saved to the binary file as an int
	char* name;//dynamic string
	Address address;
	Employee** employees;//dynamyc array of pointers
	int numOfEmployees;
}Branch;

void initBranch(Branch* branch);
Employee** initEmployeesArray(Branch* b);
int readBranchFromFile(FILE* f, Branch* b, int fileType);
void printBranchDataToFile(FILE* f, const Branch* branch, int fileType);
void printBranch(const void* branch);
void addEmployeeToBranch(const Employee* e, Branch* b);
void deleteEmployeeFromBranch(const Employee* e, Branch* b);
int isSameBranch(const Branch* b1, const Branch* b2);
void printBranchEmployees(const Branch* b);
void freeEmployeesInArray(Branch* pB);
int findEmployeeInBranch(const Branch* branch, const Employee* employee);

#endif
