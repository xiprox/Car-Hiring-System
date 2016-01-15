#ifndef CAR_HIRING_SYSTEM_CAR_H
#define CAR_HIRING_SYSTEM_CAR_H

#include <stdio.h>
#include <stdlib.h>

char USER_FORMAT[] = "%d %s %s %s %s %d\n";


char ID_STORE_CARS[] = "ID_STORE_CARS.txt";
char CARS_STORE[] = "CARS_STORE.txt";
char CARS_STORE_COPY[] = "CARS_STORE_COPY.txt";

int carsCount;

/**
 *
 */
struct Car *getAllCars() {
    // TODO: Implementation
}

/**
 *
 */
struct Car addUser(/*...*/) {
    // TODO: Implementation
}

/**
 *
 */
void removeUser(int id) {
    // TODO: Implementation
}

/**
 *
 */
struct Car updateCar(int id/* ... */) {
    // TODO: Implementation
}

/**
 *
 */
struct Car *filterCars(struct Car *cars) {
    // TODO: Implementation
}

/**
 *
 */
void hireCar(int id, int carId) {
    // TODO: Implementation
}

/**
 *
 */
void returnCar(int id, int carId) {
    // TODO: Implementation
}

#endif //CAR_HIRING_SYSTEM_CAR_H
