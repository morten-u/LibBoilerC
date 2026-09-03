#include "boilerc/bc_fileio.h"
#include <stdio.h>

int main() {

    if (bc_fileExist(".gitignore")) {
        printf("Found .gitignore file\n");
    } else {
        printf("Did not work\n");
    }

    if (!bc_fileWrite("ignore/fileio.txt", "Hello, World!")) {
        printf("Failed to write to file\n");
    }

    return 0;
}
