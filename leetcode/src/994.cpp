#include <cstdio>
#include <cstdint>
#include <vector>
#include <queue>
#include <array>
#include "../include/debug.h"

using namespace std;

class Solution {
public:
    enum Cell {
        kEmpty,
        kFresh,
        kRotten,
    };

    int orangesRotting(vector<vector<int>>& grid) {
        const int32_t colNum = grid.size();
        assert(colNum > 0);
        const int32_t rowNum = grid.at(0).size();
        assert(rowNum > 0);

        queue<pair<int32_t, int32_t>> q;

        for (int32_t y = 0; y < colNum; ++y)
            for (int32_t x = 0; x < rowNum; ++x)
                if (grid.at(y).at(x) == Cell::kRotten)
                    q.emplace(make_pair(x, y));

        constexpr array<pair<int32_t, int32_t>, 4> dir = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};
        int32_t elapse = 0;
        queue<pair<int32_t, int32_t>> nq;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (const auto& d : dir)
            {
                const int32_t nx = x + d.first;
                const int32_t ny = y + d.second;

                const bool bOutOfRange = nx < 0 || ny < 0 || rowNum <= nx || colNum <= ny;

                if (bOutOfRange || grid.at(ny).at(nx) != kFresh)
                    continue;
                
                grid.at(ny).at(nx) = kRotten;
                nq.emplace(make_pair(nx, ny));
            }

            if (q.empty())
            {
                if (nq.empty())
                    break;

                queue<pair<int32_t, int32_t>> temp = std::move(q);
                q = std::move(nq);
                nq = std::move(temp);
                elapse++;
            }
        }

        for (int32_t y = 0; y < colNum; ++y)
            for (int32_t x = 0; x < rowNum; ++x)
                if (grid.at(y).at(x) == Cell::kFresh)
                    return -1;

        return elapse;
    }
};

// TODO: read discussion
int32_t main (int32_t argc, char* argv[])
{
    Solution solution;
    vector<vector<int32_t>> grid = { };
    int32_t ans = 0;

    struct Input
    {
        vector<vector<int32_t>> grid;
        int32_t exp = 0;
    };

    vector<Input> inputs;

    {
        inputs = {
            {{{0}}, 0},
            {{{1}}, -1},
            {{{2}}, 0},
            {{{0, 0}}, 0},
            {{{0, 1}}, -1},
            {{{0, 2}}, 0},
            {{{1, 0}}, -1},
            {{{1, 1}}, -1},
            {{{1, 2}}, 1},
            {{{2, 0}}, 0},
            {{{2, 1}}, 1},
            {{{2, 2}}, 0},
            {{{0}, {0}}, 0},
            {{{0}, {1}}, -1},
            {{{0}, {2}}, 0},
            {{{1}, {0}}, -1},
            {{{1}, {1}}, -1},
            {{{1}, {2}}, 1},
            {{{2}, {0}}, 0},
            {{{2}, {1}}, 1},
            {{{2}, {2}}, 0},
            {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0},
            {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, -1},
            {{{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}, 0},
            {{{2, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 4},
            {{{2, 1, 1}, {0, 0, 1}, {0, 0, 1}}, 4},
            {{{2, 0, 0}, {1, 0, 0}, {1, 1, 1}}, 4},
            {{{2, 1, 0}, {0, 1, 0}, {0, 1, 1}}, 4},
            {{{0, 0, 0}, {0, 2, 0}, {0, 0, 0}}, 0},
            {{{0, 0, 0}, {0, 2, 1}, {0, 0, 0}}, 1},
            {{{0, 0, 0}, {0, 2, 1}, {0, 0, 1}}, 2},
            {{{0, 0, 0}, {0, 2, 1}, {0, 0, 1}}, 2},
            {{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}, 4},
        };

        for (auto& inp : inputs )
        {
            ans = solution.orangesRotting(inp.grid);
            MY_ASSERT(ans == inp.exp);
        }
    }

    return 0;
}