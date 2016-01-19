#ifndef CAR_HIRING_SYSTEM_CAR_H
#define CAR_HIRING_SYSTEM_CAR_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

char CAR_FORMAT[] = "%d %d %s %s %d %d\n";

char ID_STORE_CARS[] = "ID_STORE_CARS.txt";
char CARS_STORE[] = "CARS_STORE.txt";
char CARS_STORE_COPY[] = "CARS_STORE_COPY.txt";

int carsCount;

struct Car readCarFromFile(FILE *);
void writeCarToFile(FILE *, struct Car *);

/**
 *
 */
struct Car * getAllCars() {
    FILE *file = fopen(CARS_STORE, "r");

    /* Return empty array if file doesn't even exist */
    if (file == NULL) {
        struct Car *empty = malloc(0);
        return empty;
    }

    struct Car container[1000];

    carsCount = 0;
    while (!feof(file)) {
        struct Car car = readCarFromFile(file);
        container[carsCount++] = car;
    }
    fclose(file);

    struct Car *cars = malloc(carsCount * sizeof(struct Car));

    for (int i = 0; i < carsCount; i++) {
        cars[i] = container[i];
    }

    return cars;
}

struct Car readCarFromFile(FILE *file) {
    struct Car car;
    fscanf(file, CAR_FORMAT, &car.id, &car.price, car.model, car.manufacturer, &car.kilometrage, &car.hired);
    return car;
}

void writeCarToFile(FILE *file, struct Car *car) {
    fprintf(file, CAR_FORMAT, car->id, car->price, car->model, car->manufacturer, car->kilometrage, car->hired);
}

/**
 *
 */
struct Car addCar(/*...*/) {
    // TODO: Implementation
}

/**
 *
 */
void removeCar(int id) {
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
