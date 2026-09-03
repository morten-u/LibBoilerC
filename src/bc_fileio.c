#include "boilerc/bc_fileio.h"

// Headers

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if defined (_WIN32)
#include <windows.h>
#include <io.h>
#include <handleapi.h>

#elif defined(__linux__)
#include <unistd.h>
#include <dirent.h>

#endif


// Implementation


// Already cross platform

// Files
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

bool bc_fileSize(const char *filename, size_t *size) {
    *size = 0;

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error fseek end of file");
        fclose(file);
        return false;
    }

    long file_size = ftell(file);
    if (file_size == -1) {
        perror("Error ftell file size");
        fclose(file);
        return false;
    }
    *size = (size_t)file_size;

    return true;
}

bool bc_fileDelete(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting file");
        return false;
    }
    return true;
}

#if defined (_WIN32) // WINDOWS

bool bc_fileExist(const char *filename) {
    return (_access(filename, 0) == 0);
}


#elif defined (__linux__) // LINUX
bool bc_fileExist(const char *filename) {
    return (access(filename, F_OK) == 0);
}
#endif


// Directories

bool bc_dirExist(const char *dirname) {
    struct stat stats;

    if (stat(dirname, &stats) == 0) {
        return S_ISDIR(stats.st_mode);
    }

    return false;
}


#if defined (_WIN32)

bool bc_dirEmpty(const char *dirname) {
    char search_path[MAX_PATH];

    snprintf(search_path, sizeof(search_path), "%s\\*", dirname);

    WIN32_FIND_DATAA find_data;
    HANDLE handle = FindFirstFileA(search_path, &find_data);

    if (handle == INVALID_HANDLE_VALUE) return false;

    do
    {

        if (strcmp(find_data.cFileName, ".") != 0 &&
            strcmp(find_data.cFileName, "..") != 0) {
                FindClose(handle);
                return false;
        }

    } while(FindNextFileA(handle, &find_data));

    return true;
}

#elif defined(__linux__)

    bool bc_dirEmpty(const char *dirname) {
        struct dirent *entry;
        DIR *dir = opendir(dirname);

        if (!dir) {
            return false;
        }

        while ((entry = readdir(dir)) != nullptr) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                closedir(dir);
                return false;
            }
        }

        closedir(dir);
        return true;
    }

#endif
