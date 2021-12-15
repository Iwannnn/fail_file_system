#include "global.h"

typedef struct FILENODE {
    char filename[STRING_MAX];
    char username[STRING_MAX];
    // read write excute 4 2 1
    int owner_mode;
    int other_mode;
    struct FILENODE *next;
} file_node;

typedef struct FOLDERNODE {
    char foldername[STRING_MAX];
    file_node *file;
    struct FOLDERNODE *child;
    struct FOLDERNODE *sibling;
} folder_node;

folder_node *root;

void init_filesystem();

void save_filesystem();

folder_node *init_folder_tree(FILE *file_info, char *op);

file_node *init_file_link_node(FILE *file_info);

void LDR(FILE *file_info, folder_node *node);

void traverse_folder(FILE *file_info, file_node *file);

folder_node *create_folder_node(char foldername[]);

void delete_folder_node(folder_node *folder);

void list_folder_node(folder_node *folder);

file_node *create_file_node(char filename[], char username[], int user_mode, int other_mode);

void delete_file_node(file_node *file);

void read_file(folder_node *folder);

void write_file(folder_node *folder);

void excute_file(folder_node *folder);

void change_mod(folder_node *folder, int owner, int other);