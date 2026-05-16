#include "../includes/workshop.h"
#include "../includes/db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int callback_workshop(void* data, int argc, char** argv, char** azColName) {
    Workshop* w = (Workshop*)data;
    if (argc >= 3) {
        w->number = atoi(argv[0]);
        strcpy(w->address, argv[1]);
        strcpy(w->car_brands, argv[2]);
    }
    return 0;
}

static int callback_list(void* data, int argc, char** argv, char** azColName) {
    printf("  %s | %s | %s\n", argv[0], argv[1], argv[2]);
    return 0;
}

int add_workshop(Workshop* w) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO workshops (number, address, car_brands) VALUES (%d, '%s', '%s')",
             w->number, w->address, w->car_brands);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

int get_workshop(int number, Workshop* w) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT number, address, car_brands FROM workshops WHERE number=%d", number);
    
    memset(w, 0, sizeof(Workshop));
    int rc = db_query(db, sql, callback_workshop, w);
    db_disconnect(db);
    return (rc == SQLITE_OK && w->number != 0);
}

int update_workshop(Workshop* w) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE workshops SET address='%s', car_brands='%s' WHERE number=%d",
             w->address, w->car_brands, w->number);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

int delete_workshop(int number) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM workshops WHERE number=%d", number);
    
    int rc = db_execute(db, sql);
    db_disconnect(db);
    return rc == SQLITE_OK;
}

void list_workshops(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Workshops ===\n");
    printf("  Number | Address | Car Brands\n");
    db_query(db, "SELECT number, address, car_brands FROM workshops ORDER BY number", callback_list, NULL);
    db_disconnect(db);
}

int workshop_exists(int number) {
    Workshop w;
    return get_workshop(number, &w);
}
