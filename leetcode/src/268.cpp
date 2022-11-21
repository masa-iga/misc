#include <cstdint>
#include <cstdio>
#include <vector>
#include <cassert>
#include <numeric>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        const int32_t sum = std::accumulate(nums.begin(), nums.end(), 0);
        const int32_t sum0 = (1 + nums.size()) * nums.size() / 2;

        return sum0 - sum;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<int32_t> nums;
    int32_t ans = 0, exp = 0;
    {
        nums = {9, 6, 4, 2, 3, 5, 7, 0, 1};
        exp = 8;
        ans = solution.missingNumber(nums); assert(ans == exp);
    }

    return 0;
}