#ifndef ADMIN_H
#define ADMIN_H
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Windows.h"


struct Student
{
    char first_name[20];
    char last_name[20];
    unsigned int symbol_no;
    int DOB[3];
    int no_of_sub;
    char subject[8][30];
    int marks[8];
    float gpa[8];
    char grade[8][3];
    float cgpa;
};
void menu();
#endif