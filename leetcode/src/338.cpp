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

        for (int32_t i = 0; i <= n; ++i)
        {
            ans.emplace_back(countBit(i));
        }

        return ans;
    }

private:
    int32_t countBit(int32_t n)
    {
        int32_t num = n;
        int32_t count = 0;

        while (num != 0)
        {
            if (num & 0x1)
                ++count;
            
            num = num >> 1;
        }

        DPRINTF("%d: %d\n", n, count);

        return count;
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