#include <cassert>
#include <cstdio>
#include <cstdint>
#include <chrono>
#include <vector>
#include <queue>
#include "../include/debug.h"

using namespace std;

class Solution {
public:
    size_t computeIndex(size_t x, size_t y)
    {
        return x + y * m_width;
    }

    size_t getWidth(const vector<vector<char>> &grid)
    {
        if (grid.size() == 0)
            return 0;

        return grid.at(0).size();
    }

    size_t getHeight(const vector<vector<char>> &grid)
    {
        return grid.size();
    }

    bool recursiveCheckIsland(size_t x, size_t y, const vector<vector<char>> &grid, vector<bool> &bVisitedArray)
    {
        if (getWidth(grid) == 0 || getHeight(grid) == 0)
            return false;

        // boundary check
        if (x >= getWidth(grid) || y >= getHeight(grid))
            return false;

        if (bVisitedArray.at(computeIndex(x, y)))
            return false; // this is already visited. This means you already counted the island

        bVisitedArray.at(computeIndex(x, y)) = true;

        if (grid.at(y).at(x) == '0')
            return false;

        recursiveCheckIsland(x - 1, y, grid, bVisitedArray);
        recursiveCheckIsland(x + 1, y, grid, bVisitedArray);
        recursiveCheckIsland(x, y - 1, grid, bVisitedArray);
        recursiveCheckIsland(x, y + 1, grid, bVisitedArray);

        return true;
    }

    int solveDfs(vector<vector<char>>& grid)
    {
        if (getWidth(grid) == 0 || getHeight(grid) == 0)
            return 0;

        m_width = getWidth(grid);
        m_height = getHeight(grid);

        vector<bool> bVisitedArray(m_width * m_height, 0);

        int32_t numOfIdlands = 0;

        for (size_t y = 0; y < m_height; ++y)
        {
            for (size_t x = 0; x < m_width; ++x)
            {
                if (bVisitedArray.at(computeIndex(x, y)))
                    continue;
                
                if (recursiveCheckIsland(x, y, grid, bVisitedArray))
                    ++numOfIdlands;
            }
        }

        return numOfIdlands;
    }

    int solveBfs(vector<vector<char>>& grid)
    {
        if (getWidth(grid) == 0 || getHeight(grid) == 0)
            return 0;

        m_width = getWidth(grid);
        m_height = getHeight(grid);

        vector<bool> bVisitedArray(m_width * m_height, 0);
        queue<pair<size_t, size_t>> q;
        int32_t numOfIdlands = 0;

        for (size_t y = 0; y < m_height; ++y)
        {
            for (size_t x = 0; x < m_width; ++x)
            {
                if (bVisitedArray.at(computeIndex(x, y)))
                    continue;

                bVisitedArray.at(computeIndex(x, y)) = true;

                if (grid.at(y).at(x) == '0')
                    continue;

                q.push(make_pair(x - 1, y));
                q.push(make_pair(x + 1, y));
                q.push(make_pair(x, y - 1));
                q.push(make_pair(x, y + 1));

                while (!q.empty())
                {
                    const auto [posx, posy] = q.front();
                    q.pop();

                    const bool outOfRange = (posx >= m_width) || (posy >= m_height);

                    if (outOfRange)
                        continue;

                    if (bVisitedArray.at(computeIndex(posx, posy)))
                        continue;
                    
                    bVisitedArray.at(computeIndex(posx, posy)) = true;

                    if (grid.at(posy).at(posx) == '0')
                        continue;
                    
                    q.push(make_pair(posx - 1, posy));
                    q.push(make_pair(posx + 1, posy));
                    q.push(make_pair(posx, posy - 1));
                    q.push(make_pair(posx, posy + 1));
                }

                ++numOfIdlands;
            }
        }

        return numOfIdlands;
    }

    int numIslands(vector<vector<char>>& grid) {
        //return solveDfs(grid);
        return solveBfs(grid);
    }

private:
    size_t m_width = 0;
    size_t m_height = 0;
};

int main(int32_t argc, char* argv[])
{
    Solution solution;

    const auto start = chrono::system_clock::now();

    {
        vector<vector<char>> input = {
            {'1', '1'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1'},
            {'1'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '0'},
            {'0', '0', '0'},
            {'0', '0', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'0', '0', '0'},
            {'0', '1', '0'},
            {'0', '0', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'0', '0', '0'},
            {'0', '0', '0'},
            {'0', '0', '1'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1', '1', '0'},
            {'1', '0', '0'},
            {'0', '0', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1', '1', '1'},
            {'1', '0', '0'},
            {'1', '0', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '1'},
            {'1', '1', '0'},
            {'1', '0', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '1'},
            {'1', '0', '1'},
            {'1', '1', '1'},
        };
        MY_ASSERT2(solution.numIslands(input), 1);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '0'},
            {'0', '1', '0'},
            {'0', '1', '0'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1', '1', '1'},
            {'1', '1', '1'},
            {'1', '1', '1'},
        };
        assert(solution.numIslands(input) == 1);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '0'},
            {'0', '0', '0'},
            {'0', '0', '1'},
        };
        assert(solution.numIslands(input) == 2);
    }

    {
        vector<vector<char>> input = {
            {'1', '1', '0'},
            {'0', '0', '0'},
            {'0', '1', '1'},
        };
        assert(solution.numIslands(input) == 2);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '1'},
            {'0', '0', '0'},
            {'1', '0', '0'},
        };
        assert(solution.numIslands(input) == 2);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'1', '0', '1'},
            {'1', '0', '1'},
        };
        assert(solution.numIslands(input) == 2);
    }

    {
        vector<vector<char>> input = {
            {'1', '1', '0'},
            {'1', '0', '0'},
            {'0', '0', '1'},
        };
        assert(solution.numIslands(input) == 2);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '0'},
            {'0', '1', '0'},
            {'1', '0', '0'},
        };
        assert(solution.numIslands(input) == 3);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'0', '0', '0'},
            {'1', '1', '1'},
        };
        assert(solution.numIslands(input) == 3);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'0', '1', '0'},
            {'0', '0', '0'},
        };
        MY_ASSERT(solution.numIslands(input) == 3);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'0', '0', '1'},
            {'1', '1', '0'},
        };
        assert(solution.numIslands(input) == 3);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '0'},
            {'0', '0', '1'},
            {'0', '1', '0'},
        };
        assert(solution.numIslands(input) == 3);
    }

    {
        vector<vector<char>> input = {
            {'0', '1', '0'},
            {'1', '0', '1'},
            {'0', '1', '0'},
        };
        assert(solution.numIslands(input) == 4);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'0', '0', '0'},
            {'1', '0', '1'},
        };
        assert(solution.numIslands(input) == 4);
    }

    {
        vector<vector<char>> input = {
            {'1', '0', '1'},
            {'0', '1', '0'},
            {'1', '0', '1'},
        };
        assert(solution.numIslands(input) == 5);
    }

    {
        vector<vector<char>> input = {
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        };
        assert(solution.numIslands(input) == 0);
    }

    const auto end = chrono::system_clock::now();

    const double elapse = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() / 1000.0);

    printf("elapse %.3lf ms\n", elapse);

    return 0;
}