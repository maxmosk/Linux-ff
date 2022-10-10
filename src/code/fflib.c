#include "fflib.h"


#ifndef NDEBUG
#define FF_ASSERT(cond, condstr)            \
do                                           \
{                                             \
    if (!cond)                                 \
    {                                           \
        fprintf(stderr, "Failed: %s\n", condstr);\
        abort();                                  \
    }                                              \
}                                                   \
while (false)
#else
#define FF_ASSERT(cond) do {} while (false)
#endif

#define FF_CHECK(cond, ret)      \
do                                \
{                                  \
    bool FF_CHECK_COND_ = (cond);   \
    FF_ASSERT(FF_CHECK_COND_, #cond);\
    if (!FF_CHECK_COND_)              \
    {                                  \
        return (ret);                   \
    }                                    \
}                                         \
while (false)


enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK(argc >= 2, FF_MODE_INVALID);
    FF_CHECK(argv != NULL, FF_MODE_INVALID);
}

