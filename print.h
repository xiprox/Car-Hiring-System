#ifndef CAR_HIRING_SYSTEM_PRINT_H
#define CAR_HIRING_SYSTEM_PRINT_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

void printHeaderBasedOnUserType(int);

void printUserHeader();

void printUser(struct User *);

void printUserHeaderAsAdmin();

void printUserAsAdmin(struct User *);

void printUserHeaderAsDev();

void printUserAsDev(struct User *);

void printCarsHeader();

void printCar(struct Car *car);

void printHiresHeader();

void printHire(struct Hire *);

////////// User printing functions

/**
 * Prints a collection of users in table-like fashion.
 */
void printUsers(struct User *users, int count, int asType) {
    printHeaderBasedOnUserType(asType);
    switch (asType) {
        case 0:
            for (int i = 0; i < count; i++) {
                printUserAsDev(&users[i]);
            }
            break;
        case 1:
            for (int i = 0; i < count; i++) {
                printUserAsAdmin(&users[i]);
            }
            break;
        case 3: // Don't break - leave the job to the default case
        default:
            for (int i = 0; i < count; i++) {
                printUser(&users[i]);
            }
    }
    printf("\n");
}

/**
 * Prints a user table header based on a given type (dev, admin, or customer).
 */
void printHeaderBasedOnUserType(int type) {
    switch (type) {
        case 0:
            printUserHeaderAsDev();
            break;
        case 1:
            printUserHeaderAsAdmin();
            break;
        case 3: // Don't break - leave the job to the default case
        default:
            printUserHeader();
    }
}

/**
 * Prints the user table header.
 *
 * This function will only print the ID and Username columns.
 */
void printUserHeader() {
    printf("ID\t\ttUsername\t\tName\t\tSurname\n");
}

/**
 * Prints a user as a table line.
 */
void printUser(struct User *user) {
    printf("%d\t\t%s\t\t%s\t\t%s\n", user->id, user->username, user->name, user->surname);
}

/**
 * Prints the user table header.
 *
 * This function will print all information except the Password.
 */
void printUserHeaderAsAdmin() {
    printf("ID\t\tUsername\t\tName\t\tSurname\t\tType\n");
    printf("______________________________\n");
}

/**
 * Prints a user as a table line.
 *
 * The admin command prints all information except password.
 */
void printUserAsAdmin(struct User *user) {
    printf("%d\t%s\t\t%s\t\t%s\t\t%s\n", user->id, user->username, user->name, user->surname, getTypeString(user));
}

/**
 * Prints the user table header. This function will print all information.
 */
void printUserHeaderAsDev() {
    printf("ID\tUsername\t\tPassword\t\tName\t\tSurname\t\tType\n");
    printf("________________________________________\n");
}

/**
 * Prints a user as a table line.
 *
 * The dev print command prints all information.
 */
void printUserAsDev(struct User *user) {
    printf("%d\t%s\t\t%s\t\t\t%s\t\t%s\t\t%s\n", user->id, user->username, user->password, user->name, user->surname,
           getTypeString(user));
}



////////// Car printing functions

/**
 * Prints a collection of cars in table-like fashion.
 */
void printCars(struct Car *cars, int count) {
    printCarsHeader();
    for (int i = 0; i < count; i++) {
        printCar(&cars[i]);
    }
    printf("\n");
}

/**
 * Prints the car table header
 */
void printCarsHeader() {
    printf("ID\tManufacturer\t\tModel\t\tPrice\t\tKilometrage\t\tStatus\n");
    printf("----------------------------------------------------------------------\n");
}

/**
 * Prints a car as a table line
 */
void printCar(struct Car *car) {
    printf("%d\t%s\t\t%s\t\t%d\t\t%d\t\t%s\n", car->id, car->manufacturer, car->model, car->price, car->kilometrage,
           car->hired ? "Hired" : "Available");
}



////////// Hire printing functions

/**
 * Prints a collection of hires in table-like fashion.
 */
void printHires(struct Hire *hires, int count) {
    printHiresHeader();
    for (int i = 0; i < count; i++) {
        printHire(&hires[i]);
    }
    printf("\n");
}

/**
 * Prints the hire table header
 */
void printHiresHeader() {
    printf("ID\tCar ID\tUser ID\tHire Date\tReturn Date\n");
    printf("----------------------------------------------------\n");
}

/**
 * Prints a hire as a table line
 */
void printHire(struct Hire *hire) {
    /*
    char hiredBuffer[80];
    char returnBuffer[80];

    struct tm *hiredTm = localtime(&hire->hireDate);
    struct tm *returnTm = localtime(&hire->returnDate);

    strftime(hiredBuffer, 80, "%x", hiredTm);
    strftime(returnBuffer, 80, "%x", returnTm);
    */

    printf("%d\t%d\t\t%d\t\t%s\t%s\n", hire->id, hire->carId, hire->userId, "?",
           hire->returnDate != 0 ? "?" : "Not returned");

    // TODO: Fix this...
}


////////// Misc stuff

/**
 * Prints the obvious message
 */
void printNoValidChoiceMessage() {
    printf("Please enter a valid choice.");
}

void printWrongUsernameOrPassword() {
    printf("Wrong username or password. Please try again. Input x to exit.\n");
}

void printInvalidId() {
    printf("Please enter a valid id.\n");
}

void printNoAvailableHireSlots() {
    printf("You have reached the maximum number of hires you can make. (3)\n");
}

/**
 * Prints a row with any given column params with two tab spaces in between each.
 *
 * Unsupported
 */
void printRow(int columnCount, ...) {
    /*
     * Was going to write a function that prints a row for just anything. Figured there's no way to tell a vararg type
     * at runtime in C though. Such letdown.
     */
}

#endif //CAR_HIRING_SYSTEM_PRINT_H
