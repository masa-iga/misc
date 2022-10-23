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

        vector<vector<int32_t>> cache(nums.size(), vector<int32_t>(sum/2 + 1, kInvalid));

        return dp(nums, cache, nums.size() - 1, sum / 2);
    }

private:
    static constexpr int32_t kInvalid = INT32_MIN;

    bool dp(const vector<int32_t>& nums, vector<vector<int32_t>>& cache, int32_t i, int32_t j)
    {
        ASSERT(0 <= i && i < cache.size());
        ASSERT(j < static_cast<int32_t>(cache.at(0).size()));

        if (j < 0)
            return false;

        if (cache.at(i).at(j) != kInvalid)
            return cache.at(i).at(j);

        if (i == 0)
            return (nums.at(0) == j);

        if (nums.at(i) == j)
            return true;

        const bool ret = dp(nums, cache, i - 1, j) | dp(nums, cache, i - 1, j - nums.at(i));
        cache.at(i).at(j) = ret;

        return ret;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<int32_t> inp;
    bool exp = false;

#if 1
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
        exp = false;
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