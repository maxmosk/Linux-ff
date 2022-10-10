#ifndef FFLIB_H_INCLUDED
#define FFLIB_H_INCLUDED


#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
    FF_INVALIDMODE = 2
};


enum FF_MODES ffGetMode(int argc, const char **argv);

enum FF_CODES
ffFindFile(const char *name, const char *dir, enum FF_MODES mode,
                                size_t *sizeDest, char ***pathDest);


#endif /* FFLIB_H_INCLUDED */

