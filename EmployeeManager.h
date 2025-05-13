//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __EMPLOYEEMANAGER__
#define __EMPLOYEEMANAGER__
#include "Employee.h"

typedef enum { notSorted, byName, byRole, bySalary, NumOfSort } sort_type;
const char* sortTitle[NumOfSort];

typedef struct
{
	Employee* employees;//dynamic array
	int numOfEmployees;
	sort_type sortBy;
}EmployeeManager;

static EmployeeManager bankEmployees;

void initEmployeeManager(int fileType);
void continueEmployeeInit(FILE* f, Employee* e, int fileType);
void printEmployeeManager();
int addEmployee(const Employee* e, int state, int branchCode);
Employee* findEmployeeByNameOrID(const char name[], const int id);
void sortEmployeeArray(sort_type sortType);
sort_type getSortTypeFromUser();
int compareEmployeeByName(const void* employee1, const void* employee2);
int compareEmployeeByRole(const void* employee1, const void* employee2);
int compareEmployeeBySalary(const void* employee1, const void* employee2);
Employee* searchEmployee();
sort_type getSortType();
void freeBankEmployeesArray();
int removeEmployee(const Employee* employee);


#endif