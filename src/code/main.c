/*!
 *  \mainpage
 *
 *  \author Maxim Moskalets
 *  \date October, 2022
 *
 *  \brief FF - File finder utility
 *  \details Utility for Linux operating systems to find file in some directory
 *
 *  - \subpage Building
 *  To build in release mode use command "make" in Linux shell from project root
 *
 *  - \subpage Usage
 *  Run utility by command "ff filename [dirname]" to find file "filename" (optionaly)
 *  in directory "dirname"
 */

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
    FF_CHECK_CODE(status, EXIT_FAILURE);

    status = ffPathesFree(&foundPathes);
    FF_CHECK_CODE(status, EXIT_FAILURE);


    return EXIT_SUCCESS;
}

