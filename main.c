#include <stdio.h>
#include "struct.h"
#include "user.h"
#include "print.h"
#include "auth.h"
#include "car.h"

void devMode();

void adminMode();

void customerMode();

int promptLogin(int type);

int main() {
    printf("Welcome. Banners are still in print...\n\n");

    /* Initialization of some stuff */
    initUserH();
    initCarH();

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
                devMode();
                break;
            case 2:
                adminMode();
                break;
            case 3:
                customerMode();
            default:
                printNoValidChoiceMessage();
        }
    }

    return 0;
}

void devMode() {
    if (promptLogin(TYPE_DEV) <= 0) {
        main();
        return;
    }

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

                printf("\tName (max 20 characters): ");
                scanf("%s", newUser.name);

                printf("\tSurname (max 20 characters): ");
                scanf("%s", newUser.surname);

                int isAdmin = 0;
                printf("\tAdmin? (1 or 0. 0 by default.): ");
                scanf("%d", &isAdmin);
                newUser.type = isAdmin ? TYPE_ADMIN : TYPE_CUSTOMER;

                addUser(&newUser);
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

void adminMode() {
    if (promptLogin(TYPE_ADMIN) <= 0) {
        main();
        return;
    }

    int choice = -1;
    while (choice != 0) {
        printf(" ----------------------------\n");
        printf("|          ADMIN MENU        |\n");
        printf(" ----------------------------\n");
        printf("\n");
        printf("\t0: <—\n");
        printf("\t1: List all cars in database\n");
        printf("\t2: Add a car\n");
        printf("\t3: Remove a car\n");
        printf("\t4: Search cars by attributes (model, price, etc.)\n");
        printf("\t5: Update car info\n");
        printf("Please make a choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 0:
                main();
                break;
            case 1: {
                struct Car *cars = getAllCars();
                if (carsCount != 0) {
                    printCars(cars, carsCount);
                } else {
                    printf("\tNo cars found.\n\n");
                }
            }
                break;
            case 2:
                // TODO
                break;
            case 3:
                printf("Removing a car: \n");
                printf("\tWhich car would you like to remove (ID): ");
                int id;
                scanf("%d", &id);
                removeCar(id);
                break;
            case 4:
                // TODO
                break;
            case 5:
                printf("Updating a car: \n");
                printf("\tWhich car would you like to update (ID): ");
                int carId;
                scanf("%d", &carId);

                struct Car updatedCar;
                updateCar(carId, getCarFromUser(&updatedCar));
                break;
            default:
                printNoValidChoiceMessage();
        }
    }
}

void customerMode() {
    if (promptLogin(TYPE_CUSTOMER) <= 0) {
        main();
        return;
    }

    int choice = -1;
    while (choice != 0) {
        printf(" ----------------------------\n");
        printf("|       CUSTOMER MENU        |\n");
        printf(" ----------------------------\n");
        printf("\n");
        printf("\t0: <—\n");
        printf("\t1: Hire a car\n");
        printf("\t2: Return a car\n");
        printf("\t3: List all hired cars\n");
        printf("\t4: List all available cars\n");
        printf("\t5: Search cars by attributes (model, price, etc.)\n");
        printf("\t6: My hired cars\n");
        printf("Please make a choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 0:
                main();
                break;
            case 1:
                // TODO
                break;
            case 2:
                // TODO
                break;
            case 3:
                // TODO
                break;
            case 4:
                // TODO
                break;
            case 5:
                // TODO
                break;
            default:
                printNoValidChoiceMessage();
        }
    }
}

int promptLogin(int type) {
    struct User user;
    user.type = type;

    int authenticated = 0;
    while (authenticated == 0) {
        printf("\nUsername: ");
        scanf("%s", user.username);

        /* Handle exit option */
        if (!strcmp(user.username, "x")) {
            authenticated = -1;
            continue;
        }

        printf("Password: ");
        scanf("%s", user.password);

        authenticated = authenticate(&user, type);

        if (!authenticated) {
            printWrongUsernameOrPassword();
        }
    }

    return authenticated;
}