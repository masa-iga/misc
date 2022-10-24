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
        int32_t sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % 2 != 0)
            return false;
        
        sum /= 2;

        vector<vector<int32_t>> cache(nums.size() + 1, vector<int32_t>(sum + 1, kInvalid));

        for (int32_t i = 1; i < nums.size(); ++i)
            cache.at(i).at(0) = true;
        
        for (int32_t j = 1; j < sum + 1; ++j)
            cache.at(0).at(j) = false;

        for (int32_t i = 1; i < nums.size() + 1; ++i)
        {
            for (int32_t j = 1; j < sum + 1; ++j)
            {
                cache.at(i).at(j) = cache.at(i - 1).at(j);

                if (j >= nums.at(i - 1))
                {
                    cache.at(i).at(j) |= cache.at(i - 1).at(j - nums.at(i - 1));
                }
            }
        }

        return cache.at(nums.size()).at(sum);
    }

private:
    static constexpr int32_t kInvalid = INT32_MIN;
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