#include "boilerc/bc_fileio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    if (bc_fileExist(".gitignore")) {
        printf("Found .gitignore file\n");
    } else {
        printf("Did not work\n");
    }

    if (!bc_fileWrite("ignore/fileio.txt", "Hello, World!\n")) {
        printf("Failed to write to file\n");
        return 1;
    }

    if (!bc_fileAppend("ignore/fileio.txt", "More content\n")) {
        printf("Failed to append to file\n");
        return 1;
    }

    char *content = bc_fileRead("ignore/fileio.txt");
    if (!content) {
        printf("Failed to read file\n");
        return 1;
    }

    printf("Content: %s\n", content);
    free(content);

    if (!bc_fileDelete("ignore/fileio.txt")) {
        printf("Failed to delete file\n");
        return 1;
    }

    if (bc_dirExist("src")) {
        printf("Found source directory\n");
    }

    if (!bc_dirExist("no_dir_like_this")) {
        printf("bc_dirExist works\n");
    }

    if (bc_dirEmpty("ignore")) {
        printf("ignore directory is empty\n");
    }

    if (!bc_dirEmpty("src")) {
        printf("bc_dirEmpty works\n");
    }

    return 0;
}
