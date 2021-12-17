#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct FOLDERNODE {
    const char *foldername;
} folder_node;

int main() {
    mkdir("/test", 0775);
    creat("./test/testtest", 0775);
    return 0;
}