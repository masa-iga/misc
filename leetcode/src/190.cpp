#include <cstdio>
#include <cstdint>
#include <cassert>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;

        for (int32_t i = 0; i < 32; ++i)
        {
            const uint32_t a = (n >> (31 - i)) & 0x1ul;
            ans |= a << i;
        }

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    uint32_t n = 0;
    uint32_t ans = 0;
    uint32_t exp = 0;

    {
        n = 0b10101000000000000000000000000000;
        exp = 0b00000000000000000000000000010101;
        ans = solution.reverseBits(n); assert(ans == exp);
    }

    {
        n = 0b00000010100101000001111010011100;
        exp = 0b0011'1001'0111'1000'0010'1001'0100'0000;
        ans = solution.reverseBits(n); assert(ans == exp);
    }

    {
        n = 0b11111111111111111111111111111101;
        exp = 0b10111111111111111111111111111111;
        ans = solution.reverseBits(n); assert(ans == exp);
    }

    return 0;
}