#include "database.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "user.h"

int DATABASE_CreateFile() {
    FILE* file = fopen(DATABASE_FILE_PATH, "a");

    if (file == NULL) {
        return EXIT_FAILURE;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

int DATABASE_WriteUser(char username[USER_MAX_USERNAME_LENGTH], char password[USER_MAX_PASSWORD_LENGTH], int admin) {
    FILE* file = fopen(DATABASE_FILE_PATH, "ab+");

    if (file == NULL) {
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);

    int count = ftell(file) / sizeof(User);

    fseek(file, 0, SEEK_SET); 

    for (int i = 0; i < count; i++) {
        User* temp = DATABASE_GetUser(i); 

        if (temp != NULL) {
            if (strcmp(temp->name, username) == 0) {
                fclose(file);
                return EXIT_FAILURE;
            }
        }

        free(temp); 
    }

    User user;

    strncpy(user.name, username, USER_MAX_USERNAME_LENGTH);
    strncpy(user.password, password, USER_MAX_PASSWORD_LENGTH);

    user.admin = admin;

    fseek(file, 0, SEEK_END);

    user.id = ftell(file) / sizeof(User);

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    return EXIT_SUCCESS;
}

int DATABASE_RemoveUser(int id) {
    FILE* file = fopen(DATABASE_FILE_PATH, "rb+");

    if (file == NULL) {
        return EXIT_FAILURE;
    }

    FILE* temp = fopen(DATABASE_TEMPORARY_FILE_PATH, "wb");

    if (temp == NULL) {
        fclose(file);
        return EXIT_SUCCESS;
    }

    User user;

    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (user.id != id) {
            fwrite(&user, sizeof(User), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(DATABASE_FILE_PATH);
    rename(DATABASE_TEMPORARY_FILE_PATH, DATABASE_FILE_PATH);

    return EXIT_SUCCESS;
}

User* DATABASE_GetUser(int id) {
    FILE* file = fopen(DATABASE_FILE_PATH, "rb+");

    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    User* user = (User*)malloc(sizeof(User));

    if (user == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fseek(file, sizeof(User) * id, SEEK_SET);

    if (fread(user, sizeof(User), 1, file) != 1) {
        free(user); 
        fclose(file);
        return NULL;
    }

    fclose(file);
    return user; 
}
