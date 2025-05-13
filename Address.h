//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __ADDRESS__
#define __ADDRESS__
#define SIZE 20 



typedef struct
{
	char country[SIZE];
	char city[SIZE];
	char street[SIZE];
	int number;
}Address;


void initAddress(Address* address);
int readAddressFromFile(FILE* f, Address* a);
void printAddressDataToFile(FILE* f, const Address* address, int fileType);
void printAddress(const void* a);

#endif
