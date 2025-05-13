//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "general.h"
#include "CustomerManager.h"

char* initString(char* buf, int size)
{
	//function inits string and replaces \n with \0 (end of string)
	if (buf != NULL && size > 0)
	{
		if (fgets(buf, size, stdin))
		{
			buf[strcspn(buf, "\n")] = '\0';
			buf[0] = toupper(buf[0]);
			strcpy(buf, trim(buf));
			return buf;
		}
		*buf = '\0';
	}
	return NULL;
}


int compareTwoStringsNoCaseSensetive(char s1[],char s2[])
{
	int i = 0;
	if (s1 == NULL || s2 == NULL)
		return 0;
	if (strlen(s1) != strlen(s2))
		return 0;
	while (s1[i])
	{
		if (tolower(s1[i]) != tolower(s2[i]))
			return 0;
		i++;
	}
	return 1;
}

void generalFunction(void* arr, size_t size, size_t elem_size, void (*func)(void*))
{
	for (size_t i = 0; i < size; i++)
	{
		void* elem = (char*)arr + i * elem_size;
		func(elem);
	}
}

char* ltrim(char* s)
{
	while (isspace(*s)) s++;
	return s;
}

char* rtrim(char* s)
{
	char* back = s + strlen(s);
	while (isspace(*--back));
	*(back + 1) = '\0';
	return s;
}

char* trim(char* s)
{
	return rtrim(ltrim(s));
}


char* initDynamicString()
{
	char* theStr = NULL;
	char inpStr[MAX_LENGTH];

	initString(inpStr, sizeof(inpStr));
	theStr = _strdup(inpStr);
	return theStr;

}

int initInteger(int min, int max)
{
	int number, temp, counter = 0;
	while (!scanf("%d", &number))   // on invalid conversion the scanf return 0 
	{
		printf("Inlvalid data\n");
		printf("Please enter a integer value\n");
		flush();
	}
	flush();
	temp = number;
	while (temp != 0)
	{
		temp /= 10;
		counter++;
	}
	if (counter < min || counter > max)
	{
		printf("Input must consist of %d to %d digits! Try again ", min, max);
		return initInteger(min, max);
	}
	return number;
}

void flush()
{
	char c;
	while ((c = getchar()) != '\n');
	return;
}

void fileFlush(FILE* f)
{
	while (fgetc(f) != '\n') {};
	return;
}


