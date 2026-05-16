#ifndef AUTH_H
#define AUTH_H

typedef struct {
    int id;
    char login[50];
    char role[20];
    char full_name[100];
} User;

int auth_login(const char* login, const char* password, User* user);
void auth_logout(void);
User* get_current_user(void);

#endif
