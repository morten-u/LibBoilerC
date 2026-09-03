#include "boilerc/bc_fileio.h"

// Headers

#include <stdio.h>

#if defined (_WIN32)
    #include <io.h>
#elif defined(__LINUX__)
    #include <unistd.h>
#endif


// Implementation


// Already cross platform

bool bc_fileWrite(const char *filename, const char *content) {

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}



#if defined (_WIN32) // WINDOWS

bool bc_fileExist(const char *filename) {
    return (_access(filename, 0) == 0);
}


#elif defined (__LINUX) // LINUX
bool bc_fileExist(const char *filename) {
    return (access(filename, F_OK) == 0);
}
#endif
