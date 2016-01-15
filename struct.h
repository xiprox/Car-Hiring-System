#ifndef CAR_HIRING_SYSTEM_STRUCT_H
#define CAR_HIRING_SYSTEM_STRUCT_H

struct User {
    int id;
    char username[20];
    char password[20];
    char name[20];
    char surname[20];
    int type; // One of TYPE_DEV, TYPE_ADMIN or TYPE_CUSTOMER (See user.h)
    int hiredCars[3];
};

struct Car {
    int id;
    int price;
    char model[20];
    char manufacturer[40];
    int kilometrage;
    int hired;
};

#endif //CAR_HIRING_SYSTEM_STRUCT_H
