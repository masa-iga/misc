#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

#define ENABLE_DPRINTF (1)
#if ENABLE_DPRINTF
    #define DPRINTF(...) \
    do {\
        printf(__VA_ARGS__);\
    } while (false)
#else
    #define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

class Solution {
public:
    int32_t dfs(int32_t node, int32_t depth, vector<bool> bVisited, const vector<vector<int32_t>>& graph)
    {
        int32_t maxDepth = depth;

        for (int32_t edge : graph.at(node))
        {
            if (bVisited.at(edge))
                continue;
            
            bVisited.at(edge) = true;
            const int32_t d = dfs(edge, depth + 1, bVisited, graph);
            maxDepth = std::max(d, maxDepth);
        }

        return maxDepth;
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        vector<vector<int32_t>> graph(n);

        for (const vector<int32_t> e : edges)
        {
            assert(e.size() == 2);
            assert(e.at(0) != e.at(1));
            graph.at(e.at(0)).emplace_back(e.at(1));
            graph.at(e.at(1)).emplace_back(e.at(0));
        }

        vector<int32_t> mhts(n, INT32_MAX);

        for (int32_t i = 0; i < n; ++i)
        {
            vector<bool> bVisited(n, false);
            bVisited.at(i) = true;

            mhts.at(i) = dfs(i, 0, bVisited, graph);
        }

        vector<int32_t> ans;
        const int32_t min = *min_element(mhts.begin(), mhts.end());

        for (int32_t i = 0; i < n; ++i)
        {
            if (mhts.at(i) == min)
            {
                ans.emplace_back(i);
            }
        }

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t n = 0;
    vector<vector<int32_t>> edges;
    vector<int32_t> ans, exp;
    {
        n = 4;
        edges = {{1, 0}, {1, 2}, {1, 3}};
        ans = solution.findMinHeightTrees(n, edges);
        exp = {1};
        assert(ans == exp);
    }

    {
        n = 6;
        edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
        ans = solution.findMinHeightTrees(n, edges);
        exp = {3, 4};
        assert(ans == exp);
    }

    return 0;
}