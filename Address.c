//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Address.h"
#include "general.h"

void initAddress(Address* address)
{
	printf("To initialize an adress, enter following parameters:\n");
	printf("Country: ");
	initString(address->country, sizeof(address->country));
	printf("City: ");
	initString(address->city, sizeof(address->city));
	printf("Street: ");
	initString(address->street, sizeof(address->street));
	printf("Number: ");
	address->number = initInteger(1, 6);
}

int readAddressFromFile(FILE* f, Address* a)
{
	if (!fgets(a->country, sizeof(a->country), f))
		return 0;
	if (!fgets(a->city, sizeof(a->city), f))
		return 0;
	if (!fgets(a->street, sizeof(a->street), f))
		return 0;
	if (fscanf(f, "%d", &a->number) != 1)
		return 0;
	a->country[strcspn(a->country, "\n")] = 0;
	a->city[strcspn(a->city, "\n")] = 0;
	a->street[strcspn(a->street, "\n")] = 0;
	return 1;
}

void printAddressDataToFile(FILE* f, const Address* address, int fileType)
{
	switch (fileType) {
	case 1:
		fprintf(f, "%s\n%s\n%s\n%ld", address->country, address->city, address->street, address->number);
		break;
	case 2:
		if (fwrite(address, sizeof(Address), 1, f) != 1) { fclose(f);return; }
		break;
	}
}

void printAddress(const void* a)
{
	Address* address = (Address*)a;
	printf("Address: %s, %s, %s, %d\n", address->country, address->city, address->street, address->number);
}
