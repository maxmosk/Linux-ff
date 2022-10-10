#ifndef FFLIB_H_INCLUDED
#define FFLIB_H_INCLUDED


#include <dirent.h>

#if defined(__linux__) || defined(linux) || defined(__linux)
#include <linux/limits.h>
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <Windef.h>
#else
#define MAX_PATH 256
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


enum FF_MODES
{
    FF_MODE_INVALID  = 0,
    FF_MODE_FILEONLY = 1,
    FF_MODE_FILEDIR  = 2
};

enum FF_CODES
{
    FF_SUCCESS     = 0,
    FF_NULLPTR     = 1,
    FF_INVALIDMODE = 2,
    FF_DIRERROR    = 3
};

typedef struct
{
    size_t n;
    char **pathes
} pathes_t;


enum FF_MODES ffGetMode(int argc, const char **argv);

enum FF_CODES
ffFindFile(const char *name, const char *dir, enum FF_MODES mode, pathes_t *dest);


#endif /* FFLIB_H_INCLUDED */

