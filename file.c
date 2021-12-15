#include "file.h"

void init_filesystem() {
    FILE *file_info = fopen(FILEINFO_DIR, FILEINFO_MODE);
    char op[20];
    fscanf(file_info, "%s", op);
    if (strcmp(op, "FOLDER") == 0) {
        root = init_folder_tree(file_info, op);
    }
    fclose(file_info);
}

folder_node *init_folder_tree(FILE *file_info, char *op) {
    folder_node *node = (folder_node *)malloc(sizeof(folder_node));
    char foldername[STRING_MAX];
    printf("%s ", op);
    fscanf(file_info, "%s", foldername);
    node = create_folder_node(foldername);
    printf("%s\n", node->foldername);
    fscanf(file_info, "%s", op);
    while (strcmp(op, "FILE") == 0) {
        printf("%s ", op);
        init_file_link(file_info, node);
        fscanf(file_info, "%s", op);
    }
    if (strcmp(op, "FOLDER") == 0) {
        node->child = init_folder_tree(file_info, op);
    } else {
        printf("%s\n", op);
    }
    fscanf(file_info, "%s", op);
    if (strcmp(op, "FOLDER") == 0) {
        node->sibling = init_folder_tree(file_info, op);
    } else {
        printf("%s\n", op);
    }
    return node;
}

void init_file_link(FILE *file_info, folder_node *folder) {
    char filename[STRING_MAX];
    char username[STRING_MAX];
    int owner_mode;
    int other_mode;
    fscanf(file_info, "%s %s %d %d", filename, username, &owner_mode, &other_mode);
    file_node *file = folder->file;
    while (file->next) {
        file = file->next;
    }
    file->next = create_file_node(filename, username, owner_mode, other_mode);
    return;
}

void save_filesystem() {
    FILE *file_info = fopen(FILEINFO_DIR, FILEINFO_MODE);
    LDR(file_info, root);
    fclose(file_info);
}

void LDR(FILE *file_info, folder_node *folder) {
    // fprintf(file_info, "FOLDER ");
    // fprintf(file_info, "%s\n", folder->foldername);
    printf("FOLDER %s\n", folder->foldername);
    if (folder->file) traverse_folder(file_info, folder->file);
    if (folder->child) {
        LDR(file_info, folder->child);
    } else {
        // fprintf(file_info, "EMPTY\n");
        printf("EMPTY\n");
    }
    if (folder->sibling) {
        LDR(file_info, folder->sibling);
    } else {
        // fprintf(file_info, "EMPTY\n");
        printf("EMPTY\n");
    }
}

void traverse_folder(FILE *file_info, file_node *file) {
    // fprintf(file_info, "FILE ");
    // fprintf(file_info, "%s %s %d %d\n", file->filename, file->username, file->owner_mode, file->other_mode);
    if (file->next) traverse_folder(file_info, file->next);
}

folder_node *create_folder_node(char foldername[]) {

    folder_node *folder = (folder_node *)malloc(sizeof(folder_node));
    strcpy(folder->foldername, foldername);
    folder->file = NULL;
    folder->child = NULL;
    folder->sibling = NULL;
    return folder;
}

void delete_folder_node(folder_node *folder) {
    free(folder);
}

void list_folder_node(folder_node *folder);

file_node *create_file_node(char filename[], char username[], int owner_mode, int other_mode) {
    file_node *file = (file_node *)malloc(sizeof(file_node));
    strcpy(file->filename, filename);
    strcpy(file->username, username);
    file->owner_mode = owner_mode;
    file->other_mode = other_mode;
    file->next = NULL;
    return file;
}

void delete_file_node(file_node *file) {
    free(file);
}

void read_file(folder_node *folder);

void write_file(folder_node *folder);

void excute_file(folder_node *folder);

void change_mod(folder_node *folder, int owner, int other);

// void test() {
//     FILE *file_info = fopen(FILEINFO_DIR, FILEINFO_MODE);
//     char s[20], c;
//     while (~fscanf(file_info, "%c", &c)) {
//         printf("%c\n", c);
//         if (c == '.') {
//             fscanf(file_info, "%s", s);
//             printf("%s", s);
//         }
//     }
//     fclose(file_info);
// }

int main() {
    init_filesystem();
    printf("-----------------------------\n");
    save_filesystem();
}