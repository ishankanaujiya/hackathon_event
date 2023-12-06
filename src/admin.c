#include "../include/admin.h"
void menu()
{
    system("cls");
    while (1)
    {
        int choice = 0;
        printf("-------Admin Menu-------");
        printf("\n1.Add Student Record\n");
        printf("2.View Student Record\n");
        printf("3.Search Student Record\n");
        printf("4.Delete Student Record\n");
        printf("5.Edit Student Record\n");
        printf("6.Authentication Menu\n");
        printf("------------------------------------\n");
    re_choice:
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
           // addstudent();
            break;

        case 2:
           // view_record();
            break;

        case 3:
           // search();
            break;
        case 4:
           // delete ();
            break;
        case 5:
           // modify();
            break;
        case 6:
            return;
            break;

        default:
            printf("\nInvalid Choice");
            Sleep(1000);
            menu();
            break;
        }
        choice = 0;
    }
}