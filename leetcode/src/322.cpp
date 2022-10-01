#include <cstdio>
#include <cstdint>
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
#define ASSERT(...) assert(__VA_ARGS__)
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Solution {
public:
    Solution() {
        m_cache.fill(kUncached);
    }

    int coinChange(vector<int>& coins, int amount) {
        int32_t ans = dp(coins, amount);

        if (ans == kNoCombination)
            ans = -1;

        return ans;
    }

private:
    int32_t dp(const vector<int32_t>& coins, int32_t target)
    {
        ASSERT(target >= 0);

        if (target == 0)
            return 0;

        if (m_cache.at(target) != kUncached)
            return m_cache.at(target);

        int32_t min = kNoCombination;

        for (int32_t coin : coins)
        {
            if (target - coin >= 0)
            {
                int32_t num = dp(coins, target - coin);

                if (num != kNoCombination)
                    ++num;

                min = std::min(min, num);
            }
        }

        m_cache.at(target) = min;

        return min;
    }

    static constexpr int32_t kNoCombination = INT32_MAX;
    static constexpr int32_t kUncached = INT32_MAX - 1;
    static constexpr size_t kMaxAmount = 10000 + 1;

    array<int32_t, kMaxAmount> m_cache;
};

int32_t main(int32_t argc, char* argv[])
{
    vector<int32_t> coins;
    int32_t amount = 0;
    int32_t exp = 0;

    {
        coins = {1, 2, 5};
        amount = 11;
        exp = 3;
        Solution solution; int32_t ans = solution.coinChange(coins, amount); ASSERT(ans == exp);
    }

    {
        coins = {2};
        amount = 3;
        exp = -1;
        Solution solution; int32_t ans = solution.coinChange(coins, amount); ASSERT(ans == exp);
    }

    {
        coins = {1};
        amount = 0;
        exp = 0;
        Solution solution; int32_t ans = solution.coinChange(coins, amount); ASSERT(ans == exp);
    }

    {
        coins = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        amount = 10000;
        exp = 1000;
        Solution solution; int32_t ans = solution.coinChange(coins, amount); ASSERT(ans == exp);
    }

    return 0;
}