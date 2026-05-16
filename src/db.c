#include "../includes/db.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3* db_connect(const char* filename) {
    sqlite3* db;
    int rc = sqlite3_open(filename, &db);
    if (rc) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

void db_disconnect(sqlite3* db) {
    if (db) {
        sqlite3_close(db);
    }
}

int db_execute(sqlite3* db, const char* sql) {
    char* errmsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}

int db_query(sqlite3* db, const char* sql, int (*callback)(void*, int, char**, char**), void* data) {
    char* errmsg = 0;
    int rc = sqlite3_exec(db, sql, callback, data, &errmsg);
    if (rc != SQLITE_OK) {
        printf("Query error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}
