#include "student.h"
#include "stdlib.h"
#include "string.h"

void view_student_record()
{
    char empty_string[] = " ";
    int temp_DOB[3];
    system("cls");
    FILE *student_info;
    unsigned int read_symbol_no;
    printf("-------View Student Record-------");
re_symbol_no:
    printf("\nEnter your symbol number: ");
    scanf("%d", &read_symbol_no);
    fflush(stdin);
    printf("\nEnter your date of birth in  DD/MM/YYYY: ");
    printf("\nEnter day: ");
    scanf("%d", &temp_DOB[0]);
    printf("Enter month: ");
    scanf("%d", &temp_DOB[1]);
    printf("Enter year: ");
    scanf("%d", &temp_DOB[2]);
    fflush(stdin);

    student_info = fopen("resources/student_info.txt", "rb");
    if (student_info == NULL)
    {
        printf("Student_info file is exit");
        exit(1);
    }
    struct Student read_student;
    int i = 0;
    int student_found = 0;
    while (fread(&read_student, sizeof(struct Student), 1, student_info))
    {
        if (read_student.symbol_no == read_symbol_no && read_student.DOB[0] == temp_DOB[0] && read_student.DOB[1] == temp_DOB[1] && read_student.DOB[2] == temp_DOB[2])
        {
            student_found = 1;

            printf("\n\nStudent Name : %s %s", read_student.first_name, read_student.last_name);
            printf("\n\nSymbol Number: %d", read_student.symbol_no);
            printf("\n\nLevel: Bachelor");
            printf("\n\nDate of Birth: %d/%d/%d", read_student.DOB[0], read_student.DOB[1], read_student.DOB[2]);
            printf("\n\n\t_________________________________________________________________________");
            printf("\n\n\t|\tSubjects\t|\tMarks\t|\tGrade\t|\tGPA\t|");
            printf("\n\t_________________________________________________________________________");
            for (i = 0; i < read_student.no_of_sub; i++)
            {
                printf("\n\t|\t%-10s\t|%10d \t|%10s\t|%10.2f\t|", read_student.subject[i], read_student.marks[i], read_student.grade[i], read_student.gpa[i]);
            }
            printf("\n\t_________________________________________________________________________");
            printf("\n\n\t\t\t\t\t    Grade Point Average (GPA): %.2f", read_student.cgpa);
            printf("\n\t_________________________________________________________________________\n\n");
        }
    }

    if (student_found == 0)
    {
        printf("\nRecord not found! Try again!\n");
        Sleep(2000);
        system("cls");
        read_symbol_no = 0;
        fclose(student_info);
        goto re_symbol_no;
    }
    fclose(student_info);
}