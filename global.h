#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FAILURE 0
#define SUCCESS 1
#define STRING_MAX 20
#define USERINFO_DIR "./userinfo"
#define USERINFO_MODE "a+"
#define FILEINFO_DIR "./fileinfo"
#define FILEINFO_MODE "a+"

char current_user[] = "";