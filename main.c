//Students submitting: Kristina goldin 317958700, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "exe.h"


int main()
{

	firstInit();

	char select;

	printf("            BANK MANAGER SYSTEM\n");

	do
	{
		printf("------------------------------------------\n\n");
		printf("		Main Menu\n");
		printf("1 - Add new branch to system.\n");
		printf("2 - Show bank details and all bank branches.\n");
		printf("3 - Add new customer.\n");
		printf("4 - Show all customers of the bank. \n");
		printf("5 - Add new employee.\n");
		printf("6 - Show all bank employees.\n");
		printf("7 - Sort bank employees.\n");
		printf("8 - Search bank employees.\n");
		printf("9 - Update employee salary.\n");
		printf("a - Show all bank accounts.\n");
		printf("b - Show all employees in a branch.\n");
		printf("c - Delete branch/customer/employee.\n");
		printf("e - Exit program.\n");

		printf(" Please enter an option from the main menu: ");
		(void)scanf("%c", &select);
		while (getchar() != '\n') {};//clearing buffer

		switch (select)
		{
		case '1':
			option1();
			break;
		case '2':
			option2();
			break;
		case '3':
			option3();
			break;
		case '4':
			option4();
			break;
		case '5':
			option5();
			break;
		case '6':
			option6();
			break;
		case '7':
			option7();
			break;
		case '8':
			option8();
			break;
		case '9':
			option9();
			break;
		case 'a':
			option10();
			break;
		case 'b':
			option11();
			break;
		case 'c':
			option12();
			break;
		case 'e':
			Exit();
			printf("Exitting... Have a nice day!");
			break;
		default:
			printf("You entered wrong input, Try again. \n\n");
			break;
		}
	} while (select != 'e');
	return 0;
}