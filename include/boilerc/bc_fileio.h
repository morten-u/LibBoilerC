#pragma once

// Checks if 'filename' exists
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
