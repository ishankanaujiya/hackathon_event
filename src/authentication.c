#include "authentication.h"

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
			logged_in = login();
			if (logged_in)
			{
				printf("\nLogged in successfully. Press enter to continue...");
				fflush(stdin);
				getchar();
				menu();
			}
			else
			{
				printf("\nLogin was not successful please try again!!!");
				fflush(stdin);
				getchar();
				continue;
			}
			break;

		case 2:
			printf("Registering...");
			if (!college_code_matches())
			{
				printf("\n College code didn't matched. Please try again ! ");
				fflush(stdin);
				getchar();
				continue;
			}
			if (account_registered())
			{
				continue;
			}
			else
			{
				printf("Failed to register account!!! Try again.");
				fflush(stdin);
				getchar();
				continue;
			}
			break;

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

int login()
{
	fflush(stdin);
	char input_username[31];
	char input_password[31];
	system("cls");
	printf("-------Login-------\n");
	printf("Enter your Login ID: ");
	scanf("%[^\n]", input_username);
	fflush(stdin);
	printf("Enter your password: ");
	scanf("%[^\n]", input_password);
	fflush(stdin);
	if (login_validated(input_username, input_password))
	{
		return 1;
	}
	return 0;
}

int account_registered()
{
	fflush(stdin);
	User user;
	char user_name[31];
	char password[31];
	FILE *user_data;
	int user_exists;
	user_data = fopen("resources/user_data.DAT", "rb+");
	if (user_data == NULL)
	{
		printf("Could not read the user_data file or could not create the file.");
		Sleep(2000);
		exit_program(1);
	}

	system("cls");
	printf("--------Register Account-------\n");

re_username:
	printf("Enter a new login ID: ");
	scanf("%s", user_name);
	fflush(stdin);

	// Check if the user is already registered
	user_exists = user_already_registered(user_name, user_data);
	if (user_exists)
	{
		printf("The user id: %s already exists! Press enter key to try again...", user_name);
		user_exists = 0;
		rewind(user_data);
		getchar();
		goto re_username;
	}

	// Check if username is valid
	if (!is_password_user_valid(user_name))
	{
		printf("Length of username must be >= 8 and <= 30 and can only be alphanumeric value. Try again!\n");
		memset(user_name, 0, sizeof(user_name));
		Sleep(1500);
		goto re_username;
	}
	strcpy(user.username, user_name);

// Take password input from user
re_password:
	printf("Enter a new password: ");
	scanf("%s", password);
	fflush(stdin);

	// Check if password is valid alpha numeric
	if (!is_password_user_valid(password))
	{
		printf("Length of password must be >= 8 and <= 30 and can only be alphanumeric value. Try again!\n");
		memset(password, 0, sizeof(password));
		Sleep(1500);
		goto re_password;
	}

	User read_user;
	strcpy(user.password_hash, password);
	if (is_file_empty(user_data))
	{
		fwrite(&user, sizeof(User), 1, user_data);
		fclose(user_data);
		printf("Account successfully registered. Press enter to go back to menu...");
		fflush(stdin);
		getchar();
		return 1;
	}
	else
	{
		fseek(user_data, 0, SEEK_END);
		fwrite(&user, sizeof(User), 1, user_data);
		fclose(user_data);
		printf("Account successfully registered. Press enter to go back to menu...");
		fflush(stdin);
		getchar();
		return 1;
	}
	fflush(stdin);
	fclose(user_data);
	return 0;
}

// Check if username and password contains only alphaNumberic characters
int is_password_user_valid(char password_user[])
{
	int length = strlen(password_user);
	int i = 0;
	if (length < 8 || length > 30)
		return 0;
	for (i = 0; i < length; i++)
	{
		if (!isalnum((unsigned char)password_user[i]))
		{
			return 0;
		}
	}
	return 1;
}

int user_already_registered(char username[], FILE *file)
{
	int user_exists = 0;
	User read_user;
	while (fread(&read_user, sizeof(User), 1, file))
	{
		if (strcmp(read_user.username, username) == 0)
		{
			user_exists = 1;
			break;
		}
	}
	return user_exists;
}

int login_validated(char username[], char password[])
{
	FILE *user_data;
	user_data = fopen("resources/user_data.DAT", "rb");

	if (user_data == NULL)
	{
		printf("\nThe file user_data.DAT does could not be found.!!");
	}
	User read_user_data;
	int id_matched = 0;

	while (fread(&read_user_data, sizeof(User), 1, user_data))
	{
		if ((strcmp(read_user_data.username, username) == 0) && (strcmp(read_user_data.password_hash, password) == 0))
		{
			id_matched = 1;
		}
	}

	fclose(user_data);
	return id_matched;
}

int college_code_matches()
{
	system("cls");
	int input_length;
	char input_code[30];
	char code[30];
	FILE *college_code;
	college_code = fopen("resources/college_codes.txt", "r");
	if (college_code == NULL)
	{
		printf("\n College Code file not found.");
		return 0;
	}

	fflush(stdin);
	printf("\n Enter your College code: ");
	scanf("%[^\n]", input_code);
	fflush(stdin);

	while (fgets(code, sizeof(code), college_code) != NULL)
	{
		code[strcspn(code, "\n")] = '\0';
		if (strcmp(code, input_code) == 0)
		{
			fclose(college_code);
			return 1;
		}
	}
	fclose(college_code);
	return 0;
}
