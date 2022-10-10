#ifndef FFLIB_HELPER_H_INCLUDED
#define FFLIB_HELPER_H_INCLUDED


#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __func__
#endif

#ifndef NDEBUG
#define FF_ASSERT(cond, condstr)                                         \
do                                                                        \
{                                                                          \
    if (!cond)                                                              \
    {                                                                        \
        fprintf(stderr, "*** Failed: %s in file %s function %s line %d ***\n",\
                condstr, __FILE__, __PRETTY_FUNCTION__, __LINE__);             \
        abort();                                                                \
    }                                                                            \
}                                                                                 \
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


#endif /* FFLIB_HELPER_H_INCLUDED */
