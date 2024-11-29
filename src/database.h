#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_FILE_PATH "users.bin"
#define DATABASE_TEMPORARY_FILE_PATH "users.temp.bin"

#include "user.h"

#include <stdio.h>
#include <stdbool.h>

int DATABASE_CreateFile();

int DATABASE_WriteUser(char username[USER_MAX_USERNAME_LENGTH], char password[USER_MAX_PASSWORD_LENGTH], int admin);

int DATABASE_RemoveUser(int id);

User* DATABASE_GetUser(int id);

#endif