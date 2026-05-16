#ifndef CAR_H
#define CAR_H

typedef struct {
    char license_plate[10];
    char brand[50];
    int year;
    char owner_name[100];
    char tech_passport[20];
    char owner_address[200];
} Car;

int add_car(Car* c);
int get_car(const char* plate, Car* c);
int update_car(Car* c);
int delete_car(const char* plate);
void list_cars(void);
int car_exists(const char* plate);
char* get_car_brand(const char* plate);

#endif
