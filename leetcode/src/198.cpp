#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include <array>

using namespace std;

#define ENABLE_PRINTF (1)
#define ENABLE_ASSERT (1)

#if ENABLE_PRINTF
#define PRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define PRINTF(...)
#endif // #if ENABLE_PRINTF

#if ENABLE_ASSERT
#define ASSERT(...) assert(__VA_ARGS__);
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Solution {
public:
    Solution()
    {
        m_cache.fill(kInvalid);
    }

    int rob(vector<int>& nums) {
        return dp(nums, nums.size() - 1);
    }

private:
    int32_t dp(const vector<int32_t>& nums, int32_t x)
    {
        ASSERT(x >= 0 && x < nums.size());

        if (m_cache[x] != kInvalid)
            return m_cache[x];

        if (x == 0)
            return nums[0];
        
        if (x == 1)
            return max(nums[0], nums[1]);
        
        const int32_t f0 = dp(nums, x - 2);
        const int32_t f1 = dp(nums, x - 1);

        m_cache[x] = max(f0 + nums[x], f1);

        return m_cache[x];
    }

    static constexpr size_t kNumMax = 100 + 1;
    static constexpr int32_t kInvalid = -1;

    array<int32_t, kNumMax> m_cache;
};

int32_t main(int32_t argc, char* argv[])
{
    vector<int32_t> nums;
    int32_t ans = 0;
    int32_t exp = 0;

    {
        nums = {1, 2, 3, 1};
        exp = 4;
        Solution solution; ans = solution.rob(nums); ASSERT(ans == exp);
    }

    {
        nums = {2, 7, 9, 3, 1};
        exp = 12;
        Solution solution; ans = solution.rob(nums); ASSERT(ans == exp);
    }

    {
        nums = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};
        exp = 145;
        Solution solution; ans = solution.rob(nums); ASSERT(ans == exp);
    }

    return 0;
}