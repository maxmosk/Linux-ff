#include <stdlib.h>
#include "fflib.h"


int main(int argc, char **argv)
{
    enum FF_MODES mode = ffGetMode(argc, (const char **) argv);
    if (mode == FF_MODE_INVALID)
    {
        printf("Invalid command line args. Please, read documentation.\n");
        return EXIT_FAILURE;
    }

    size_t nPathes = SIZE_MAX;
    char **pathes = NULL;
    ffFindFile(argv[1], argv[2], mode, &nPathes, &pathes);

    return EXIT_SUCCESS;
}

