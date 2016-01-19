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
char USER_FORMAT[] = "%d %s %s %s %s %d\n";

char ID_STORE_USERS[] = "ID_STORE_USERS.txt";
char USERS_STORE[] = "USERS_STORE.txt";
char USERS_STORE_COPY[] = "USERS_STORE_COPY.txt";

int lastUsersId = 0;

int usersCount;

int reloadLastUsersId();

struct User readUserFromFile(FILE *);
void writeUserToFile(FILE *file, struct User *user);

/**
 * Prepares the user header. Make sure to call this in your main function before anything else!
 */
void initUserH() {
    reloadLastUsersId();
}

/**
 * ...
 */
void updateLastUsersId(int id) {
    lastUsersId = id;
    FILE *file = fopen(ID_STORE_USERS, "w");
    fprintf(file, ID_FORMAT, id);
    fclose(file);
}

/**
 * ...
 */
int reloadLastUsersId() {
    FILE *file = fopen(ID_STORE_USERS, "r");

    if (file == NULL) {
        fopen(ID_STORE_USERS, "w");
        return lastUsersId;
    }

    fscanf(file, ID_FORMAT, &lastUsersId);
    fclose(file);
    return lastUsersId;
}

/**
 * ...
 */
void addUser(struct User *user, int autoincrementId) {
    FILE *file = fopen(USERS_STORE, "a");

    user->id = autoincrementId ? ++lastUsersId : user->id;
    writeUserToFile(file, user);
    fclose(file);

    /* Make sure to store the now update last id */
    updateLastUsersId(lastUsersId);
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
            writeUserToFile(tempFile, &user);
        }
    }

    /* Delete the original file and rename the copy as original. Then proceed to delete the now useless copy */
    fclose(file);
    int deleteResult = remove(USERS_STORE);
    if (deleteResult == 0) {
        rename(USERS_STORE_COPY, USERS_STORE);
        remove(USERS_STORE_COPY);
    } else {
        printf("\tCouldn't remove user with id %d", id);
    }

    fclose(tempFile);
}

/**
 * Replaces a user in the database with a given user struct only retaining the ID. Basically, everything other tha
 * the ID is replaced with the values of the user parameter.
 */
struct User * updateUser(int id, struct User *user) {
    removeUser(id);
    user->id = id;
    addUser(user, 0);
    return user;
}

/**
 *
 */
struct User *getAllUsers() {
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

/**
 * Finds and returns a user by its ID. Newly created one otherwise.
 */
struct User findUserById(int id) {
    struct User *users = getAllUsers();
    for (int i = 0; i < usersCount; i++) {
        if (users[i].id == id) return users[i];
    }
    struct User empty;
    return empty;
}

/**
 * Finds and returns a user by its username. Newly created one otherwise.
 */
struct User findUserByUsername(char username[]) {
    struct User *users = getAllUsers();
    for (int i = 0; i < usersCount; i++) {
        if (strcmp(users[i].username, username) == 0) return users[i];
    }
    struct User empty;
    return empty;
}

struct User readUserFromFile(FILE *file) {
    struct User user;
    fscanf(file, USER_FORMAT, &user.id, user.username, user.password, user.name, user.surname, &user.type);
    return user;
}

void writeUserToFile(FILE *file, struct User *user) {
    fprintf(file, USER_FORMAT, user->id, user->username, user->password, user->name, user->surname, user->type);
}

char *getTypeString(struct User *user) {
    char *type = malloc(10 * sizeof(char));
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
    return type;
}

#endif //CAR_HIRING_SYSTEM_USER_H
