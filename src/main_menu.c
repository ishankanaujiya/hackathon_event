#include "../include/mainmenu.h"
#include "../include/admin.h"
#include "../include/authentication.h"
void main_menu()
{
	while (1)
	{

		int choice = 0;
		printf("\n--------Main Menu-------");
		printf("\n1. Admin");
		printf("\n2. Student");
		printf("\n3. Exit");
		printf("\nPlease enter your choice: ");
		scanf("%d", &choice);
		fflush(stdin);

		switch (choice)
		{
		case 1:
			//admin function
          //  menu();
		   entry();
			break;

		case 2:
			//student function
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("The entered choice is not valid. Please try again....");
            Sleep(2000);
			break;
		}
	}
}
