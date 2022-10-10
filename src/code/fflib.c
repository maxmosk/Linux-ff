#include "fflib.h"
#include "fflib_helper.h"


enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK(argc >= 2, FF_MODE_INVALID);
    FF_CHECK(argv != NULL, FF_MODE_INVALID);
}

