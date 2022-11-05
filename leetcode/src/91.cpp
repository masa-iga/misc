#include <cstdio>
#include <cstdint>
#include <cassert>
#include <string>
#include <set>
#include <cstring>
#include <string_view>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int32_t cache[s.length()];
        memset(cache, 0xFF, sizeof(cache));
        return dp(cache, s, 0);
    }

private:
    inline bool isValidNumber(const string_view s, int32_t pos, int32_t len)
    {
        static const set<string_view> validStrs = {
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", 
            "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", 
            "21", "22", "23", "24", "25", "26",
        };

        string_view str = s.substr(pos, len);

        if (validStrs.find(str) != validStrs.end())
            return true;

        return false;
    }

    int32_t dp(int32_t cache[], const string& s, int32_t pos)
    {
        assert(pos <= s.length());

        if (pos == s.length())
            return 1;
        
        if (cache[pos] != -1)
            return cache[pos];
        
        int32_t n = 0;

        if (isValidNumber(s, pos, 1))
            n = dp(cache, s, pos + 1);

        if (pos == s.length() - 1)
            return n;
        
        if (isValidNumber(s, pos, 2))
            n += dp(cache, s, pos + 2);

        cache[pos] = n;
        return cache[pos];
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    string s = "";
    int32_t exp = 0;

    {
        s = "0";
        exp = 0;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "1";
        exp = 1;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "12";
        exp = 2;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "06";
        exp = 0;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "226";
        exp = 3;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "1111";
        exp = 5;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "1234";
        exp = 3;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }
    {
        s = "11106";
        exp = 2;
        const int32_t ans = solution.numDecodings(s); assert(ans == exp);
    }

    return 0;
}