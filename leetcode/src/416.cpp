#include <cstdio>
#include <cstdint>
#include <cassert>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

#define EN_PRINTF (1)
#define EN_ASSERT (1)

#if EN_PRINTF
#define PRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define PRINTF(...)
#endif // EN_PRINTF

#if EN_ASSERT
#define ASSERT(...) assert(__VA_ARGS__);
#else
#define ASSERT(...)
#endif // #if EN_ASSERT

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        const int32_t sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % 2 != 0)
            return false;

        std::sort(nums.begin(), nums.end(), std::greater<int32_t>()); // O(N * logN)

        return dp(nums, sum / 2, 0, 0);
    }

private:
    bool dp(vector<int32_t>& nums /* sorted in decending order */, int32_t target, int32_t sum, int32_t idx)
    {
        if (idx == nums.size())
            return false;

        ASSERT(sum < target);
        ASSERT(idx < nums.size());

        for (int32_t i = idx; i < nums.size(); ++i)
        {
            sum += nums.at(i);

            if (sum == target)
                return true;

            if (sum > target)
            {
                sum -= nums.at(i);
                continue;
            }

            if (dp(nums, target, sum, i + 1))
                return true;
            
            sum -= nums.at(i);
        }

        return false;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<int32_t> inp;
    bool exp = false;

#if 0
    {
        inp = {1, 5, 11, 5};
        exp = true;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }

    {
        inp = {1, 2, 3, 5};
        exp = false;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }

    {
        inp = {2, 2, 1, 1};
        exp = true;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }

    {
        inp = {2, 2, 3, 5};
        exp = true;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }

    {
        inp = {1, 2, 5};
        exp = false;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }
#endif

    {
        inp = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,99,97};
        exp = false;
        const bool ans = solution.canPartition(inp); ASSERT(ans == exp);
    }

    return 0;
}