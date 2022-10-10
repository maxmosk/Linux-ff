#include "fflib.h"
#include "fflib_helper.h"


int namecmp(const void *name_1, const void *name_2);

enum FF_CODES ffAddName(pathes_t *dest, const char *name);


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
ffFindFile(const char *name, const char *dir, enum FF_MODES mode, pathes_t *dest)
{
    FF_CHECK(FF_MODE_INVALID != mode, FF_INVALIDMODE);

    FF_CHECK(NULL != name, FF_NULLPTR);
    FF_CHECK(NULL != dest, FF_NULLPTR);


    char curDir[PATH_MAX + 1] = ".";
    if (FF_MODE_FILEDIR == mode)
    {
        FF_CHECK(NULL != dir, FF_NULLPTR);
        strncpy(curDir, dir, PATH_MAX);
    }

#ifdef DEBUG_PRINT
    printf(">>> Search file \"%s\" in directory \"%s\"\n", name, curDir);
#endif


    DIR *searchDir = opendir(curDir);
    FF_CHECK(NULL != searchDir, FF_DIRERROR);

    struct dirent *dent = NULL;
    while ((dent = readdir(searchDir)) != NULL)
    {
#ifdef DEBUG_PRINT
        printf(">>> Found file \"%s\"\n", dent->d_name);
#endif

        if (0 == namecmp(dent->d_name, name))
        {
            FF_CHECK(ffAddName(dest, dent->d_name), FF_ADDERROR);
        }
    }

    FF_CHECK(0 == closedir(searchDir), FF_DIRERROR);


    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/


/*(---------------------------------------------------------------------------*/
int namecmp(const void *name_1, const void *name_2)
{
    return strncmp((const char *) name_1, (const char *) name_2, NAME_MAX);
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
enum FF_CODES ffAddName(pathes_t *dest, const char *name)
{
    FF_CHECK(NULL != name, FF_NULLPTR);
    FF_CHECK(NULL != dest, FF_NULLPTR);

    char **newPathes = realloc(dest->pathes, dest->size + 1);
    FF_CHECK(NULL != newPathes, FF_MEMERROR);
    dest->pathes = newPathes;
    dest->size++;

    char *newName = calloc(PATH_MAX + 1, sizeof *name);
    FF_CHECK(NULL != newName, FF_MEMERROR);
    dest->pathes[dest->size - 1] = strncpy(newName, name, PATH_MAX);

    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

