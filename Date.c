//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "general.h"
#include "Date.h"

void initDate(Date* date)
{
	printf("Input details for date (day month year): ");
	while (scanf("%d %d %d", &date->day, &date->month, &date->year) != 3)
	{
		printf("Please enter number values (day month year): ");
		flush();
	}
	flush();
	date->year = checkYear(date->year);
	date->month = checkMonth(date->month);
	date->day = checkDay(date->day, date->month, date->year);

}

int readDateFromFile(FILE* f, Date* d)
{
	if (fscanf(f, "%d %d %d", &d->day, &d->month, &d->year) != 3)
		return 0;
	fileFlush(f);
	return 1;
}

void printDateDataToFile(FILE* f, const Date* date, int fileType)
{
	switch (fileType) {
	case 1:
		fprintf(f, "%ld %ld %ld\n", date->day, date->month, date->year);
		break;
	case 2:
		if (fwrite(date, sizeof(Date), 1, f) != 1) { fclose(f);return; }
		break;
	}
}

void printDate(const void* date)
{
	Date* d = (Date*)date;
	printf("%d/%d/%d, ", d->day, d->month, d->year);
}

int checkYear(int year)
{
	time_t seconds = time(NULL);
	struct tm* current_time = localtime(&seconds);
	if (year < 1900 || year >(current_time->tm_year + 1900))
	{
		printf("The year is not in range, Try again");
		(void)scanf("%d", &year);
		while (getchar() != '\n');
		return checkYear(year);
	}
	return year;
}
int checkMonth(int month)
{
	if (month < 1 || month > 12)
	{
		printf("The month is not in range, Try again");
		(void)scanf("%d", &month);
		while (getchar() != '\n');
		return checkMonth(month);
	}
	return month;
}

int checkDay(int day, int month, int year)
{
	int numOfDays = daysInMonth(month, year);
	if (day < 1 || day > numOfDays)
	{
		printf("The day is not in range, Try again");
		(void)scanf("%d", &day);
		while (getchar() != '\n');
		return checkDay(day, month, year);
	}
	return day;
}



int daysInMonth(int month, int year) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		// Check for leap year
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
		else {
			return 28;
		}
	default:
		return -1; // Invalid month
	}
}
