//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __GENERIC__
#define __GENERIC__
#define MAX_LENGTH 100
#define FILEOPENINGERROR(str) printf(#str ".txt file not found\nYou may add " #str " manually through the main menu.\n");
#define STRUCTREADINGERROR(str) printf("Error reading a " #str " from the file!\n");
#define ADDINGTOFILEERROR(str) printf("Couldn't add new " #str " to the file!!\n");
#define DELETINGFROMFILEERROR(str) printf("Couldn't delete the " #str " from the file!!\n");



char* initString(char* buf, int size);
int compareTwoStringsNoCaseSensetive(char s1[], char s2[]);
char* ltrim(char* s);
char* rtrim(char* s);
char* trim(char* s);
char* initDynamicString();
int initInteger(int min, int max);
void flush();
void fileFlush(FILE* f);
void generalFunction(void* arr, size_t size, size_t elem_size, void (*func)(void*));

#endif
