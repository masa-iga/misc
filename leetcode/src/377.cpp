#include <cstdio>
#include <cstdint>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int32_t cache[target + 1];
        memset(cache, 0xFF, sizeof(cache)); // expressed "-1" as integer

        dp(cache, nums, target);

        return cache[target];
    }

private:
    int32_t dp(int32_t cache[], const vector<int32_t>& nums, int32_t target)
    {
        if (target < 0)
            return 0;

        if (target == 0)
            return 1;
        
        if (cache[target] != -1)
            return cache[target];

        int32_t n = 0;

        for (int32_t num : nums)
        {
            n += dp(cache, nums, target - num);
        }

        cache[target] = n;

        return cache[target];
    }
};

int32_t main(int32_t argc, char* argv[])
{
    printf("hello\n");

    Solution solution;
    vector<int32_t> nums;
    int32_t target = 0;
    int32_t exp = 0;

    {
        nums = {1, 2, 3};
        target = 4;
        exp = 7;
        int32_t ans = solution.combinationSum4(nums, target); assert(ans == ans);
    }

    {
        nums = {9};
        target = 3;
        exp = 0;
        int32_t ans = solution.combinationSum4(nums, target); assert(ans == ans);
    }

    return 0;
}