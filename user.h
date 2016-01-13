#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <MacTypes.h>
#include "struct.h"

#ifndef CAR_HIRING_SYSTEM_USER_H
#define CAR_HIRING_SYSTEM_USER_H

int TYPE_DEV = 0;
int TYPE_ADMIN = 1;
int TYPE_CUSTOMER = 2;

char ID_FORMAT[] = "%d";
char USER_FORMAT[] = "%d %s %s %d\n";

char ID_STORE[] = "ID_STORE_USERS.txt";
char USERS_STORE[] = "USERS_STORE.txt";
char USERS_STORE_COPY[] = "USERS_STORE_COPY.txt";

int lastId;

int usersCount;

struct User readUserFromFile(FILE *);

/**
 * ...
 */
void updateLastId(int id) {
    lastId = id;
    FILE *file = fopen(ID_STORE, "w");
    fprintf(file, ID_FORMAT, id);
    fclose(file);
}

/**
 * ...
 */
int reloadLastId() {
    FILE *file = fopen(ID_STORE, "r");
    fscanf(file, ID_FORMAT, &lastId);
    fclose(file);
    return lastId;
}

/**
 * ...
 */
struct User addUser(char username[], char password[], int type) {
    FILE *users = fopen(USERS_STORE, "a");

    fprintf(users, USER_FORMAT, ++lastId, username, password, type);
    fclose(users);

    /* Make sure to store the now update last id */
    updateLastId(lastId);

    /* Return the added user for convenience reasons */
    struct User user;
    user.id = lastId;
    strcpy(user.username, username);
    strcpy(user.password, password);
    user.type = type;
    return user;
}

/**
 *
 */
void removeUser(int id) {
    FILE *file = fopen(USERS_STORE, "r+");
    FILE *tempFile = fopen(USERS_STORE_COPY, "w+");

    /*
     * Loop through the first file copying any nonmatching users (the ones that don't have the id we are removing) to a
     * temporary file
     */
    while (!feof(file)) {
        struct User user = readUserFromFile(file);

        if (user.id != id) {
            fprintf(tempFile, USER_FORMAT, user.id, user.username, user.password, user.type);
        }
    }

    /* Close the first file and then open it as 'w' in order to erase all of its contents */
    fclose(file);
    FILE *newFile = fopen(USERS_STORE, "w");

    /* Loop through the temporary file copying over all users */
    while (!feof(tempFile)) {
        struct User user = readUserFromFile(tempFile);
        fprintf(newFile, USER_FORMAT, user.id, user.username, user.password, user.type);
    }

    fclose(newFile);
    fclose(tempFile);
}

/**
 *
 */
struct User * getAllUsers() {
    FILE *file = fopen(USERS_STORE, "r");

    /* Return empty array if file doesn't even exist */
    if (file == NULL) {
        struct User *empty = malloc(0);
        return empty;
    }

    struct User container[10000];

    usersCount = 0;
    while (!feof(file)) {
        struct User user = readUserFromFile(file);
        container[usersCount++] = user;
    }
    fclose(file);

    struct User *users = malloc(usersCount * sizeof(struct User));

    for (int i = 0; i < usersCount; i++) {
        users[i] = container[i];
    }

    return users;
}

struct User readUserFromFile(FILE *file) {
    struct User user;
    fscanf(file, USER_FORMAT, &user.id, user.username, user.password, &user.type);
    return user;
}

#endif //CAR_HIRING_SYSTEM_USER_H
