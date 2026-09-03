#include "boilerc/bc_fileio.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    assert(bc_fileWrite("test.txt", "Hello, World"));

    assert(bc_fileExist("test.txt"));
    assert(!bc_fileExist("no_such_file.txt"));

    assert(bc_fileAppend("test.txt", "!"));

    char *content = bc_fileRead("test.txt");
    assert(content != nullptr);

    assert(strcmp(content, "Hello, World!") == 0);

    free(content);
    printf("All fileio tests passed!\n");
    return 0;
}
