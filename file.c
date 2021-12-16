#include "file.h"

void init_filesystem() {
    FILE *file_info = fopen(FILEINFO_DIR, FILEINFO_READ_MODE);
    char op[20];
    fscanf(file_info, "%s", op);
    if (strcmp(op, FOLDER_) == 0) {
        root = init_folder_tree(file_info, op);
    }
    fclose(file_info);
}

folder_node *init_folder_tree(FILE *file_info, char *op) {
    folder_node *node = (folder_node *)malloc(sizeof(folder_node));
    char foldername[STRING_MAX];
    fscanf(file_info, "%s", foldername);
    // printf("FOLDER %s\n", foldername);
    node = create_folder_node(foldername);
    push_folder(foldername);
    fscanf(file_info, "%s", op);
    if (strcmp(op, FILE_) == 0) {
        file_node *file = NULL, *next = NULL;
        do {
            if (!file) {
                // printf("first\t");
                file = init_file_link_node(file_info);
                node->file = file;
            } else {
                // printf("next\t");
                next = init_file_link_node(file_info);
                file->next = next;
                file = file->next;
            }
            fscanf(file_info, "%s", op);
        } while (strcmp(op, FILE_) == 0);
    }
    if (strcmp(op, FOLDER_) == 0) {
        node->child = init_folder_tree(file_info, op);
    } else {
        // printf("EMPTY\n");
    }
    pop_folder();
    fscanf(file_info, "%s", op);
    if (strcmp(op, FOLDER_) == 0) {
        node->sibling = init_folder_tree(file_info, op);
    } else {
        // printf("EMPTY\n");
    }
    return node;
}

file_node *init_file_link_node(FILE *file_info) {
    file_node *node = (file_node *)malloc(sizeof(file_node));
    char filename[STRING_MAX];
    char username[STRING_MAX];
    int owner_mode;
    int other_mode;
    fscanf(file_info, "%s %s %d %d", filename, username, &owner_mode, &other_mode);
    // printf("FILE %s %s %d %d\n", filename, username, owner_mode, other_mode);
    node = create_file_node(filename, username, owner_mode, other_mode);
    return node;
}

void save_filesystem() {
    FILE *file_info = fopen(FILEINFO_DIR, FILEINFO_SAVE_MODE);
    LDR(file_info, root);
    fclose(file_info);
}

void LDR(FILE *file_info, folder_node *node) {
    fprintf(file_info, "FOLDER ");
    fprintf(file_info, "%s\n", node->foldername);
    // printf("FOLDER %s\n", node->foldername);
    if (node->file) traverse_folder(file_info, node->file);
    if (node->child) {
        LDR(file_info, node->child);
    } else {
        fprintf(file_info, "EMPTY\n");
        // printf("EMPTY\n");
    }
    if (node->sibling) {
        LDR(file_info, node->sibling);
    } else {
        fprintf(file_info, "EMPTY\n");
        // printf("EMPTY\n");
    }
    free(node);
}

void traverse_folder(FILE *file_info, file_node *node) {
    fprintf(file_info, "FILE ");
    fprintf(file_info, "%s %s %d %d\n", node->filename, node->username, node->owner_mode, node->other_mode);
    // printf("FILE %s %s %d %d\n", node->filename, node->username, node->owner_mode, node->other_mode);
    if (node->next) {
        traverse_folder(file_info, node->next);
    }
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

void push_folder(char foldername[]) {
    strcat(current_dir, SLASH);
    strcat(current_dir, foldername);
    printf("%s\n", current_dir);
}

void pop_folder() {
    char tmp[100] = "";
    int last_slash_index = 0;
    for (int i = strlen(current_dir) - 1; i >= 0; i--) {
        if (current_dir[i] == '/') {
            last_slash_index = i;
            break;
        }
    }
    for (int i = 0; i < last_slash_index; i++) {
        tmp[i] = current_dir[i];
    }
    strcpy(current_dir, tmp);
    printf("%s\n", current_dir);
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