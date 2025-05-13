//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#ifndef __DATE___
#define __DATE___

typedef struct
{
	int day;
	int month;
	int year;
}Date;

void initDate(Date* date);
int readDateFromFile(FILE* f, Date* d);
void printDateDataToFile(FILE* f, const Date* date, int fileType);
void printDate(const void* date);
int checkYear(int year);
int checkMonth(int month);
int checkDay(int day, int month, int year);
int daysInMonth(int month, int year);

#endif
