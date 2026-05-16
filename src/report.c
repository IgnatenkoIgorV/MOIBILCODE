#include "../includes/report.h"
#include "../includes/db.h"
#include <stdio.h>

static int callback_simple(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("  %s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("  ---\n");
    return 0;
}

static int callback_table(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("  %s | ", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void report_workshop_repairs(int workshop_number) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT r.id, r.start_date, r.end_date, r.license_plate, r.repair_type, r.cost, r.master_name "
             "FROM repairs r WHERE r.workshop_number=%d", workshop_number);
    
    printf("\n=== Workshop %d Repairs ===\n", workshop_number);
    db_query(db, sql, callback_simple, NULL);
    db_disconnect(db);
}

void report_master_repairs(const char* master_name) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT * FROM repairs WHERE master_name='%s'", master_name);
    
    printf("\n=== Master %s Repairs ===\n", master_name);
    db_query(db, sql, callback_simple, NULL);
    db_disconnect(db);
}

void report_repairs_by_brand(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Repairs by Car Brand ===\n");
    db_query(db, 
             "SELECT c.brand, COUNT(r.id) as repairs_count, SUM(r.cost) as total_cost "
             "FROM repairs r JOIN cars c ON r.license_plate=c.license_plate "
             "GROUP BY c.brand ORDER BY repairs_count DESC", 
             callback_simple, NULL);
    db_disconnect(db);
}

void report_workshop_stats(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Workshop Statistics ===\n");
    db_query(db,
             "SELECT w.number, w.address, COUNT(r.id) as total_repairs, SUM(r.cost) as total_revenue "
             "FROM workshops w LEFT JOIN repairs r ON w.number=r.workshop_number "
             "GROUP BY w.number ORDER BY total_revenue DESC",
             callback_simple, NULL);
    db_disconnect(db);
}

void report_best_workshop(void) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    printf("\n=== Best Workshop (most repairs) ===\n");
    db_query(db,
             "SELECT w.number, w.address, COUNT(r.id) as total_repairs, SUM(r.cost) as total_revenue "
             "FROM workshops w LEFT JOIN repairs r ON w.number=r.workshop_number "
             "GROUP BY w.number ORDER BY total_repairs DESC LIMIT 1",
             callback_simple, NULL);
    db_disconnect(db);
}

double calculate_driver_earnings(const char* master_name, const char* start_date, const char* end_date) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT SUM(cost) as total FROM repairs WHERE master_name='%s' "
             "AND start_date >= '%s' AND end_date <= '%s'",
             master_name, start_date, end_date);
    
    double total = 0;
    db_query(db, sql, callback_simple, NULL);
    db_disconnect(db);
    return total * 0.2;
}

void calculate_all_earnings(const char* start_date, const char* end_date) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT master_name, SUM(cost) as total, SUM(cost)*0.2 as earnings "
             "FROM repairs WHERE start_date >= '%s' AND end_date <= '%s' "
             "GROUP BY master_name",
             start_date, end_date);
    
    printf("\n=== Driver Earnings (%s to %s) ===\n", start_date, end_date);
    db_query(db, sql, callback_simple, NULL);
    db_disconnect(db);
}
