#include <cstdint>
#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        int32_t cache[m * n];
        memset(cache, 0xFF, sizeof(cache));
        return dp(m - 1, n - 1, cache, m);
    }

private:
    inline int32_t dp(int32_t m, int32_t n, int32_t cache[], size_t maxm)
    {
        if (m < 0 || n < 0)
            return 0;
        
        if (m == 0 && n == 0)
            return 1;
        
        const size_t idx = n * maxm + m;

        if (cache[idx] != -1)
            return cache[idx];

        cache[idx] = dp(m - 1, n, cache, maxm) + dp(m, n - 1, cache, maxm);
        return cache[idx];
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t m = 0, n = 0;
    int32_t exp = 0;

    {
        m = 3; n = 7; exp = 28;
        const int32_t ans = solution.uniquePaths(m, n); assert(ans == exp);
    }

    {
        m = 3; n = 2; exp = 3;
        const int32_t ans = solution.uniquePaths(m, n); assert(ans == exp);
    }

    {
        m = 23; n = 12; exp = 193536720;
        const int32_t ans = solution.uniquePaths(m, n); assert(ans == exp);
    }
    return 0;
}