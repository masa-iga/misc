#include <array>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>
#include <queue>
#include "../include/debug.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        m_m = mat.size();

        if (m_m == 0)
            return mat;

        m_n = mat.at(0).size();

        if (m_n == 0)
            return mat;

        std::queue<std::pair<int32_t, int32_t>> q = { };

        for (int32_t y = 0; y < m_m; ++y)
            for (int32_t x = 0 ; x < m_n; ++x)
                if (mat.at(y).at(x) == 0)
                    q.emplace(x, y);
                else
                    mat.at(y).at(x) = -1;

        constexpr std::array<std::pair<int32_t, int32_t>, 4> dir = {
            std::make_pair(-1, 0),
            std::make_pair(1, 0),
            std::make_pair(0, -1),
            std::make_pair(0, 1)};

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (const auto& d : dir)
            {
                const int32_t next_x = x + d.first;
                const int32_t next_y = y + d.second;

                const bool bOutOfRange = next_x < 0 || next_y < 0 || m_n <= next_x || m_m <= next_y;

                if (bOutOfRange || mat.at(next_y).at(next_x) != -1)
                    continue;
                
                mat.at(next_y).at(next_x) = mat.at(y).at(x) + 1;
                q.emplace(next_x, next_y);
            }
        }

        return mat;
    }

private:
    int32_t m_m = 0; // size of row
    int32_t m_n = 0; // size of column
};

int main(int argc, char *argv[])
{
    Solution solution;
    vector<vector<int32_t>> inp, out, exp;

    {
        inp = {{0}};
        out = solution.updateMatrix(inp);
        exp = {{0}};
        MY_ASSERT(out == exp);
    }

    {
        inp = {{0, 1}};
        out = solution.updateMatrix(inp);
        exp = {{0, 1}};
        MY_ASSERT(out == exp);

        inp = {{1, 0}};
        out = solution.updateMatrix(inp);
        exp = {{1, 0}};
        MY_ASSERT(out == exp);
    }

    {
        inp = {{0}, {1}};
        out = solution.updateMatrix(inp);
        exp = {{0}, {1}};
        MY_ASSERT(out == exp);

        inp = {{1}, {0}};
        out = solution.updateMatrix(inp);
        exp = {{1}, {0}};
        MY_ASSERT(out == exp);
    }

    {
        inp = {{0, 0}, {1, 0}};
        out = solution.updateMatrix(inp);
        exp = {{0, 0}, {1, 0}};
        MY_ASSERT(out == exp);

        inp = {{0, 0}, {1, 1}};
        out = solution.updateMatrix(inp);
        exp = {{0, 0}, {1, 1}};
        MY_ASSERT(out == exp);

        inp = {{0, 1}, {1, 1}};
        out = solution.updateMatrix(inp);
        exp = {{0, 1}, {1, 2}};
        MY_ASSERT(out == exp);
    }

    {
        inp = {{0,0,0}, {0,1,0}, {0,0,0}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,0}, {0,1,0}, {0,0,0}};
        MY_ASSERT(out == exp);

        inp = {{0,0,0}, {1,0,0}, {0,0,1}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,0}, {1,0,0}, {0,0,1}};
        MY_ASSERT(out == exp);

        inp = {{1,1,0}, {1,0,0}, {0,0,0}};
        out = solution.updateMatrix(inp);
        exp = {{2,1,0}, {1,0,0}, {0,0,0}};
        MY_ASSERT(out == exp);

        inp = {{0,0,0}, {0,1,0}, {1,1,1}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,0}, {0,1,0}, {1,2,1}};
        MY_ASSERT(out == exp);

        inp = {{0,0,1}, {0,1,0}, {1,1,1}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,1}, {0,1,0}, {1,2,1}};
        MY_ASSERT(out == exp);

        inp = {{0,0,1}, {0,1,1}, {1,1,1}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,1}, {0,1,2}, {1,2,3}};
        MY_ASSERT(out == exp);

        inp = {{0,0,1}, {1,1,1}, {1,1,1}};
        out = solution.updateMatrix(inp);
        exp = {{0,0,1}, {1,1,2}, {2,2,3}};
        MY_ASSERT(out == exp);

        inp = {{1,1,1}, {1,1,1}, {0,1,1}};
        out = solution.updateMatrix(inp);
        exp = {{2,3,4}, {1,2,3}, {0,1,2}};
        MY_ASSERT(out == exp);
    }


    return 0;
}
