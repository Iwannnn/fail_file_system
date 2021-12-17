#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct FOLDERNODE {
    const char *foldername;
} folder_node;

int main() {
    rmdir("./test/ttt");
    return 0;
}