#include <stdio.h>
#include <stdlib.h>

typedef struct FILENODE {
    char filename[20];
    char user[20];
    // read write excute 4 2 1
    int owner_mode;
    int other_mode;
    struct FILENODE *next;
} file_node;

typedef struct FOLDERNODE {
    char pathname[20];
    file_node *file;
} folder_node;

int init_fill_node();

int delete_file_node();

int init_folder_node();

int delete_folder_node();