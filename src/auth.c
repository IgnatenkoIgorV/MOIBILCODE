#include "../includes/auth.h"
#include "../includes/db.h"
#include <stdio.h>
#include <string.h>

static User current_user = {0};

static int callback_auth(void* data, int argc, char** argv, char** azColName) {
    User* user = (User*)data;
    if (argc >= 4) {
        user->id = atoi(argv[0]);
        strcpy(user->login, argv[1]);
        strcpy(user->role, argv[2]);
        strcpy(user->full_name, argv[3]);
    }
    return 0;
}

int auth_login(const char* login, const char* password, User* user) {
    sqlite3* db = db_connect("automasters.db");
    if (!db) return 0;
    
    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT id, login, role, full_name FROM users WHERE login='%s' AND password='%s'",
             login, password);
    
    memset(user, 0, sizeof(User));
    int rc = db_query(db, sql, callback_auth, user);
    db_disconnect(db);
    
    if (rc == SQLITE_OK && user->id != 0) {
        current_user = *user;
        return 1;
    }
    return 0;
}

void auth_logout(void) {
    memset(&current_user, 0, sizeof(User));
}

User* get_current_user(void) {
    return &current_user;
}
