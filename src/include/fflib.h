/*!
 *  \file
 *
 *  \author Maxim Moskalets
 *  \date October, 2022
 *
 *  \brief Library for file-finder utility (ff)
 */

#ifndef FFLIB_H_INCLUDED
#define FFLIB_H_INCLUDED


#if defined(__linux__) || defined(linux) || defined(__linux)
#include <linux/limits.h>
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <Windef.h>
#else
/*!
 *  \brief Maximal path length in case of undefined OS
 */
#define MAX_PATH 255
#endif

#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


/*!
 *  \brief Macro for checking code of interface function
 *  \param code Code from enum FF_CODES
 *  \param ret Expression to be returned in error case
 */
#define FF_CHECK_CODE(code, ret)\
do                               \
{                                 \
    enum FF_CODES code_ = (code);  \
    if (FF_SUCCESS != code_)        \
    {                                \
        ffperror(code_);              \
        return (ret);                  \
    }                                   \
}                                        \
while (false)


/*!
 *  \brief Modes of utility
 *  \note Used for command line arguments
 */
enum FF_MODES
{
    FF_MODE_INVALID  = 0,   /*!< Invalid mode */
    FF_MODE_FILEONLY = 1,   /*!< Find file in current directory */
    FF_MODE_FILEDIR  = 2    /*!< Find file in specified directory */
};

/*!
 *  \brief Codes for main interfce functions
 */
enum FF_CODES
{
    FF_SUCCESS     = 0,     /*!< Successful function completion */
    FF_NULLPTR     = 1,     /*!< Passed NULL-pointer as parametr */
    FF_INVALIDMODE = 2,     /*!< Invalid mode passed as parametr */
    FF_DIRERROR    = 3,     /*!< Error in directory opening */
    FF_MEMERROR    = 4,     /*!< Error in memory management function */
    FF_FILEERROR   = 5      /*!< Error in file operations */
};


/*!
 *  \brief Type for founded pathes
 */
typedef struct
{
    size_t size;            /**< Number of founded pathes */
    char **restrict pathes; /**< Pointer to array with pointers to pathes */
} pathes_t;


/*!
 *  \brief Function to get mode by command line arguments
 *  \params[in] argc, argv Matching command line arguments
 *  \retnurn Mode code from emun FF_MODES
 *  \note See The C Programming Language standard
 */
enum FF_MODES ffGetMode(int argc, const char **argv);

/*!
 *  \brief Function to find files in directory
 *  \param[in] name String with name to find
 *  \param[in] dir Search directory name
 *  \param[in] mode Mode of search
 *  \param[out] dest Pathes structure for founded names
 *  \return Status code from enum FF_CODES
 *  \note Param dir may be NULL in some modes
 */
enum FF_CODES
ffFindFile(const char *name, const char *dir, enum FF_MODES mode, pathes_t *restrict dest);

/*!
 *  \brief Function to free resources used by pathes_t struct
 *  \param[out] pathes Struct to be freed
 *  \return Status code from enum FF_CODES
 */
enum FF_CODES ffPathesFree(pathes_t *restrict pathes);

/*!
 *  \brief Function to print value of interace function return code and errno
 *  \param[in] errcode Code from enum FF_CODES
 *  \note Writes to stderr
 */
void ffperror(enum FF_CODES errcode);

/*!
 *  \brief Function to write pathes fro, pathes_t struct
 *  \param[in] osteream Pointer to stream to write pathes
 *  \param[in] pathes Struct to be written
 *  \return Status code from enum FF_CODES
 */
enum FF_CODES ffWritePathes(FILE *ostream, const pathes_t *restrict pathes);


#endif /* FFLIB_H_INCLUDED */

