#ifndef CAR_HIRING_SYSTEM_CAR_H
#define CAR_HIRING_SYSTEM_CAR_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

char CAR_FORMAT[] = "%d %d %s %s %d %d\n";

char ID_STORE_CARS[] = "ID_STORE_CARS.txt";
char CARS_STORE[] = "CARS_STORE.txt";
char CARS_STORE_COPY[] = "CARS_STORE_COPY.txt";

int lastCarsId = 0;

int carsCount;
int filteredResultsCount = 0; // NOTE: This is only accurate right after calling filterCars. Don't use it in any other way!

int reloadLastCarsId();

struct Car readCarFromFile(FILE *);

void writeCarToFile(FILE *, struct Car *);

/**
 *
 */
struct Car *getAllCars() {
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
 * Prepares the car header. Make sure to call this in your main function before anything else!
 */
void initCarH() {
    reloadLastCarsId();
}

/**
 * ...
 */
void updateLastCarsId(int id) {
    lastCarsId = id;
    FILE *file = fopen(ID_STORE_CARS, "w");
    fprintf(file, ID_FORMAT, id);
    fclose(file);
}

/**
 * ...
 */
int reloadLastCarsId() {
    FILE *file = fopen(ID_STORE_CARS, "r");

    if (file == NULL) {
        fopen(ID_STORE_CARS, "w");
        return lastCarsId;
    }

    fscanf(file, ID_FORMAT, &lastCarsId);
    fclose(file);
    return lastCarsId;
}


/**
 *
 */
struct Car addCar(struct Car *car) {
    FILE *file = fopen(CARS_STORE, "a");

    fprintf(file, CAR_FORMAT, ++lastCarsId, car->price, car->model, car->manufacturer, car->kilometrage, car->hired);
    fclose(file);

    /* Make sure to store the now updated last id */
    updateLastCarsId(lastCarsId);
}

/**
 *
 */
void removeCar(int id) {
    FILE *file = fopen(CARS_STORE, "r");
    FILE *tempFile = fopen(CARS_STORE_COPY, "w");

    /*
     * Loop through the first file copying any nonmatching cars (the ones that don't have the id we are removing) to a
     * temporary file
     */
    while (!feof(file)) {
        struct Car car = readCarFromFile(file);

        if (car.id != id) {
            writeCarToFile(tempFile, &car);
        }
    }

    /* Delete the original file and rename the copy as original. Then proceed to delete the now useless copy */
    fclose(file);
    int deleteResult = remove(CARS_STORE);
    if (deleteResult == 0) {
        rename(CARS_STORE_COPY, CARS_STORE);
        remove(CARS_STORE_COPY);
    } else {
        printf("\tCouldn't remove car with id %d", id);
    }

    fclose(tempFile);
}

/**
 * Replaces a car ine in the database with a given car struct only retaining the ID. Basically, everything other tha
 * the ID is replaced with th values of the car parameter.
 */
struct Car updateCar(int id, struct Car *car) {
    removeCar(id);
    car->id = id;
//    addCar(car); TODO: Uncomment when add car is implemented
}

/**
 * Asks the user for info about a car. We use this function to get values for updating cars. A car struct is passed from
 * the outside for when we want to build up on an already existing car (that has some values). If you want to get input
 * for a new car, just pass a new Car struct.
 */
struct Car *getCarFromUser(struct Car *car) {
    printf("\nPlease input the following filed values. Enter x (or -1 for numeric fields) to retain the current values.\n\n");

    /* Manufacturer */
    printf("Manufacturer (Current: %s): ", car->manufacturer);
    char manufacturer[40];
    scanf("%s", manufacturer);

    if (strcmp(manufacturer, "x") != 0) {
        strcpy(car->manufacturer, manufacturer);
    }

    /* Model */
    printf("Model (Current: %s): ", car->model);
    char model[20];
    scanf("%s", model);

    if (strcmp(model, "x") != 0) {
        strcpy(car->model, model);
    }

    /* Price */
    printf("Price (Current: %d): ", car->price);
    int price;
    scanf("%d", &price);

    if (price != -1) {
        car->price = price;
    }

    /* Kilometrage */
    printf("Kilometrage (Current %d): ", car->kilometrage);
    int kilometrage;
    scanf("%d", &kilometrage);

    if (kilometrage != -1) {
        car->kilometrage = kilometrage;
    }

    return car;
}

/**
 * Filters and returns a given car array. Pass x for text, and -1 for numeric parameters if you want to omit them.
 *
 * Also updates filteredCarsCount once executed.
 */
struct Car * filterCars(struct Car *cars, int count, char manufacturer[], char model[], int price, int kilometrage, int hired) {
    struct Car *results = malloc(count * sizeof(struct Car));

    filteredResultsCount = 0;

    for (int i = 0; i < count; i++) {
        int add = 1;

        struct Car currentCar = cars[i];

        /* Check if we are ignoring, then proceed to see if the values are the same. In case they are not, skip this iteration. */
        if (strcmp(manufacturer, "x") != 0) {
            if (strcmp(currentCar.manufacturer, manufacturer) != 0) continue;
        }

        /* Same as above */
        if (strcmp(model, "x") != 0) {
            if (strcmp(currentCar.model, model) != 0) continue;
        }

        /* Same as above with the exception that we don't check for exact values and instead have an error range of +- 50 */
        if (price != -1) {
            if (price < currentCar.price - 50 || price > currentCar.price + 50) continue;
        }

        /* Same as above */
        if (kilometrage != -1) {
            if (kilometrage < currentCar.kilometrage - 50 || kilometrage > currentCar.kilometrage + 50) continue;
        }

        /* Same, without error range here */
        if (hired != -1) {
            if (hired != currentCar.hired) continue;
        }

        if (add) {
            results[filteredResultsCount++] = currentCar;
        }
    }

    return results;
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
