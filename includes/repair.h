#ifndef REPAIR_H
#define REPAIR_H

typedef struct {
    int id;
    int workshop_number;
    char start_date[11];
    char end_date[11];
    char license_plate[10];
    char repair_type[100];
    double cost;
    char master_name[100];
} Repair;

int add_repair(Repair* r);
int get_repair(int id, Repair* r);
int update_repair(Repair* r);
int delete_repair(int id);
void list_repairs(void);
int check_capacity(const char* plate, double cargo_mass);

#endif
