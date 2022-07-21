#include <cstdio>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cassert>
#include <algorithm>
#include <array>

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

enum class Flag : uint64_t
{
    kNone = 0,
    kPacific = 1 << 0,
    kAtlantic = 1 << 1,
};

struct State {
    bool m_bChecked = false;
    Flag m_flag = Flag::kNone;
};

Flag operator|(Flag lhs, Flag rhs)
{
    return static_cast<Flag>(static_cast<uint64_t>(lhs) | static_cast<uint64_t>(rhs));
}

Flag operator&(Flag lhs, Flag rhs)
{
    return static_cast<Flag>(static_cast<uint64_t>(lhs) & static_cast<uint64_t>(rhs));
}

Flag& operator|=(Flag& lhs, Flag rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

bool isMatch(Flag a, Flag b)
{
    return (a & b) == b;
}

class Solution {
public:
    bool canFlowToPacificOcean(int32_t x, int32_t y)
    {
        if (x == 0)
            return true;

        if (y == 0)
            return true;

        return false;
    }

    bool canFlowToAtlanticOcean(const vector<vector<int32_t>>& heights, int32_t x, int32_t y)
    {
        const uint32_t m = heights.size();
        assert(m > 0);
        const uint32_t n = heights.at(0).size();
        assert(n > 0);

        if (x == n - 1)
            return true;

        if (y == m - 1)
            return true;

        return false;
    }

    bool isOutOfBound(const vector<vector<int32_t>>& heights, int32_t x, int32_t y)
    {
        const uint32_t m = heights.size();
        assert(m > 0);
        const uint32_t n = heights.at(0).size();
        assert(n > 0);

        if (x < 0 || n <= x)
            return true;

        if (y < 0 || m <= y)
            return true;

        return false;
    }

    int32_t computeIndex(const vector<vector<int32_t>>& heights, int32_t x, int32_t y)
    {
        const uint32_t m = heights.size();
        assert(m > 0);
        const uint32_t n = heights.at(0).size();
        assert(n > 0);

        return (n * y) + x;
    }

    const array<pair<int32_t, int32_t>, 4> kDirects = {
        make_pair(-1, 0),
        make_pair(1, 0),
        make_pair(0, -1),
        make_pair(0, 1)};

    Flag dfs(vector<bool> bVisitedArray, const vector<vector<int32_t>>& heights, int32_t col, int32_t row)
    {
        // Let's try without cache

        if (bVisitedArray.at(computeIndex(heights, col, row)))
            return Flag::kNone;

        bVisitedArray.at(computeIndex(heights, col, row)) = true;

        if (isOutOfBound(heights, col, row))
            return Flag::kNone;
        
        Flag flag = Flag::kNone;

        if (canFlowToPacificOcean(col, row))
            flag |= Flag::kPacific;

        if (canFlowToAtlanticOcean(heights, col, row))
            flag |= Flag::kAtlantic;
        
        if (flag == (Flag::kPacific | Flag::kAtlantic))
            return flag;
        
        for (const auto& dir : kDirects)
        {
            const int32_t nx = col + dir.first;
            const int32_t ny = row + dir.second;

            if (isOutOfBound(heights, nx, ny))
                continue;

            const int32_t h = heights.at(row).at(col);
            const int32_t nh = heights.at(ny).at(nx);

            if (h >= nh)
            {
                flag |= dfs(bVisitedArray, heights, nx, ny);
            }
        }

        return flag;
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const uint32_t m = heights.size();
        assert(m > 0);
        const uint32_t n = heights.at(0).size();
        assert(n > 0);

        vector<bool> bVisitedArray;
        {
            bVisitedArray.resize(m * n);

            for (auto b : bVisitedArray)
                b = false;
        }

        vector<vector<int32_t>> ans;

        for (int32_t row = 0; row < m; ++row)
            for (int32_t col = 0; col < n; ++col)
            {
                const Flag f = dfs(bVisitedArray, heights, col, row);

                DPRINTF("(%d, %d) %d\n", col, row, (int32_t)f);

                if (f == (Flag::kPacific | Flag::kAtlantic))
                {
                    ans.push_back({row, col});
                }
            }

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<vector<int32_t>> heights;
    vector<vector<int32_t>> ans;
    vector<vector<int32_t>> exp;

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

    // m, n が逆になっている
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

    return 0;
}

void check(vector<vector<int32_t>>& ans, vector<vector<int32_t>>& exp)
{
    std::sort(ans.begin(), ans.end());
    std::sort(exp.begin(), exp.end());
    assert(ans == exp);
}
