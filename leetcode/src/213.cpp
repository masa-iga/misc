#include <cstdint>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        assert(nums.size() != 0);

        if (nums.size() == 1)
            return nums[0];
        
        if (nums.size() == 2)
            return std::max(nums[0], nums[1]);

        int32_t max = 0;
        int32_t cache[nums.size()];
        std::memset(cache, 0xFF, sizeof(cache));

        for (int32_t i = 0; i < nums.size(); ++i)
        {
            int32_t temp = 0;

            if (i == nums.size() - 1)
            {
                temp = nums.at(0);
                nums.at(0) = 0;
                std::memset(cache, 0xFF, sizeof(cache));
            }

            max = std::max(max, dp(cache, nums, i));

            if (i == nums.size() - 1)
            {
                nums.at(0) = temp;
            }
        }

        return max;
    }

private:
    int32_t dp(int32_t cache[], const vector<int32_t>& nums, int32_t n)
    {
        assert(n >= 0);

        if (n == 0)
            return nums.at(0);
        
        if (n == 1)
            return std::max(nums.at(0), nums.at(1));
        
        if (cache[n] != -1)
            return cache[n];

        int32_t max = 0;

        for (int32_t i = 0; i < n - 1; ++i)
        {
            max = std::max(max, dp(cache, nums, i));
        }

        cache[n] = max + nums.at(n);
        return cache[n];
    }
};

int32_t main(int32_t argc, char* argv[])
{
    vector<int32_t> nums;
    int32_t exp = 0;

    Solution solution;
    {
        nums = {1, 2, 3, 1};
        exp = 4;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {2, 3, 2};
        exp = 3;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {1, 2, 3};
        exp = 3;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {1, 2, 3, 4, 5};
        exp = 8;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {5, 4, 3, 2, 1};
        exp = 8;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {2, 2, 2, 2, 2};
        exp = 4;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {10, 1, 1, 1, 1};
        exp = 11;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {1, 10, 1, 1, 1};
        exp = 11;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    {
        nums = {94, 40, 49, 65, 21, 21, 106, 80, 92, 81, 679, 4, 61, 6, 237, 12, 72, 74, 29, 95, 265, 35, 47, 1, 61, 397, 52, 72, 37, 51, 1, 81, 45, 435, 7, 36, 57, 86, 81, 72};
        exp = 2926;
        const int32_t ans = solution.rob(nums); assert(ans == exp);
    }

    return 0;
}