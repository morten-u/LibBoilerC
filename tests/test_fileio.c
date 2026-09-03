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
    size_t size = 0;
    assert(bc_fileSize("test.txt", &size));

    char *content = bc_fileRead("test.txt");
    assert(content != nullptr);

    assert(strcmp(content, "Hello, World!") == 0);
    free(content);

    // This test fails in testing, but works in example
    // Error 'permission denied'
    // Do not think this is an error but maybe something with cmake under testing
    assert(bc_fileDelete("test.txt"));
    assert(!bc_fileExist("test.txt"));

    printf("All fileio tests passed!\n");
    return 0;
}
