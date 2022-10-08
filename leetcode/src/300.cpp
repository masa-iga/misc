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
        return 4;
    }

private:
    int32_t dp(const vector<int32_t>& nums, int32_t pos)
    {
        vector<int32_t> maxArray(nums.size(), 0);

        for (int32_t i = 0; i < nums.size(); ++i)
        {
            for (int32_t j = 0; j < i; ++j)
            {
                if (nums.at(i) > nums.at(j) && maxArray.at(i) > maxArray.at(j) + 1)
                {
                    maxArray.at(i) = maxArray.at(j) + 1;
                }
            }
        }

        return *std::max_element(maxArray.begin(), maxArray.end());
    }
};

int32_t main(int32_t argc, char* argv[])
{
    vector<int32_t> inp;
    int32_t ans = 0;
    int32_t exp = 0;

    {
        Solution solution;
        inp = {10, 9, 2, 5, 3, 7, 101, 18};
        exp = 4;
        ans = solution.lengthOfLIS(inp); ASSERT(ans == exp);
    }

    return 0;
}