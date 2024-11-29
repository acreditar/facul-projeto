#ifndef USER_H
#define USER_H

#ifndef USER_MAX_USERNAME_LENGTH
#define USER_MAX_USERNAME_LENGTH 20
#endif

#ifndef USER_MAX_PASSWORD_LENGTH
#define USER_MAX_PASSWORD_LENGTH 20
#endif

typedef struct User {
    char name[USER_MAX_USERNAME_LENGTH];

    char password[USER_MAX_PASSWORD_LENGTH];

    int id;

    int admin;
} User;

#endif
