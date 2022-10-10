/*!
 *  \file
 *
 *  \author Maxim Moskalets
 *  \date October, 2022
 *
 *  \brief File with macros for debug and error processing in file-finder linrary
 */

#ifndef FFLIB_HELPER_H_INCLUDED
#define FFLIB_HELPER_H_INCLUDED


#ifndef __PRETTY_FUNCTION__
/*!
 *  \brief Function name in macro if other undefined
 */
#define __PRETTY_FUNCTION__ __func__
#endif

#ifndef NDEBUG
/*!
 *  \brief Assert analog with more informative output
 *  \param cond Condition to be asserted
 *  \param condstr String that will be printed in fail case
 *  \note All expressions will be calculated only once
 */
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
#define FF_ASSERT(cond, condstr) do {} while (false)
#endif

/*!
 *  \brief Checker for condition with return on fail
 *  \param cond Contition that must be true
 *  \param ret Value that will be returned
 *  \note All expressions will be calculated only once
 */
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
