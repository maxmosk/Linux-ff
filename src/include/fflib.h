#ifndef FFLIB_H_INCLUDED
#define FFLIB_H_INCLUDED


#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


enum FF_MODES
{
    FF_MODE_INVALID  = 0,
    FF_MODE_FILEONLY = 1,
    FF_MODE_FILEDIR  = 2
};


enum FF_MODES ffGetMode(int argc, const char **argv);


#endif

