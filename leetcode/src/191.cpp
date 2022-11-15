#include <cstdio>
#include <cstdint>
#include <cassert>

using namespace std;

// TODO: もっと早い方法はあるか？
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int32_t hamming = 0;

        while (n != 0)
        {
            if (n & 0x1 == 0x1)
                ++hamming;

            n = n >> 1;
        }

        return hamming;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t n = 0;
    int32_t exp = 0;

    {
        n = 0b00000000000000000000000000001011;
        exp = 3;
        const int32_t ans = solution.hammingWeight(n); assert(ans == exp);
    }
    {
        n = 0b00000000000000000000000010000000;
        exp = 1;
        const int32_t ans = solution.hammingWeight(n); assert(ans == exp);
    }
    {
        n = 0b11111111111111111111111111111101;
        exp = 31;
        const int32_t ans = solution.hammingWeight(n); assert(ans == exp);
    }

    return 0;
}