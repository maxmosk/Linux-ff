#include <stdlib.h>
#include "fflib.h"


int main(int argc, char **argv)
{
    enum FF_MODES mode = ffGetMode(argc, (const char **) argv);

    return EXIT_SUCCESS;
}

