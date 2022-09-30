#include <cstdio>
#include <cstdint>
#include <cassert>
#include <array>

using namespace std;

#define ENABLE_DPRINTF (1)
#define ENABLE_ASSERT (1)

#if ENABLE_DPRINTF
#define DPRINTF(...) do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

#if ENABLE_ASSERT
#define ASSERT(...) assert(__VA_ARGS__);
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Solution {
public:
    int climbStairs(int n) {
        return dp(n);
    }

    Solution()
    {
        m_cache.fill(kInvalid);
    }

private:
    int32_t dp(int32_t n)
    {
        if (m_cache.at(n) != kInvalid)
            return m_cache.at(n);

        if (n <= 0)
            return 0;
        
        if (n == 1)
            return 1;
        
        if (n == 2)
            return 2;

        const int32_t n1 = dp(n - 2);
        const int32_t n0 = dp(n - 1);

        m_cache.at(n) = n1 + n0;
        return m_cache.at(n);
    }

    static constexpr int32_t kMax = 46;
    static constexpr int32_t kInvalid = -1;

    array<int32_t, kMax> m_cache;
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    ASSERT(solution.climbStairs(1) == 1);
    ASSERT(solution.climbStairs(2) == 2);
    ASSERT(solution.climbStairs(3) == 3);
    ASSERT(solution.climbStairs(4) == 5);

    return 0;
}