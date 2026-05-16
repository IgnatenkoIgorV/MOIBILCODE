#ifndef DB_H
#define DB_H

#include <sqlite3.h>

sqlite3* db_connect(const char* filename);
void db_disconnect(sqlite3* db);
int db_execute(sqlite3* db, const char* sql);
int db_query(sqlite3* db, const char* sql, int (*callback)(void*, int, char**, char**), void* data);

#endif
