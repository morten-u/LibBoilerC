#include "boilerc/bc_fileio.h"
#include <stdio.h>

int main() {

    if (bc_fileExist(".gitignore")) {
        printf("Found .gitignore file\n");
    } else {
        printf("Did not work\n");
    }

    return 0;
}
