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
            // TODO
            break;
        case 2:
            // TODO
            break;
    }
    return result;
}

#endif //CAR_HIRING_SYSTEM_AUTH_H
