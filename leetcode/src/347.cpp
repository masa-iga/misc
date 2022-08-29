#include <cstdint>
#include <cstdio>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define ASSERT(...) \
do { \
    assert(__VA_ARGS__); \
} while (false)

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int32_t, int32_t> hashMap;
        for (const int32_t n : nums)
        {
            if (hashMap.find(n) == hashMap.end())
            {
                hashMap.emplace(n, 1);
                continue;
            }

            hashMap.at(n) += 1;
        }

        struct Data {
            Data (int32_t num, int32_t freq) : m_num(num), m_freq(freq) { }
            int32_t m_num = 0;
            int32_t m_freq = 0;
        };

        auto comp = [](const Data& l, const Data& r)
        {
            return l.m_freq < r.m_freq;
        };

        priority_queue<Data, vector<Data>, decltype(comp)> hq(comp);

        for (const pair<int32_t, int32_t>& p : hashMap)
        {
            hq.emplace(Data(p.first, p.second));
        }

        vector<int32_t> freqElements(k);

        for (int32_t i = 0; i < k; ++i)
        {
            const int32_t e = hq.top().m_num;
            hq.pop();
            freqElements.at(i) = e;
        }

        return freqElements;
    }
};

void check(vector<int32_t> l, vector<int32_t> r)
{
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());
    ASSERT(l == r);
}

int32_t main(int32_t argc, char* argv[])
{
    printf("hello\n");

    Solution solution;
    vector<int32_t> nums;
    int32_t k = 0;
    vector<int32_t> ans;
    vector<int32_t> exp;

    {
        nums = {100};
        k = 1;
        exp = {100};
        ans = solution.topKFrequent(nums, k); check(ans, exp);
    }

    {
        nums = {1, 1, 10000};
        k = 1;
        exp = {1};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {1, 10000, 10000};
        k = 1;
        exp = {10000};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {-10000, -10000, 1};
        k = 1;
        exp = {-10000};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {-10000, 1, 1};
        k = 1;
        exp = {1};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {1, 2};
        k = 2;
        exp = {1, 2};
        ans = solution.topKFrequent(nums, k); check(ans, exp);
    }

    {
        nums = {1, 1, 2, 3};
        k = 1;
        exp = {1};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {1, 1, 2, 2, 3};
        k = 2;
        exp = {1, 2};
        ans = solution.topKFrequent(nums, k); check(ans, exp);

        nums = {1, 2, 3};
        k = 3;
        exp = {1, 2, 3};
        ans = solution.topKFrequent(nums, k); check(ans, exp);
    }

    {
        nums = {1, 1, 1, 2, 2, 3};
        k = 2;
        exp = {1, 2};
        ans = solution.topKFrequent(nums, k); check(ans, exp);
    }

    return 0;
}