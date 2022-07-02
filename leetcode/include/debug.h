#include <cassert>

#define MY_ASSERT(exp) \
{ \
    if (!(exp)) \
    { \
        printf("Line %d. Assertion failed.\n", __LINE__); \
        assert(false); \
    } \
}

#define MY_ASSERT2(ans, exp) \
{ \
    if (ans != exp) \
    { \
        printf("Line %d. Assertion failed. (ans %d, exp %d)\n", __LINE__, ans, exp); \
        assert(false); \
    } \
}
