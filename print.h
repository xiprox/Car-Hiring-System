#ifndef CAR_HIRING_SYSTEM_PRINT_H
#define CAR_HIRING_SYSTEM_PRINT_H

#include <stdio.h>
#include <string.h>
#include "struct.h"

void printUser(struct User *user);

void printUserAsAdmin(struct User *user);

void printUserAsDev(struct User *user);

/**
 *
 */
void printUsers(struct User *users, int count, int asType) {
    for (int i = 0; i < count; i++) {
        switch (asType) {
            case 0:
                printUserAsDev(&users[i]);
                break;
            case 1:
                printUserAsAdmin(&users[i]);
                break;
            case 3: // Don't break - leave the job to the default case
            default:
                printUser(&users[i]);
        }
        printf("\n");
    }
}

/**
 *
 */
void printUser(struct User *user) {
    printf("ID: %d\n", user->id);
    printf("Username: %s\n", user->username);
}

/**
 *
 */
void printUserAsAdmin(struct User *user) {
    printUser(user);
    char type[10];
    switch (user->type) {
        case 0:
            strcpy(type, "Developer");
            break;
        case 1:
            strcpy(type, "Admin");
            break;
        case 2:
            strcpy(type, "Customer");
            break;
        default:
            strcpy(type, "?");
    }
    printf("Type: %s\n", type);
}

void printUserAsDev(struct User *user) {
    printUserAsAdmin(user);
    printf("Password: %s", user->password);
}

/**
 *
 */
void printNoValidChoiceMessage() {
    printf("Please enter a valid choice.");
}

#endif //CAR_HIRING_SYSTEM_PRINT_H
