#include <cstdio>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>

#define ENABLE_PRINTF (1)
#define ENABLE_ASSERT (1)

using namespace std;

#if ENABLE_PRINTF
    #define DPRINTF(...) \
    do { \
        printf(__VA_ARGS__); \
    } while (false)
#else
    #define DPRINTF (...)
#endif // #if ENABLE_PRINTF

#if ENABLE_ASSERT
    #define ASSERT(...) assert(__VA_ARGS__);
#else
    #define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        return compute(nums);
    }

private:
    int32_t compute(const vector<int32_t>& nums)
    {
        vector<int32_t> tails;

        for (const int32_t n : nums)
        {
            const int32_t idx = bs(n, tails);

            ASSERT(0 <= idx && idx <= tails.size());

            if (idx < tails.size())
                tails.at(idx) = n;
            else
                tails.emplace_back(n);
        }

        return tails.size();
    }

    int32_t bs(int32_t n, const vector<int32_t> vals)
    {
        int32_t left = 0;
        int32_t right = vals.size() - 1;

        while (left <= right)
        {
            const int32_t center = (left + right) / 2;

            if (n == vals.at(center))
            {
                return center;
            }
            else if (n < vals.at(center))
            {
                right = center - 1;
            }
            else
            {
                left = center + 1;
            }
        }

        return left;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    vector<int32_t> inp;
    int32_t ans = 0;
    int32_t exp = 0;

    {
        inp = {10, 9, 2, 5, 3, 7, 101, 18};
        exp = 4;
        Solution solution; ans = solution.lengthOfLIS(inp); ASSERT(ans == exp);
    }

    {
        inp = {7,7,7,7,7,7,7};
        exp = 1;
        Solution solution; ans = solution.lengthOfLIS(inp); ASSERT(ans == exp);
    }

    {
        inp = {1,2,3};
        exp = 3;
        Solution solution; ans = solution.lengthOfLIS(inp); ASSERT(ans == exp);
    }

    {
        inp = {7,6,5};
        exp = 1;
        Solution solution; ans = solution.lengthOfLIS(inp); ASSERT(ans == exp);
    }

    return 0;
}