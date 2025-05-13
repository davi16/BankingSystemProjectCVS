//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __BANKACCOUNT__
#define __BANKACCOUNT__
#include "Branch.h"

typedef struct
{
	int number;
	Branch* branch;
}BankAccount;


void initBankAccount(BankAccount* account);
void printBankAccountDataToFile(FILE* f, const BankAccount* account, int fileType);
void printBankAccount(const void* account);
int readBankAccountFromFile(FILE* f, BankAccount* account, int fileType);
void addBranchToAccount(BankAccount* account);


#endif