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

    pathes_t foundPathes = {0};
    enum FF_CODES status = ffFindFile(argv[1], argv[2], mode, &foundPathes);

    status = ffPathesFree(&foundPathes);


    return EXIT_SUCCESS;
}

