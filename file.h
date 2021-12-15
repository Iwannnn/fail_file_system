#include "global.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct FILENODE {
    char filename[STRING_MAX];
    char username[STRING_MAX];
    // read write excute 4 2 1
    int owner_mode;
    int other_mode;
    struct FILENODE *next;
} file_node;

typedef struct FOLDERNODE {
    char pathname[STRING_MAX];
    struct FOLDERNODE *next_sibling_node;
    struct FOLDERNODE *first_child_node;
    file_node *file;
} folder_node;

folder_node *root;

int init_filesystem();

int save_filesystem();

int create_folder_node(folder_node *parent, char foldername[]);

int delete_folder_node(folder_node *folder);

int list_folder_node(folder_node *folder);

int create_file_node(folder_node *folder, char filename[]);

int delete_file_node(folder_node *folder, char filename[]);

int read_file(folder_node *folder);

int write_file(folder_node *folder);

int excute_file(folder_node *folder);

int change_mod(folder_node *folder, int owner, int other);