#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Windows.h"
#include "admin.h"

typedef struct
{
	char username[31];
	unsigned char password_hash[64];
} User;
void entry();

#endif
