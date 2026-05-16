#include "../includes/car.h"
#include "../includes/db.h"
#include <stdio.h>
#include <string.h>

static int callback_car(void* data, int argc, char** argv, char** azColName) {
    Car* c = (Car*)data;
    if (argc >= 6) {
        strcpy(c->license_plate, argv[0]);
        strcpy(c->brand, argv[1]);
        c->year = argv[2] ? atoi(argv[2]) : 0;
        strcpy(c->owner_name, argv[3]);
        strcpy(c->tech_passport, argv[4]);
        strcpy(c->owner_address, argv[5] ? argv[5] : "");
    }
    return 0;
}

static int callback_list(void* data, int argc, char** argv, char** azColName) {
    printf("  %s | %s | %d | %s\n", argv[0], argv[1], argv[2] ? atoi(argv[2]) : 0, argv[3]);
    return 0;
}

int add_car(Car* c) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO cars (license_plate, brand, year, owner_name, tech_passport, owner_address) "
             "VALUES ('%s', '%s', %d, '%s', '%s', '%s')",
             c->license_plate, c->brand, c->year, c->owner_name, c->tech_passport, c->owner_address);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

int get_car(const char* plate, Car* c) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT license_plate, brand, year, owner_name, tech_passport, owner_address FROM cars WHERE license_plate='%s'", plate);
    
    memset(c, 0, sizeof(Car));
    int rc = db_query(db, sql, callback_car, c);
    db_disconnect(db);
    return (rc == SQLITE_OK && strlen(c->license_plate) > 0);
}

int update_car(Car* c) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE cars SET brand='%s', year=%d, owner_name='%s', tech_passport='%s', owner_address='%s' "
             "WHERE license_plate='%s'",
             c->brand, c->year, c->owner_name, c->tech_passport, c->owner_address, c->license_plate);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

int delete_car(const char* plate) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM cars WHERE license_plate='%s'", plate);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

void list_cars(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Cars ===\n");
    printf("  Plate | Brand | Year | Owner\n");
    db_query(db, "SELECT license_plate, brand, year, owner_name FROM cars ORDER BY license_plate", callback_list, NULL);
    db_disconnect(db);
}

int car_exists(const char* plate) {
    Car c;
    return get_car(plate, &c);
}

char* get_car_brand(const char* plate) {
    static Car c;
    if (get_car(plate, &c)) {
        return c.brand;
    }
    return NULL;
}
