#include "fflib.h"


#define FF_ASSERT(cond)\
do                      \
{                        \
    assert(cond);         \
}                          \
while (false)


#define FF_CHECK(cond, ret)   \
do                             \
{                               \
    bool FF_CHECK_COND_ = (cond);\
    if (!FF_CHECK_COND_)          \
    {                              \
        return (ret);               \
    }                                \
}                                     \
while (false)


enum FF_MODES ffGetMode(int argc, const char **argv)
{
    FF_CHECK(argc >= 2, FF_MODE_INVALID);
    FF_CHECK(argv != NULL, FF_MODE_INVALID);
}

