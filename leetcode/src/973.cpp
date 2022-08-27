#include <cstdint>
#include <cstdio>
#include <queue>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

#define ENABLE_DPRINTF (1)
#define ENABLE_DASSERT (1)

#if ENABLE_DPRINTF
#define DPRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF
#endif // #if ENABLE_DPRINTF

#if ENABLE_DASSERT
#define DASSERT(...) assert(__VA_ARGS__);
#else
#define DASSERT(...)
#endif // #if ENABLE_DASSERT

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        auto mypow = [](int32_t a, int32_t b)
        {
            int64_t a2 = a * a;
            int64_t b2 = b * b;
            return a2 + b2;
        };

        auto comp = [mypow](const vector<int32_t>& l, const vector<int32_t>& r)
        {
            DASSERT(l.size() == 2);
            DASSERT(r.size() == 2);
            return mypow(l.at(0), l.at(1)) < mypow(r.at(0), r.at(1));
        };

        priority_queue<vector<int32_t>, vector<vector<int32_t>>, decltype(comp)> pq(comp);
        {
            for (const vector<int32_t> &point : points)
            {
                DASSERT(point.size() == 2);

                if (pq.size() < k)
                {
                    pq.emplace(point);
                    continue;
                }

                const vector<int32_t> top = pq.top();

                if (mypow(top.at(0), top.at(1)) < mypow(point.at(0), point.at(1)))
                    continue;

                pq.pop();
                pq.emplace(point);
            }
        }

        vector<vector<int32_t>> ans;
        {
            for (int32_t i = 0; i < k; ++i)
            {
                ans.emplace_back(pq.top());
                pq.pop();
            }

            DASSERT(pq.empty());
        }

        return ans;      
    }
};

bool check(int32_t k, vector<vector<int32_t>> l, vector<vector<int32_t>> r)
{
    DASSERT(l.size() == k);
    DASSERT(r.size() == k);

    auto greater = [](const vector<int32_t>& lhs, const vector<int32_t>& rhs)
    {
        int64_t l = lhs.at(0) * lhs.at(0) + lhs.at(1) * lhs.at(1);
        int64_t r = rhs.at(0) * rhs.at(0) + rhs.at(1) * rhs.at(1);
        return l > r;
    };

    std::sort(l.begin(), l.end(), greater);
    std::sort(r.begin(), r.end(), greater);

    DASSERT(l == r);

    return true;
}

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t k = 0;
    vector<vector<int32_t>> points;
    vector<vector<int32_t>> ans;
    vector<vector<int32_t>> exp;

    {
        k = 1;
        points = {
            {0,0},
        };
        exp = {{0, 0}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));
    }

    {
        k = 1;
        points = {
            {-9999,-9999},
            {1, 1},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {1, 1},
            {9999,9999},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 2;
        points = {
            {1, 1},
            {2, 2},
        };
        exp = {{1, 1}, {2, 2}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));
    }

    {
        k = 1;
        points = {
            {1, 1},
            {1, 2},
            {1, 3},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {1, 2},
            {1, 3},
            {1, 1},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {1, 3},
            {1, 1},
            {1, 2},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {1, 1},
            {2, 1},
            {3, 1},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {2, 1},
            {3, 1},
            {1, 1},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 1;
        points = {
            {3, 1},
            {1, 1},
            {2, 1},
        };
        exp = {{1, 1}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 2;
        points = {
            {1, 1},
            {1, 2},
            {1, 3},
        };
        exp = {{1, 1}, {1, 2}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 3;
        points = {
            {1, 1},
            {1, 2},
            {1, 3},
        };
        exp = {{1, 1}, {1, 2}, {1, 3}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));
    }

    {
        k = 1;
        points = {
            {1,3},
            {-2, 2},
        };
        exp = {{-2, 2}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));

        k = 2;
        points = {
            {3, 3},
            {5, -1},
            {-2, -4},
        };
        exp = {{-2, -4}, {3, 3}};
        ans = solution.kClosest(points, k); assert(check(k, ans, exp));
    }

    return 0;
}