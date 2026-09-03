#include "boilerc/bc_fileio.h"
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


    return 0;
}
