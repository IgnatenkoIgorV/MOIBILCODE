#include "../includes/repair.h"
#include "../includes/db.h"
#include "../includes/car.h"
#include "../includes/workshop.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int callback_repair(void* data, int argc, char** argv, char** azColName) {
    Repair* r = (Repair*)data;
    if (argc >= 8) {
        r->id = atoi(argv[0]);
        r->workshop_number = atoi(argv[1]);
        strcpy(r->start_date, argv[2]);
        strcpy(r->end_date, argv[3]);
        strcpy(r->license_plate, argv[4]);
        strcpy(r->repair_type, argv[5]);
        r->cost = atof(argv[6]);
        strcpy(r->master_name, argv[7]);
    }
    return 0;
}

static int callback_list(void* data, int argc, char** argv, char** azColName) {
    printf("  %s | %s | %s | %s | %.2f\n", argv[0], argv[1], argv[2], argv[4], atof(argv[5]));
    return 0;
}

int check_capacity(const char* plate, double cargo_mass) {
    char* brand = get_car_brand(plate);
    if (!brand) return 0;
    return 1;
}

static void update_master_stats(const char* master_name, const char* repair_type) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO master_stats (master_id, repair_type, repairs_count) "
             "SELECT id, '%s', 1 FROM masters WHERE name='%s' "
             "ON CONFLICT(master_id, repair_type) DO UPDATE SET repairs_count = repairs_count + 1",
             repair_type, master_name);
    
    db_execute(db, sql);
    db_disconnect(db);
}

int add_repair(Repair* r) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    if (!workshop_exists(r->workshop_number)) {
        printf("Error: Workshop %d does not exist!\n", r->workshop_number);
        db_disconnect(db);
        return 0;
    }
    
    if (!car_exists(r->license_plate)) {
        printf("Error: Car %s does not exist!\n", r->license_plate);
        db_disconnect(db);
        return 0;
    }
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO repairs (workshop_number, start_date, end_date, license_plate, repair_type, cost, master_name) "
             "VALUES (%d, '%s', '%s', '%s', '%s', %.2f, '%s')",
             r->workshop_number, r->start_date, r->end_date, r->license_plate, r->repair_type, r->cost, r->master_name);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    
    if (rc == SQLITE_OK) {
        update_master_stats(r->master_name, r->repair_type);
    }
    
    return rc == SQLITE_OK;
}

int get_repair(int id, Repair* r) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM repairs WHERE id=%d", id);
    
    memset(r, 0, sizeof(Repair));
    int rc = db_query(db, sql, callback_repair, r);
    db_disconnect(db);
    return (rc == SQLITE_OK && r->id != 0);
}

int update_repair(Repair* r) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE repairs SET workshop_number=%d, start_date='%s', end_date='%s', "
             "license_plate='%s', repair_type='%s', cost=%.2f, master_name='%s' WHERE id=%d",
             r->workshop_number, r->start_date, r->end_date, r->license_plate,
             r->repair_type, r->cost, r->master_name, r->id);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

int delete_repair(int id) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM repairs WHERE id=%d", id);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

void list_repairs(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Repairs ===\n");
    printf("  ID | Workshop | Start | End | Type | Cost\n");
    db_query(db, "SELECT id, workshop_number, start_date, end_date, repair_type, cost FROM repairs ORDER BY id", callback_list, NULL);
    db_disconnect(db);
}
