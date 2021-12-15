#include "global.h"
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct USER {
    char *username;
    char *password;
} user;

// 登录
int login(char *username, char *password);
// 注册
int reg(char *username, char *password);
// 登出
int logout();
// 查找用户
int find_user(char *username);
// 判断密码
int check_password(char *username, char *password);