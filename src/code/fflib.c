#include "fflib.h"
#include "fflib_helper.h"


/*(---------------------------------------------------------------------------*/
enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK((argc >= 2) && (argc <= 3), FF_MODE_INVALID);
    FF_CHECK(argv != NULL, FF_MODE_INVALID);


    enum FF_MODES mode = FF_MODE_INVALID;

    switch (argc)
    {
        case 2:
            if (NULL != argv[2-1])
            {
                mode = FF_MODE_FILEONLY;
            }
            break;

        case 3: 
            if ((NULL != argv[3-1]) && (NULL != argv[2-1]))
            {
                mode = FF_MODE_FILEDIR;
            }
            break;

        default:
            mode = FF_MODE_INVALID;
    }


    return mode;
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
enum FF_CODES
ffFindFile(const char *name, const char *dir, enum FF_MODES mode,
                                size_t *sizeDest, char ***pathDest)
{
    FF_CHECK(FF_MODE_INVALID != mode, FF_INVALIDMODE);

    FF_CHECK(NULL != name,     FF_NULLPTR);
    FF_CHECK(NULL != sizeDest, FF_NULLPTR);
    FF_CHECK(NULL != pathDest, FF_NULLPTR);

    char curDir[PATH_MAX + 1] = ".";
    if (FF_MODE_FILEDIR == mode)
    {
        FF_CHECK(NULL != dir, FF_NULLPTR);
        strncpy(curDir, dir, PATH_MAX);
    }

#ifdef DEBUG_PRINT
    printf(">>> Search file \"%s\" in directory \"%s\"\n", name, curDir);
#endif

    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

