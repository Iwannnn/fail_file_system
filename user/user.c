#include "user.h"
#define SUCCESS 1
#define FAILURE 0

int login(char *username, char *password) {
    if (!strcmp(username, "")) {
        printf("ALREADY LOGIN\n");
        return FAILURE;
    }
    if (find_user(username)) {
        if (check_password(username, password)) {
            current_user = username;
            printf("LOGIN SUCCESS\n");
            return SUCCESS;
        } else {
            printf("PASSWORD ERROR\n");
            return FAILURE;
        }
    } else {
        printf("NOT EXITS USER\n");
        return FAILURE;
    }
}

int reg(char *username, char *password) {
    if (!strcmp(username, "")) {
        printf("ALREADY LOGIN\n");
        return FAILURE;
    }
    if (!find_user(username)) {
        FILE *user_file = NULL;
        user_file = fopen(dir, mode);
        fprintf(user_file, "%s %s", username, password);
        fclose(user_file);
        printf("REGISTER SUCCESS\n");
        return SUCCESS;
    }
    printf("EXIST USER\n");
    return FAILURE;
}

int logout() {
    if (strcmp(current_user, "")) {
        current_user = "";
        return SUCCESS;
    }
    printf("NO USER LOGIN\n");
    return FAILURE;
}

int find_user(char *username) {
    char username_[255], password_[255];
    int t = 0, tt = 0;
    FILE *user_file = fopen(dir, mode);
    while (fscanf(user_file, "%s %s", username_, password_) != EOF) {
        if (strcmp(username_, username) == 0) {
            return SUCCESS;
        }
    }
    fclose(user_file);
    return FAILURE;
}

int check_password(char *username, char *password) {
    char username_[255], password_[255];
    FILE *user_file = NULL;
    user_file = fopen(dir, mode);
    while (fscanf(user_file, "%s %s", username_, password_) != EOF) {
        if (strcmp(username, username_) == 0) {
            if (strcmp(password, password_) == 0) {
                return SUCCESS;
            } else {
                return FAILURE;
            }
        }
    }
    fclose(user_file);
    return FAILURE;
}

int main(int argc, char **argv) {
    reg("root", "123456");
}