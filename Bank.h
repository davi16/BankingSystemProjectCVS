//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __BANK__
#define __BANK__
#include "Lists.h"
#include "Branch.h"
#define NAME 27

typedef struct
{
	int bank_code;
	char* name;
	LIST1 branchList;
	int numOfBranches;
}Bank;

static Bank ourBank;

void initBank(int fileType);
void continueBankInit(FILE* f, Branch* b, int fileType);
void printBankBranches();
int addBranch(const Branch* branch, int fileType);
int removeBranch(const Branch* branch);
Branch* findBranchByCode(const int code);
void printBankDetails();
void freeEmployeeArraysInBranches();
void freeBank();
Branch* findEmployeeBranch(const Employee* employee);

#endif