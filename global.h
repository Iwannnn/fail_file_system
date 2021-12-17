#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 ** 	int open(const char *pathname, int oflag, int perms);
 **		int creat (const char *pathname,mode_t mode);
 **		int mkdir (const char *__path, __mode_t __mode)
 **/
#define FAILURE 0
#define SUCCESS 1
#define STRING_MAX 20
#define USERINFO_DIR "./userinfo"
#define USERINFO_MODE "a+"
#define FILEINFO_DIR "./fileinfo"
#define FILEINFO_READ_MODE "a+"
#define FILEINFO_SAVE_MODE "w"
#define CREAT_MODE 0775

const char *FOLDER_ = "FOLDER";
const char *FILE_ = "FILE";
const char *EMPTY_ = "EMPTY";
const char *SLASH = "/";

char current_user[] = "";
char current_dir[100] = ".";