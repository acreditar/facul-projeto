#include <stdlib.h>
#include <windows.h>

#include "database.h"
#include "splash.h"
#include "auth.h"
#include "menu.h"
#include "settings.h"

int main(void) {    
    SetConsoleOutputCP(CP_UTF8);

#if !DEBUG
    SPLASH_ShowSplashScreen();
#endif

    DATABASE_CreateFile();

    char username[USER_MAX_USERNAME_LENGTH];
    char password[USER_MAX_PASSWORD_LENGTH];

    strncpy(username, "admin", USER_MAX_USERNAME_LENGTH);
    strncpy(password, "admin", USER_MAX_PASSWORD_LENGTH);

    DATABASE_WriteUser(username, password, true);

    AUTH_ShowPanel();

    MENU_Show();

    return EXIT_SUCCESS;
}