#include <cstdio>
#include <cstdint>
#include <cassert>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        bool carry = false;
        int32_t num = 0;
        int32_t i = 1;

        while (a != 0 || b != 0 || carry != false)
        {
            const bool a0 = (a & 0x1);
            const bool b0 = (b & 0x1);
            const bool n = a0 ^ b0 ^ carry;

            if (n)
            {
                num |= i;
            }

            if ((a0 & b0) || ((a0 | b0) & carry))
            {
                carry = true;
            }
            else
            {
                carry = false;
            }

            // nagative number
            if (i == (1 << 31))
                break;

            i = i << 1;
            a = a >> 1;
            b = b >> 1;
        }

        return num;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t a = 0, b = 0;
    int32_t exp = 0;

    {
        a = 1; b = 1; exp = 2;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = 2; b = 7; exp = 9;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = 1; b = 2; exp = 3;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = 2; b = 3; exp = 5;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = 999; b = 998; exp = 1997;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = 1000; b = 1000; exp = 2000;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }

    {
        a = -1; b = -1; exp = -2;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = -1; b = -2; exp = -3;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    {
        a = -1000; b = -1000; exp = -2000;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }

    {
        a = 2; b = -1; exp = 1;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }

    {
        a = -2; b = 1; exp = -1;
        const int32_t ans = solution.getSum(a, b); assert(ans == exp);
    }
    return 0;
}