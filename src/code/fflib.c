/*!
 *  \file
 *
 *  \author Maxim Moskalets
 *  \date October, 2022
 *
 *  \brief Library implementation for file-finder utility (ff)
 */

#include "fflib.h"
#include "fflib_helper.h"


/*!
 *  \brief Function to compare two file names (may be regular expressions it 1st param)
 *  \params[in] name_1, name_2 File names to compare
 *  \return Zero in equal case, non-zero in all other
 *  \warning All args must be valid poingers
 */
static int namecmp(const char *restrict name_1, const char *restrict name_2);

/*!
 *  \brief Function to add file name to pathes struct
 *  \param[out] dest Struct to add name
 *  \param[in] name File name that will be added
 *  \return Status code from enum FF_CODES
 */
static enum FF_CODES ffAddName(pathes_t *restrict dest, const char *restrict name);


/*(---------------------------------------------------------------------------*/
enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK((argc >= 2) && (argc <= 3), FF_MODE_INVALID);
    FF_CHECK(NULL != argv, FF_MODE_INVALID);


    FF_CHECK(strchr(argv[1], '/') == NULL, FF_MODE_INVALID);

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
ffFindFile(const char *name, const char *dir, enum FF_MODES mode, pathes_t *restrict dest)
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

        if (0 == namecmp(name, dent->d_name))
        {
            enum FF_CODES status = ffAddName(dest, dent->d_name);
            FF_CHECK(FF_SUCCESS == status, status);
        }
    }

    FF_CHECK(0 == closedir(searchDir), FF_DIRERROR);


    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
enum FF_CODES ffPathesFree(pathes_t *restrict pathes)
{
    FF_CHECK(NULL != pathes, FF_NULLPTR);
    FF_CHECK(((NULL == pathes->pathes) && (0 == pathes->size)) ||
            ((NULL != pathes->pathes) && (0 != pathes->size)), FF_NULLPTR);


    for (size_t i = 0; i < pathes->size; i++)
    {
        free(pathes->pathes[i]);
    }

    free(pathes->pathes);

    pathes->pathes = (void *) 13;
    pathes->size = SIZE_MAX;


    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
void ffperror(enum FF_CODES errcode)
{
    const char *restrict error = NULL;

    switch (errcode)
    {
        case FF_SUCCESS:
            error = "Success";
            break;
        case FF_NULLPTR:
            error = "NULL pointer error";
            break;
        case FF_INVALIDMODE:
            error = "Invalid mode value";
            break;
        case FF_DIRERROR:
            error = "Error with directory opening";
            break;
        case FF_MEMERROR:
            error = "Error in memory allocation";
            break;
        case FF_FILEERROR:
            error = "Error in file operations";
            break;

        default:
            error = "Unknowen error";
    }

    fprintf(stderr, "Code: %s\n", error);
    fprintf(stderr, "Errno: %s\n", strerror(errno));
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
static int namecmp(const char *restrict name_1, const char *restrict name_2)
{
#ifdef DEBUG_PRINT
    printf(">>> Compare name \"%s\" with name \"%s\"\n", name_1, name_2);
#endif

    size_t i = SIZE_MAX;
    size_t j = SIZE_MAX;
    for (i = 0, j = 0; (name_1[i] != '\0') && (name_2[j] != '\0'); i++, j++)
    {
        if ('?' == name_1[i])
        {
            continue;
        }

        else if ('*' == name_1[i])
        {
            for (size_t k = 1; name_2[k] != '\0'; k++)
            {
                if (0 == namecmp(name_1 + i + 1, name_2 + j + k))
                {
                    return 0;
                }
            }
        }

        else if (name_1[i] != name_2[j])
        {
            return -1;
        }
    }


    return name_1[i] != name_2[j];
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
static enum FF_CODES ffAddName(pathes_t *restrict dest, const char *restrict name)
{
    FF_CHECK(NULL != name, FF_NULLPTR);
    FF_CHECK(NULL != dest, FF_NULLPTR);

#ifdef DEBUG_PRINT
    printf(">>> Add name \"%s\"\n", name);
#endif

    char **newPathes = realloc(dest->pathes, (dest->size + 1) * sizeof *dest->pathes);
    FF_CHECK(NULL != newPathes, FF_MEMERROR);
    dest->pathes = newPathes;
    dest->size++;

    char *restrict newName = calloc(PATH_MAX + 1, sizeof *name);
    FF_CHECK(NULL != newName, FF_MEMERROR);
    dest->pathes[dest->size - 1] = strncpy(newName, name, PATH_MAX);


    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

/*(---------------------------------------------------------------------------*/
enum FF_CODES ffWritePathes(FILE *ostream, const pathes_t *restrict pathes)
{
    FF_CHECK(NULL != ostream, FF_NULLPTR);
    FF_CHECK(NULL != pathes, FF_NULLPTR);
    FF_CHECK(((NULL == pathes->pathes) && (0 == pathes->size)) ||
            ((NULL != pathes->pathes) && (0 != pathes->size)), FF_NULLPTR);

    for (size_t i = 0; i < pathes->size; i++)
    {
        FF_CHECK(0 < fprintf(ostream, "%s\n", pathes->pathes[i]), FF_FILEERROR);
    }
    
    return FF_SUCCESS;
}
/*)---------------------------------------------------------------------------*/

