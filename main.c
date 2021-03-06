#include <stdio.h>
#include "struct.h"
#include "user.h"
#include "print.h"
#include "auth.h"
#include "car.h"
#include "hire.h"

void devMode();

void adminMode();

void customerMode();

void searchByAttributes();

int promptLogin(int type);

int main() {
    printf("Welcome. Banners are still in print...\n\n");

    /* Initialization of some stuff */
    initUserH();
    initCarH();
    initHiresH();

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

                addUser(&newUser, 1);
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
                printf("Adding a new car: \n");
                struct Car car;
                getCarFromUser(&car);
                addCar(&car, 1);
                break;
            case 3:
                printf("Removing a car: \n");
                printf("\tWhich car would you like to remove (ID): ");
                int id;
                scanf("%d", &id);

                if (!validateId(id)) {
                    printInvalidId();
                    break;
                }

                removeCar(id);
                break;
            case 4:
                searchByAttributes();
                break;
            case 5:
                printf("Updating a car: \n");
                printf("\tWhich car would you like to update (ID): ");
                int carId;
                scanf("%d", &carId);

                if (!validateId(carId)) {
                    printInvalidId();
                    break;
                }

                struct Car updatedCar = findCarById(carId);
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
                printf("Hiring a car: \n");
                printf("\tWhich car would you like to hire (ID): ");
                int carId;
                scanf("%d", &carId);
                struct Car car = findCarById(carId);
                hireCar(&car, currentUser.id);
                break;
            case 2:
                printf("Returning a car: \n");
                printf("\tWhich car would you like to return (Hire ID): ");
                int hireId;
                scanf("%d", &hireId);
                returnCar(hireId);
                break;
            case 3:
                printCars(filterCars(getAllCars(), carsCount, "x", "x", -1, -1, 1), filteredResultsCount);
                break;
            case 4:
                printCars(filterCars(getAllCars(), carsCount, "x", "x", -1, -1, 0), filteredResultsCount);
                break;
            case 5:
                searchByAttributes();
                break;
            case 6: {
                struct Hire *hires = getHiresByUser(currentUser.id, 0);
                if (hiresByGivenUserCount != 0) {
                    printHires(hires, hiresByGivenUserCount);
                } else {
                    printf("No hired cars.\n");
                }
            }
                break;
            default:
                printNoValidChoiceMessage();
        }
    }
}

void searchByAttributes() {
    printf("Searching cars by attributes. Input x for text, and -1 for numeric inputs to omit them.\n\n");
    char manufacturer[40], model[20];
    int price, kilometrage, hired;

    printf("Manufacturer: ");
    scanf("%s", manufacturer);

    printf("Model: ");
    scanf("%s", model);

    printf("Price (relative): ");
    scanf("%d", &price);

    printf("Kilometrage (relative): ");
    scanf("%d", &kilometrage);

    printf("Hired (1 or 0): ");
    scanf("%d", &hired);

    printCars(filterCars(getAllCars(), carsCount, manufacturer, model, price, kilometrage, hired),
              filteredResultsCount);
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

    if (authenticated == 1) {
        currentUser = findUserByUsername(user.username);
    }

    return authenticated;
}