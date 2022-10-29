#include <cstdio>
#include <cstdint>
#include <cassert>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#define ENABLE_PRINTF (1)
#define ENABLE_ASSERT (1)

#if ENABLE_PRINTF
#define PRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define PRINTF (...)
#endif // #if ENABLE_PRINTF

#if ENABLE_ASSERT
#define ASSERT(...) assert(__VA_ARGS__)
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int32_t lcs[text1.length() + 1][text2.length() + 1];
        memset(lcs, 0x0, sizeof(lcs));

        for (int32_t i = 0; i < text1.length(); ++i)
        {
            for (int32_t j = 0; j < text2.length(); ++j)
            {
                if (text1.at(i) == text2.at(j))
                    lcs[i + 1][j + 1] = lcs[i][j] + 1;
                else
                    lcs[i + 1][j + 1] = max(lcs[i + 1][j], lcs[i][j + 1]);
            }
        }

        return lcs[text1.length()][text2.length()];
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    string text1 = "";
    string text2 = "";
    int32_t exp = 0;

    {
        text1 = "abcde";
        text2 = "ace";
        exp = 3;
        int32_t ans = solution.longestCommonSubsequence(text1, text2); ASSERT(ans == exp);
    }

    {
        text1 = "abc";
        text2 = "abc";
        exp = 3;
        int32_t ans = solution.longestCommonSubsequence(text1, text2); ASSERT(ans == exp);
    }

    {
        text1 = "abc";
        text2 = "def";
        exp = 0;
        int32_t ans = solution.longestCommonSubsequence(text1, text2); ASSERT(ans == exp);
    }

    return 0;
}