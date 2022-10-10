#ifndef FFLIB_H_INCLUDED
#define FFLIB_H_INCLUDED


enum FF_MODES
{
    FF_INVALID  = 0,
    FF_FILEONLY = 1,
    FF_FILEDIR  = 2
};


enum FF_MODES ffGetMode(int argc, const char **argv);


#endif

