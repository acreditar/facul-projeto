#include "auth.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "database.h"
#include "settings.h"

User* s_AuthenticatedUser;

int AUTH_AuthenticateUser(char* username, char* password) {
    FILE* file = fopen(DATABASE_FILE_PATH, "rb+");

    if (file == NULL) {
        printf("Erro ao abrir a database de usuários.\n");
        Sleep(RESPONSE_Sleep_TIME_IN_MILLISECONDS);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);

    int count = ftell(file) / sizeof(User);

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < count; i++) {
        User* temp = DATABASE_GetUser(i);

        if (temp != NULL) {
            if (strcmp(temp->name, username) == 0 && strcmp(temp->password, password) == 0) {
                s_AuthenticatedUser = temp;

                fclose(file);

                return EXIT_SUCCESS;
            }
        }

        free(temp);
    }

    fclose(file);

    return EXIT_FAILURE;
}

void AUTH_ShowPanel() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    int attempts = 0;

    printf("██╗      ██████╗  ██████╗ ██╗███╗   ██╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██║████╗  ██║\n");
    printf("██║     ██║   ██║██║  ███╗██║██╔██╗ ██║\n");
    printf("██║     ██║   ██║██║   ██║██║██║╚██╗██║\n");
    printf("███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║\n");
    printf("╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝\n");

    while (attempts < PASSWORD_MAX_ATTEMPTS) {
        printf("Nome de usuário:");
        scanf("%s", username);

        printf("Senha de usuário:");

        int i = 0;
        char ch;

        while (1) {
            ch = getch();

            if (ch == '\r') {
                password[i] = '\0';
                printf("\n");
                break;
            }

            if (ch == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else if (i < PASSWORD_MAX_LENGTH - 1) {
                password[i] = ch;
                printf("*");
                i++;
            }
        }

        if (AUTH_AuthenticateUser(username, password) == EXIT_SUCCESS) {
            printf("Login realizado com sucesso!\n\n");
            system("cls");
            return;
        } else {
            attempts++;

            printf("Usuário ou senha incorretos, tente novamente. %d tentativas restantes.\n", PASSWORD_MAX_ATTEMPTS - attempts);
        }
    }

    printf("Número máximo de tentativas de login alcançado. O programa está sendo fechado.\n");
    Sleep(SHUTDOWN_COOLDOWN_IN_MILLISECONDS);
    exit(EXIT_FAILURE);
}