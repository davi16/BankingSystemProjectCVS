//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "CustomerManager.h"
#include "EmployeeManager.h"
#include "HumanDetails.h"
#include "general.h"

void initHumanData(HumanData* hData, char humanType)
{
	printf("Please enter ID: ");
	hData->id = initInteger(1, 9);
	if (humanType == 'e')
	{
		while (findEmployeeByNameOrID("", hData->id))
		{
			printf("Employee with this id already exist, Try again: ");
			hData->id = initInteger(1, 9);
		}
	}
	if (humanType == 'c')
	{
		while (findCustomerByID(hData->id))
		{
			printf("Customer with this id already exist, Try again: ");
			hData->id = initInteger(1, 9);
		}
	}
	printf("Please enter name: ");
	initString(hData->name, sizeof(hData->name));
	initDate(&hData->dateOfBirth);
	initAddress(&hData->address);
}

int readHumanDataFromFile(FILE* f, HumanData* h, int fileType)
{
	switch (fileType) {
	case 1:
		if (fscanf(f, "%d", &h->id) != 1)
			return 0;
		fileFlush(f);
		if (!fgets(h->name, sizeof(h->name), f))
			return 0;
		h->name[strcspn(h->name, "\n")] = 0;
		if (!readDateFromFile(f, &h->dateOfBirth))
			return 0;
		if (!readAddressFromFile(f, &h->address))
			return 0;
		fileFlush(f);
		break;
	case 2:
		if (fread(&h->id, sizeof(int), 1, f) != 1)
			return 0;
		if (fread(h->name, sizeof(h->name), 1, f) != 1)
			return 0;
		h->name[strcspn(h->name, "\n")] = 0;
		if (fread(&h->dateOfBirth, sizeof(Date), 1, f) != 1)
			return 0;
		if (fread(&h->address, sizeof(Address), 1, f) != 1)
			return 0;
		break;
	}
	return 1;
}

void printHumanDataToFile(FILE* f, const HumanData* human, int fileType)
{
	switch (fileType) {
	case 1:
		fprintf(f, "\n%ld\n%s\n", human->id, human->name);
		printDateDataToFile(f, &human->dateOfBirth, fileType);
		printAddressDataToFile(f, &human->address, fileType);
		fprintf(f, "\n");
		break;
	case 2:
		fwrite(&human->id, sizeof(int), 1, f);
		fwrite(&human->name, SIZE, 1, f);
		printDateDataToFile(f, &human->dateOfBirth, fileType);
		printAddressDataToFile(f, &human->address, fileType);
		break;
	}
}

void printHumanData(const void* hData)
{
	HumanData* h = (HumanData*)hData;
	printf("ID: %d, Name: %s, ", h->id, h->name);
	printf("DOB: ");
	printDate(&h->dateOfBirth);
	printAddress(&h->address);
}
