#ifndef CAR_HIRING_SYSTEM_AUTH_H
#define CAR_HIRING_SYSTEM_AUTH_H

/**
 * ...
 */
int authenticate(struct User *user, int type) {
    int result = 0;
    switch (type) {
        case 0:
            result = !strcmp(user->username, "admin") && !strcmp(user->password, "admin"); // Such secure. Much wow.
            break;
        case 1:
        case 2: {
            struct User *users = getAllUsers();
            for (int i = 0; i < usersCount; i++) {
                result = strcmp(user->username, users[i].username) == 0 &&
                         strcmp(user->password, users[i].password) == 0 && user->type == users[i].type;
            }
        }
    }
    return result;
}

#endif //CAR_HIRING_SYSTEM_AUTH_H
