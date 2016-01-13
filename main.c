#include <stdio.h>
#include "struct.h"
#include "user.h"
#include "print.h"
#include "auth.h"

void logInAsDev();

int main() {
    printf("Welcome. Banners are still in print...\n\n");

    int choice = -1;

    while (choice == -1) {
        printf("0: Exit\n");
        printf("1: Log in as dev\n");
        printf("2: Log in as admin\n");
        printf("3: Log in as customer\n");
        printf("Please make a choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("bai o/\n\n");
                break;
            case 1:
                logInAsDev();
                break;
            default:
                printNoValidChoiceMessage();
        }
    }

    return 0;
}

void logInAsDev() {
    struct User user;
    user.type = TYPE_DEV;

    int authenticated = 0;
    int exit = 0;
    while (!authenticated && !exit) {
        printf("\nUsername: ");
        scanf("%s", user.username);

        /* Handle exit option */
        if (!strcmp(user.username, "x")) {
            exit = 1;
            continue;
        }

        printf("Password: ");
        scanf("%s", user.password);

        authenticated = authenticate(&user, TYPE_DEV);

        if (!authenticated) {
            printf("\nWrong username or password. Please try again. Input x to exit.\n");
        }
    }

    if (!authenticated) return;

    int choice = -1;
    while (choice != 0) {
        printf(" ----------------------------\n");
        printf("|        DEVELOPER MENU      |\n");
        printf(" ----------------------------\n");
        printf("\n");
        printf("\t0: <—\n");
        printf("\t1: List all users\n");
        printf("\t2: Add a user\n");
        printf("\t3: Remove a user\n");
        printf("Please make a choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 0:
                main();
                break;
            case 1: {
                struct User *users = getAllUsers();
                if (usersCount != 0) {
                    printUsers(users, usersCount, 0);
                } else {
                    printf("\tNo users found.\n\n");
                }
            }
                break;
            case 2: {
                printf("Adding a new user: \n");

                struct User newUser;

                printf("\tUsername: ");
                scanf("%s", newUser.username);

                printf("\tPassword (max 20 characters): ");
                scanf("%s", newUser.password);

                int isAdmin = 0;
                printf("\tAdmin? (1 or 0. 0 by default.): ");
                scanf("%d", &isAdmin);

                addUser(newUser.username, newUser.password, isAdmin ? TYPE_ADMIN : TYPE_CUSTOMER);
            }
                break;
            case 3:
                printf("Removing a user: \n");
                printf("\tWhich user would you like to remove (ID): ");
                int id;
                scanf("%d", &id);

                removeUser(id);
                break;
            default:
                printNoValidChoiceMessage();
        }
    }
}