//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __EMPLOYEE__
#define __EMPLOYEE__
#include "HumanDetails.h"
#include <stdlib.h>


typedef enum { employee, manager, teamLeader, ShiftManager, NumRoles } employee_role;
const char* roleName[NumRoles];

typedef struct
{
	HumanData emploData;
	double salary;
	employee_role role;
}Employee;

int initNewEmployee(Employee* e);
int readEmployeeFromFile(FILE* f, Employee* e, int fileType);
employee_role getRoleFromUser();
void updateEmployeeSalary(const double salary, Employee* e);
void printEmployee(const void* e);
void printEmployeeDataToFile(FILE* f, const Employee* employee, int branchCode, int fileType);
int isEmployeeName(const Employee* e, const char name[]);
int isEmployeeID(const Employee* e, const int id);
int isSameEmployee(const Employee* e1, const Employee* e2);
void freeEmployee(const void* e);

#endif
