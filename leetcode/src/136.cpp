#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int32_t> uset;
        int32_t ans = 0;

        for (const int32_t n : nums)
        {
            if (uset.count(n) == 0)
            {
                uset.emplace(n);
                ans += n;
                continue;
            }

            ans -= n;
        }

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<int32_t> nums;
    int32_t ans = 0;
    int32_t exp = 0;

    {
        nums = {4, 1, 2, 1, 2};
        exp = 4;
        ans = solution.singleNumber(nums); assert(ans == exp);
    }
    {
        nums = {2, 2, 1};
        exp = 1;
        ans = solution.singleNumber(nums); assert(ans == exp);
    }
    {
        nums = {1};
        exp = 1;
        ans = solution.singleNumber(nums); assert(ans == exp);
    }

    return 0;
}