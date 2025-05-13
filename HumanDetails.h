//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __HUMAN__
#define __HUMAN__
#define SIZE 20
#include "Date.h"
#include "Address.h"

typedef struct
{
	int id;
	char name[SIZE];
	Date dateOfBirth;
	Address address;
}HumanData;

void initHumanData(HumanData* hData, char humanType);
int readHumanDataFromFile(FILE* f, HumanData* h, int fileType);
void printHumanDataToFile(FILE* f, const HumanData* human, int fileType);
void printHumanData(const void* hData);

#endif
