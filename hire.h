#ifndef CAR_HIRING_SYSTEM_HIRE_H
#define CAR_HIRING_SYSTEM_HIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "user.h"
#include "car.h"
#include "print.h"

char HIRE_FORMAT[] = "%d %d %d %d %d\n";

char ID_STORE_HIRES[] = "ID_STORE_HIRES.txt";
char HIRES_STORE[] = "HIRES_STORE.txt";
char HIRES_STORE_COPY[] = "HIRES_STORE_COPY.txt";

int lastHiresId = 0;

int hiresByGivenUserCount = 0;
int hiresCount = 0;

int reloadLastHiresId();

struct Hire readHireFromFile(FILE *);

void writeHireToFile(FILE *, struct Hire *);

/**
 * Returns all hires in the database
 */
struct Hire *getAllHires() {
    FILE *file = fopen(HIRES_STORE, "r");

    /* Return empty array if file doesn't even exist */
    if (file == NULL) {
        struct Hire *empty = malloc(0);
        return empty;
    }

    struct Hire container[1000];

    hiresCount = 0;
    while (!feof(file)) {
        struct Hire hire = readHireFromFile(file);
        container[hiresCount++] = hire;
    }
    fclose(file);

    struct Hire *hires = malloc(hiresCount * sizeof(struct Hire));

    for (int i = 0; i < hiresCount; i++) {
        hires[i] = container[i];
    }

    return hires;
}

/**
 * Returns all hires by a given user. Pass 1 for includePast to get returned hires too.
 */
struct Hire *getHiresByUser(int userId, int includePast) {
    struct Hire *hires = getAllHires();
    struct Hire *filteredHires = malloc(sizeof(hires));

    hiresByGivenUserCount = 0;
    for (int i = 0; i < hiresCount; i++) {
        if (hires[i].userId == userId) {
            if (includePast || hires[i].returnDate == 0) {
                filteredHires[hiresByGivenUserCount++] = hires[i];
            }
        }
    }

    return filteredHires;
}

struct Hire readHireFromFile(FILE *file) {
    struct Hire hire;
    fscanf(file, HIRE_FORMAT, &hire.id, &hire.carId, &hire.userId, &hire.hireDate, &hire.returnDate);
    return hire;
}

void writeHireToFile(FILE *file, struct Hire *hire) {
    fprintf(file, HIRE_FORMAT, hire->id, hire->carId, hire->userId, hire->hireDate, hire->returnDate);
}

/**
 * Prepares the hire header. Make sure to call this in your main function before anything else!
 */
void initHiresH() {
    reloadLastHiresId();
}

/**
 * Updates the last id file (and variable) with the given id
 */
void updateLastHiresId(int id) {
    lastHiresId = id;
    FILE *file = fopen(ID_STORE_HIRES, "w");
    fprintf(file, ID_FORMAT, id);
    fclose(file);
}

/**
 * Reloads the last id veriable from its file
 */
int reloadLastHiresId() {
    FILE *file = fopen(ID_STORE_HIRES, "r");

    if (file == NULL) {
        fopen(ID_STORE_HIRES, "w");
        return lastHiresId;
    }

    fscanf(file, ID_FORMAT, &lastHiresId);
    fclose(file);
    return lastHiresId;
}

/**
 * Adds a new hire to the database and returns its id
 */
int addHire(struct Hire *hire, int autoincrementId) {
    FILE *file = fopen(HIRES_STORE, "a");

    if (autoincrementId) hire->id = ++lastHiresId;
    writeHireToFile(file, hire);
    fclose(file);

    /* Make sure to store the now updated last id */
    updateLastHiresId(lastHiresId);

    return lastHiresId;
}

/**
 * Deletes a hire with a given id
 */
void removeHire(int id) {
    FILE *file = fopen(HIRES_STORE, "r");
    FILE *tempFile = fopen(HIRES_STORE_COPY, "w");

    /*
     * Loop through the first file copying any nonmatching cars (the ones that don't have the id we are removing) to a
     * temporary file
     */
    while (!feof(file)) {
        struct Hire hire = readHireFromFile(file);

        if (hire.id != id) {
            writeHireToFile(tempFile, &hire);
        }
    }

    /* Delete the original file and rename the copy as original. Then proceed to delete the now useless copy */
    fclose(file);
    int deleteResult = remove(HIRES_STORE);
    if (deleteResult == 0) {
        rename(HIRES_STORE_COPY, HIRES_STORE);
        remove(HIRES_STORE_COPY);
    } else {
        printf("\tCouldn't remove hire with id %d", id);
    }

    fclose(tempFile);
}

/**
 * Replaces a hire in the database with a given hire struct only retaining the ID. Basically, everything other than
 * the ID is replaced with the values of the hire parameter.
 */
struct Hire *updateHire(int id, struct Hire *hire) {
    removeHire(id);
    hire->id = id;
    addHire(hire, 0);
    return hire;
}

/**
 * Finds and returns a hire by its ID. Newly created one otherwise.
 */
struct Hire findHireById(int id) {
    struct Hire *hires = getAllHires();
    for (int i = 0; i < hiresCount; i++) {
        if (hires[i].id == id) return hires[i];
    }
    struct Hire empty;
    return empty;
}

/**
 * Registers a given car as hired by a given user
 */
void hireCar(struct Car *car, int userId) {
    /* Construct the hire struct */
    struct Hire hire;
    hire.carId = car->id;
    hire.userId = userId;
    hire.hireDate = time(0);
    hire.returnDate = 0l;
    addHire(&hire, 1);

    /* Mark this car as hired */
    car->hired = 1;
    updateCar(car->id, car);
}

/**
 * Unregisters a given car as hired by a given user
 */
void returnCar(int id) {
    /* Find the hire and set it's return date */
    struct Hire hire = findHireById(id);
    hire.returnDate = time(0);
    updateHire(hire.id, &hire);

    /* Set the car back as available */
    struct Car car = findCarById(hire.carId);
    car.hired = 0;
    updateCar(car.id, &car);
}

#endif //CAR_HIRING_SYSTEM_HIRE_H