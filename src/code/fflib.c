#include "fflib.h"
#include "fflib_helper.h"


enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK((argc >= 2) && (argc <= 3), FF_MODE_INVALID);
    FF_CHECK(argv != NULL, FF_MODE_INVALID);


    enum FF_MODES mode = FF_MODE_INVALID;

    switch (argc)
    {
        case 3: /* !!! Through execution !!! */
            if (NULL != argv[3-1])
            {
                mode = FF_MODE_FILEDIR;
            }
        case 2:
            if (NULL != argv[2-1])
            {
                mode = FF_MODE_FILEONLY;
            }
            break;

        default:
            mode = FF_MODE_INVALID;
    }


    return mode;
}

