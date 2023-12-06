#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "Windows.h"
#include "utility.h"
#include "admin.h"

typedef struct
{
    char username[31];
    unsigned char password_hash[64];
    //char college_code[30];
} User;

void entry();
int login();
int college_code_matches();
int account_registered();
int is_password_user_valid(char password_user[]);
int user_already_registered(char username[], FILE *file);
int login_validated(char username[], char password[]);

#endif