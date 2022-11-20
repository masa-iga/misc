#include <cstdint>
#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

#define ENABLE_DPRINTF (0)

#if ENABLE_DPRINTF
#define DPRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int32_t> ans;
        ans.reserve(n + 1);

        int32_t power = 0;

        for (int32_t i = 0; i < n + 1; ++i)
        {
            if (i < 2)
            {
                ans.emplace_back(i & 0x1);
                continue;
            }

            if (isPowerOfTwo(i))
                ++power;
            
            const int32_t idx = i & ~(1 << power);
            ans.emplace_back(ans[idx] + 1);
        }

        return ans;
    }

private:
    inline bool isPowerOfTwo(int32_t n)
    {
        return (n & n - 1) == 0;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t n = 0;
    vector<int32_t> exp;
    {
        n = 5;
        exp = {0, 1, 1, 2, 1, 2};
        const vector<int32_t> ans = solution.countBits(n); assert(ans == exp);
    }

    return 0;
}