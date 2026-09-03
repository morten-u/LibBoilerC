#pragma once

// Checks if 'filename' exists
bool bc_fileExist(const char *filename);

// Writes content to 'filename', creates file if it don't exist
// returns true on success, and false on failure
bool bc_fileWrite(const char *filename, const char *content);
