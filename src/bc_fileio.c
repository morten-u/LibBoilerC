#include "boilerc/bc_fileio.h"

// Headers
#if defined (_WIN32)
    #include <io.h>
#elif defined(__LINUX__)
    #include <unistd.h>
#endif

// Implementation
#if defined (_WIN32) // WINDOWS

bool bc_fileExist(const char *filename) {
    return (_access(filename, 0) == 0);
}


#elif defined (__LINUX) // LINUX
bool bc_fileExist(const char *filename) {
    return (access(filename, F_OK) == 0);
}
#endif
