#include "authentication.h"
#include"admin.h"

void entry()
{
	while (1)
	{
		system("cls");
		int selected_option = 0;
		int logged_in = 0;
		printf("-------Authentication Menu-------\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Main Menu\n");
		printf("Please enter your choice: ");
		scanf("%d", &selected_option);
		switch (selected_option)
		{
		case 1:
			printf("going to login");
            menu();
		case 2:
			printf("Registering...");

		case 3:
			return;
			break;

		default:
			printf("Invalid option selected. Try again");
			Sleep(666);
			printf(".");
			Sleep(666);
			printf(".");
			Sleep(666);
			printf(".");
			Sleep(666);
			fflush(stdin);
			selected_option = 0;
			break;
		}
		fflush(stdin);
	}
}

