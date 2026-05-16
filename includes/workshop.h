#ifndef WORKSHOP_H
#define WORKSHOP_H

typedef struct {
    int number;
    char address[200];
    char car_brands[500];
} Workshop;

int add_workshop(Workshop* w);
int get_workshop(int number, Workshop* w);
int update_workshop(Workshop* w);
int delete_workshop(int number);
void list_workshops(void);
int workshop_exists(int number);

#endif
