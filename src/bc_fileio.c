#include "boilerc/bc_fileio.h"

// Headers

#include <stdio.h>
#include <stdlib.h>

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

bool bc_fileAppend(const char *filename, const char *content) {

    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    if (fputs(content, file) == EOF) {
        perror("Error writing file");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

char* bc_fileRead(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return nullptr;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error fseek end of file");
        fclose(file);
        return nullptr;
    }

    long file_size = ftell(file);
    if (file_size == -1) {
        perror("Error ftell file size");
        fclose(file);
        return nullptr;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error fseek back to start");
        fclose(file);
        return nullptr;
    }

    char *buf = malloc(file_size + 1);
    if (!buf) {
        perror("Failed to allocate memory for file");
        fclose(file);
        return nullptr;
    }

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read < (size_t)file_size) {
        if (ferror(file)) {
            perror("Error reading file");
            free(buf);
            fclose(file);
            return nullptr;
        }
    }

    buf[bytes_read] = '\0';
    fclose(file);

    return buf;
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
