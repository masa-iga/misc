#include <cstdio>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cassert>
#include <algorithm>
#include <array>
#include <queue>

using namespace std;

void check(vector<vector<int32_t>>& ans, vector<vector<int32_t>>& exp);

#define ENABLE_DPRINTF (1)

#if ENABLE_DPRINTF
#define DPRINTF(...) do {\
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const size_t numOfRow = heights.size();
        assert(numOfRow > 0);
        const size_t numOfCol = heights.at(0).size();
        assert(numOfCol > 0);

        queue<pair<int32_t, int32_t>> q0, q1;
        {
            for (int32_t r = 0; r < numOfRow; ++r)
                for (int32_t c = 0; c < numOfCol; ++c)
                {
                    if (r == 0 || c == 0)
                        q0.push(make_pair(r,c));
                    
                    if (r == numOfRow - 1 || c == numOfCol - 1)
                        q1.push(make_pair(r, c));
                }
        }

        bool bVisitedArray0[numOfRow][numOfCol], bVisitedArray1[numOfRow][numOfCol];
        {
            for (auto &a : bVisitedArray0)
                for (auto &b : a)
                    b = false;

            for (auto &a : bVisitedArray1)
                for (auto &b : a)
                    b = false;
        }

        auto traverse = [](queue<pair<int32_t, int32_t>> &q, bool *bVisitedArray, const vector<vector<int>> &heights, int32_t numOfRow, int32_t numOfCol)
        {
            while (!q.empty())
            {
                const auto [r, c] = q.front();
                q.pop();

                bool& bVisitedFlag = *(bVisitedArray + r * numOfCol + c);

                if (bVisitedFlag)
                    continue;

                bVisitedFlag = true;

                constexpr array<pair<int32_t, int32_t>, 4> kDirects = {
                    make_pair(-1, 0),
                    make_pair(1, 0),
                    make_pair(0, -1),
                    make_pair(0, 1),
                };

                for (const pair<int32_t, int32_t> d : kDirects)
                {
                    const int32_t nr = r + d.first;
                    const int32_t nc = c + d.second;

                    auto isOutOfBound = [](int32_t r, int32_t c, int32_t maxr, int32_t maxc)
                    {
                        if (r < 0 || maxr <= r || c < 0 || maxc <= c)
                            return true;

                        return false;
                    };

                    if (isOutOfBound(nr, nc, numOfRow, numOfCol))
                        continue;

                    if (heights.at(r).at(c) > heights.at(nr).at(nc))
                        continue;

                    q.push(make_pair(nr, nc));
                }
            }
        };

        traverse(q0, bVisitedArray0[0], heights, numOfRow, numOfCol);
        traverse(q1, bVisitedArray1[0], heights, numOfRow, numOfCol);

        vector<vector<int32_t>> ans;

        for (int32_t r = 0; r < numOfRow; ++r)
            for (int32_t c = 0; c < numOfCol; ++c)
                if (bVisitedArray0[r][c] && bVisitedArray1[r][c])
                    ans.emplace_back(vector<int32_t>{r, c});

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<vector<int32_t>> heights;
    vector<vector<int32_t>> ans;
    vector<vector<int32_t>> exp;

#if 1
    {
        heights = {{1}};
        ans = solution.pacificAtlantic(heights);
        exp = { { 0, 0}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1},
            {1, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        check(ans, exp);
    }
#endif

#if 1
    {
        heights = {
            {1, 2},
            {2, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 1}, {1, 0}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 2},
            {2, 3},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 1}, {1, 0}, {1, 1}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1, 2},
            {1, 1, 1},
            {2, 1, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1, 1},
            {1, 1, 1},
            {2, 1, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1, 2},
            {1, 1, 1},
            {1, 1, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
        check(ans, exp);
    }

    {
        heights = {
            {1, 1, 1},
            {1, 1, 3},
            {1, 3, 1},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}};
        check(ans, exp);
    }

    {
        heights = {
            {2, 3, 4},
            {3, 1, 3},
            {4, 3, 2},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 2}, {2, 0}};
        check(ans, exp);
    }

    {
        heights = {
            {2, 4, 4},
            {3, 1, 3},
            {4, 3, 2},
        };
        ans = solution.pacificAtlantic(heights);
        exp = {{0, 1}, {0, 2}, {2, 0}};
        check(ans, exp);
    }

    {
        heights =
        {{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
        ans = solution.pacificAtlantic(heights);
    }
#endif

    return 0;
}

void check(vector<vector<int32_t>>& ans, vector<vector<int32_t>>& exp)
{
    std::sort(ans.begin(), ans.end());
    std::sort(exp.begin(), exp.end());
    assert(ans == exp);
}
