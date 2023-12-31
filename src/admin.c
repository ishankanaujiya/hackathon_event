#include "../include/admin.h"
void menu()
{
    while (1)
    {
        system("cls");
        int choice = 0;
        printf("-------Admin Menu-------");
        printf("\n1.Add Student Record\n");
        printf("2.View Student Record\n");
        printf("3.Search Student Record\n");
        printf("4.Delete Student Record\n");
        printf("5.Edit Student Record\n");
        printf("6.View Pass and Fail Record\n");
        printf("7.Authentication Menu\n");
        printf("------------------------------------\n");
    re_choice:
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
            system("cls");
            addstudent();
            break;

        case 2:
            system("cls");
            view_record();
            break;

        case 3:
            system("cls");
            search();
            break;
        case 4:
            system("cls");
            delete ();
            break;
        case 5:
            system("cls");
            modify();
            break;
        case 6:
            system("cls");
            view_pass_fail();
            break;
        case 7:
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
void addstudent()
{
    char is_continue[1];
    char *grade;
    FILE *file_ptr;
    int sub_counter = 1;
    int is_student_present = 0;
    int date_is_valid;
    int name_valid;

    struct Student input_student;
    struct Student read_student;

    file_ptr = fopen("resources/student_info.txt", "rb+");
    if (file_ptr == NULL)
    {
        printf("\nFILE DOESN'T EXIST\n");
        getchar();
        exit(0);
    }

    printf("\n\t\t\t=======Add Student======\n");
    fflush(stdin);
again_name:
    printf("\nEnter first name: ");
    scanf("%s", input_student.first_name);
    fflush(stdin);
    printf("Enter last name: ");
    scanf("%s", input_student.last_name);
    fflush(stdin);
    name_valid = name_is_valid(input_student.first_name, input_student.last_name);
    if (!name_valid)
    {
        goto again_name;
    }
again_symbol:

    is_student_present = 0;
    printf("\nEnter your symbol no: ");
    scanf("%u", &input_student.symbol_no);

    if (input_student.symbol_no <= 999 || input_student.symbol_no > 9999)
    {
        printf("Symbol Number must contain 4 positive digits.\n");
        fflush(stdin);
        goto again_symbol;
    }

    rewind(file_ptr);
    while (fread(&read_student, sizeof(struct Student), 1, file_ptr))
    {
        if (read_student.symbol_no == input_student.symbol_no)
        {
            is_student_present = 1;
            printf("\nStudent with %u symbol number already exists.\n", input_student.symbol_no);

            // rewind(file_ptr);
            goto again_symbol;
        }
    }
again_DOB:
    printf("\nEnter your date of birth in  DD/MM/YYYY: ");
    printf("\nEnter day: ");
    scanf("%d", &input_student.DOB[0]);
    printf("Enter month: ");
    scanf("%d", &input_student.DOB[1]);
    printf("Enter year: ");
    scanf("%d", &input_student.DOB[2]);
    date_is_valid = check_DOB(input_student.DOB);
    if (!date_is_valid)
    {
        goto again_DOB;
    }
again_subject:
    printf("\nEnter how many subjects you want: ");
    scanf("%d", &input_student.no_of_sub);
    if (input_student.no_of_sub > 8)
    {
        printf("\nsubjects cannot be more than 8.");
        goto again_subject;
    }
    int fail = 0;
    for (int i = 0; i < input_student.no_of_sub; i++)
    {

        fflush(stdin);
        printf("\nEnter subject name: ");
        scanf("%[^\n]", input_student.subject[i]);
        fflush(stdin);
    again_marks:
        printf("Enter  marks for %s: ", input_student.subject[i]);
        scanf("%d", &input_student.marks[i]);
        if (input_student.marks[i] < 0 || input_student.marks[i] > 100)
        {
            printf("\nInvalid input for marks.");
            goto again_marks;
        }
        if (input_student.marks[i] >= 0 && input_student.marks[i] <= 39)
        {
            fail++;
        }

        input_student.gpa[i] = calculate_gpa(input_student.marks[i]);
        grade = calculate_grade(input_student.marks[i]);
        strcpy(input_student.grade[i], grade);
        free(grade);
    }
    if (fail > 0)
    {
        strcpy(input_student.remarks, "FAIL");
    }
    else
    {
        strcpy(input_student.remarks, "PASS");
    }

    input_student.cgpa = calculate_cgpa(input_student.no_of_sub, input_student.gpa);

    if (!is_student_present)
    {
        fseek(file_ptr, 0, SEEK_END);
        fwrite(&input_student, sizeof(struct Student), 1, file_ptr);
    }
    printf("\nRECORD HAS BEEN ADDED SUCCESFULLY");
    fclose(file_ptr);
    Sleep(2000);
}

void view_record()
{
    struct Student read_student;
    FILE *file_ptr;
    int i;

    file_ptr = fopen("resources/student_info.txt", "rb");
    if (file_ptr == NULL)
    {
        perror("\nFILE DOESN'T EXIST\n");
        fflush(stdin);
        getchar();
        exit(0);
    }
    printf("\n\t\t\t=======Student Record======\n");

    while (fread(&read_student, sizeof(struct Student), 1, file_ptr))
    {

        printf("\n\nStudent Name : %s %s", read_student.first_name, read_student.last_name);
        printf("\n\nSymbol Number: %u", read_student.symbol_no);
        printf("\n\nLevel: Bachelor ( BIT 1st SEM )");
        printf("\n\nDate of Birth: %d /%d /%d", read_student.DOB[0], read_student.DOB[1], read_student.DOB[2]);
        printf("\n\n\n\t\t\t    Pre-Board Examination GradeSheet");
        printf("\n\t_________________________________________________________________________");
        printf("\n\n\t|\tSubjects\t|\tMarks\t|\tGrade\t|\tGPA\t|");
        printf("\n\t_________________________________________________________________________");
        for (i = 0; i < read_student.no_of_sub; i++)
        {
            printf("\n\t|\t%-10s\t|%10d \t|%10s\t|%10.2f\t|", read_student.subject[i], read_student.marks[i], read_student.grade[i], read_student.gpa[i]);
        }
        printf("\n\t_________________________________________________________________________");
        printf("\n\n\t Remarks: %s \t\t\t    Grade Point Average (GPA): %.2f", read_student.remarks, read_student.cgpa);
        printf("\n\t_________________________________________________________________________\n\n");
        printf("\n............................................................................................................\n\n");
    }
    fclose(file_ptr);
    printf("\nPress enter to go back to menu...");
    fflush(stdin);
    getchar();
}

void search()
{
    struct Student read_student;
    int symbol_no = 0, found_student = 0;
    FILE *file_ptr;
    int no_of_sub;
    int i;
    file_ptr = fopen("resources/student_info.txt", "rb");
    if (file_ptr == NULL)
    {
        printf("\nFILE DOESN'T EXIST\n");
        exit(0);
    }
    // system("cls");
    printf("\n\t\t\t======= Search Records ======\n\n");
re_symbol:
    printf("\nEnter symbol number: ");
    scanf("%d", &symbol_no);
    printf("\n_________________________________________________________________________________________");
    while (fread(&read_student, sizeof(struct Student), 1, file_ptr))
    {
        if (read_student.symbol_no == symbol_no)
        {
            found_student = 1;
            printf("\n\n\nStudent Name : %s %s", read_student.first_name, read_student.last_name);
            printf("\n\nSymbol Number: %u", read_student.symbol_no);
            printf("\n\nLevel: Bachelor ( BIT 1st SEM )");
            printf("\n\nDate of Birth: %d /%d /%d", read_student.DOB[0], read_student.DOB[1], read_student.DOB[2]);
            printf("\n\n\n\t\t\t    Pre-Board Examination GradeSheet");
            printf("\n\t_________________________________________________________________________");
            printf("\n\n\t|\tSubjects\t|\tMarks\t|\tGrade\t|\tGPA\t|");
            printf("\n\t_________________________________________________________________________");
            for (i = 0; i < read_student.no_of_sub; i++)
            {
                printf("\n\t|\t%-10s\t|%10d \t|%10s\t|%10.2f\t|", read_student.subject[i], read_student.marks[i], read_student.grade[i], read_student.gpa[i]);
            }
            printf("\n\t_________________________________________________________________________");
            printf("\n\n\t Remarks: %s \t\t\t    Grade Point Average (GPA): %.2f", read_student.remarks, read_student.cgpa);
            printf("\n\t_________________________________________________________________________\n\n");
        }
    }
    if (found_student == 0)
    {
        printf("\nRecord not found.");
    }
    fclose(file_ptr);
    fflush(stdin);
    getchar();
}

int check_DOB(int *date)
{
    if (*date < 1 || *date > 32)
    {
        printf("\n Invalid input for day.");
        Sleep(2000);
        return 0;
    }
    else if (*(date + 1) < 1 || *(date + 1) > 12)
    {
        printf("\n Invalid input for month.");
        Sleep(2000);
        return 0;
    }
    else if (*(date + 2) < 2050 || *(date + 2) > 2070)
    {
        printf("\n Invalid input for age.");
        Sleep(2000);
        return 0;
    }
    return 1;
}
int name_is_valid(char firstname[], char lastname[])
{
    for (int i = 0; i < strlen(firstname); i++)
    {
        if (!isalpha(firstname[i]))
        {
            printf("\nInvalid input! Only alphabets are accepted.\n");
            return 0;
        }
    }
    for (int i = 0; i < strlen(lastname); i++)
    {
        if (!isalpha(lastname[i]))
        {
            printf("\nInvalid input! Only alphabets are accepted.\n");
            return 0;
        }
    }
    return 1;
}

void view_pass_fail()
{
    struct Student read_student;
    int found_student = 0;
    FILE *file_ptr;
    int no_of_sub;
    int i;
    file_ptr = fopen("resources/student_info.txt", "rb");
    if (file_ptr == NULL)
    {
        printf("\nFILE DOESN'T EXIST\n");
        exit(0);
    }

    printf("\n\n\t\t\t\t======= Pass and Fail Records ======\n\n");
    printf("\n________________________________________________________________________________________________");
    printf("\nStudent Name\t\t\t   Symbol Number\t\tGPA\t\t\tRemarks");
    printf("\n________________________________________________________________________________________________");
    while (fread(&read_student, sizeof(struct Student), 1, file_ptr))
    {
        found_student = 1;
        printf("\n\n%s %-20s", read_student.first_name, read_student.last_name);
        printf("\t\t%u", read_student.symbol_no);
        printf("\t\t\t%.2f", read_student.cgpa);
        printf("\t\t\t%s", read_student.remarks);
    }
    printf("\n________________________________________________________________________________________________");
    if (found_student == 0)
    {
        printf("\nRecord not found.");
    }
    fclose(file_ptr);
    fflush(stdin);
    getchar();
}
