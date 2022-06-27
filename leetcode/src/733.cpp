#include <cstdio>
#include <cstring>
#include <vector>
#include "../include/debug.h"

using namespace std;

class Solution {
public:
    size_t computeIndex(int32_t m, int32_t n)
    {
        MY_ASSERT(m <= m_m);
        MY_ASSERT(n <= m_n);
        return n + m * m_n;
    }

    bool isOutOfRange(int32_t m, int32_t n)
    {
        if (m < 0 || m_m <= m || n < 0 || m_n <= n)
            return true;

        return false;
    }

    void dfs(vector<vector<int32_t>>& image, bool bVisited[], int32_t m, int32_t n, int32_t compColor, int32_t writeColor)
    {
        if (isOutOfRange(m, n))
            return;

        if (bVisited[computeIndex(m ,n)])
            return;
        
        bVisited[computeIndex(m, n)] = true;

        if (image.at(m).at(n) != compColor)
            return;
        
        image.at(m).at(n) = writeColor;
        
        dfs(image, bVisited, m - 1, n, compColor, writeColor);
        dfs(image, bVisited, m + 1, n, compColor, writeColor);
        dfs(image, bVisited, m, n - 1, compColor, writeColor);
        dfs(image, bVisited, m, n + 1, compColor, writeColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        m_m = image.size();
        m_n = image.at(0).size();

        MY_ASSERT(1 <= m_m && m_m <= 50);
        MY_ASSERT(1 <= m_n && m_n <= 50);
        MY_ASSERT(0 <= sr && sr < m_m);
        MY_ASSERT(0 <= sc && sc < m_n);

        bool bVisited[m_m * m_n];
        memset(bVisited, 0x0, sizeof(bVisited));
        const int32_t compColor = image.at(sr).at(sc);

        dfs(image, bVisited, sr, sc, compColor, color);

        return image;
    }

private:
    size_t m_m = 0;
    size_t m_n = 0;
};

int main(int argc, char* argv[])
{
    Solution solution;
    vector<vector<int>> image;
    vector<vector<int>> out;
    vector<vector<int>> exp;
    {
        const vector<vector<int>> init = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
        image = init;
        out = solution.floodFill(image, 1, 1, 2);
        exp = {{2, 2, 2}, {2, 2, 0}, {2, 0, 1}};
        MY_ASSERT(out == exp);
    }

    {
        const vector<vector<int>> init = {{1}};
        image = init;
        out = solution.floodFill(image, 0, 0, 2);
        exp = {{2}};
        MY_ASSERT(out == exp);

        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0}};
        MY_ASSERT(out == exp);

        out = solution.floodFill(image, 0, 0, (2 << 16) - 1);
        exp = {{(2 << 16) - 1}};
        MY_ASSERT(out == exp);
    }

    {
        image = {{1, 2}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 2}};
        MY_ASSERT(out == exp);

        image = {{1, 2}};
        out = solution.floodFill(image, 0, 1, 0);
        exp = {{1, 0}};
        MY_ASSERT(out == exp);

        image = {{1, 1}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 0}};
        MY_ASSERT(out == exp);

        image = {{1, 1}};
        out = solution.floodFill(image, 0, 1, 0);
        exp = {{0, 0}};
        MY_ASSERT(out == exp);
    }

    {
        image = {{1}, {2}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0}, {2}};
        MY_ASSERT(out == exp);

        image = {{1}, {2}};
        out = solution.floodFill(image, 1, 0, 0);
        exp = {{1}, {0}};
        MY_ASSERT(out == exp);

        image = {{2}, {2}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0}, {0}};
        MY_ASSERT(out == exp);

        image = {{2}, {2}};
        out = solution.floodFill(image, 1, 0, 0);
        exp = {{0}, {0}};
        MY_ASSERT(out == exp);
    }

    {
        image = {{1, 2}, {3, 4}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 2}, {3, 4}};
        MY_ASSERT(out == exp);

        image = {{1, 2}, {3, 4}};
        out = solution.floodFill(image, 0, 1, 0);
        exp = {{1, 0}, {3, 4}};
        MY_ASSERT(out == exp);

        image = {{1, 2}, {3, 4}};
        out = solution.floodFill(image, 1, 0, 0);
        exp = {{1, 2}, {0, 4}};
        MY_ASSERT(out == exp);

        image = {{1, 2}, {3, 4}};
        out = solution.floodFill(image, 1, 1, 0);
        exp = {{1, 2}, {3, 0}};
        MY_ASSERT(out == exp);

        image = {{1, 1}, {3, 4}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 0}, {3, 4}};
        MY_ASSERT(out == exp);

        image = {{1, 2}, {0, 4}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 2}, {0, 4}};
        MY_ASSERT(out == exp);

        image = {{1, 2}, {3, 1}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 2}, {3, 1}};
        MY_ASSERT(out == exp);

        image = {{1, 1}, {1, 1}};
        out = solution.floodFill(image, 0, 0, 0);
        exp = {{0, 0}, {0, 0}};
        MY_ASSERT(out == exp);
    }

    return 0;
}