#pragma once

// Checks if 'filename' exists
#include <stddef.h>
bool bc_fileExist(const char *filename);

// Writes content to 'filename', creates file if it don't exist
// returns true on success, and false on failure
bool bc_fileWrite(const char *filename, const char *content);

// Appends content to 'filename', creates file if it don't exist
// returns true on success, and false on failure
bool bc_fileAppend(const char *filename, const char *content);

// Reads content from 'filename'
// returns allocated char* that needs to be freed
// returns nullptr on failure
char* bc_fileRead(const char *filename);

// Checks filesize of 'filename' and sets '*size'
// returns true on success, and false on failure
bool bc_fileSize(const char *filename, size_t *size);

// Deletes 'filename'
// returns true on success, and false on failure
bool bc_fileDelete(const char *filename);
