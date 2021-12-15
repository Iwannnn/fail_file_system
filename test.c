#include <stdio.h>

typedef struct FOLDERNODE {
    const char *foldername;
} folder_node;

int main() {
    folder_node folder = {"123"};
    printf("%s", folder.foldername);
    return 0;
}