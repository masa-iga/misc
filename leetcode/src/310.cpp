#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

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
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        vector<set<int32_t>> graph(n);
        {
            for (const vector<int32_t>& edge : edges)
            {
                graph.at(edge.at(0)).emplace(edge.at(1));
                graph.at(edge.at(1)).emplace(edge.at(0));
            }
        }

        vector<int32_t> leaves;
        {
            for (int32_t i = 0; i < n; ++i)
                if (graph.at(i).size() <= 1)
                    leaves.emplace_back(i);
        }

        while (n > 2)
        {
            n -= leaves.size();

            vector<int32_t> nextLeaves;

            for (const int32_t leave : leaves)
            {
                assert(graph.at(leave).size() == 1);
                const int32_t nextNode = *graph.at(leave).begin();
                graph.at(nextNode).erase(leave);

                if (graph.at(nextNode).size() == 1)
                {
                    nextLeaves.emplace_back(nextNode);
                }
            }

            assert(nextLeaves.size() != 0);
            leaves = std::move(nextLeaves);
        }

        return leaves;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t n = 0;
    vector<vector<int32_t>> edges;
    vector<int32_t> ans, exp;

    {
        n = 1;
        edges = {};
        ans = solution.findMinHeightTrees(n, edges);
        exp = {0};
        assert(ans == exp);
    }

    {
        n = 2;

        edges = {{0, 1}};
        exp = {0, 1};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);

        edges = {{1, 0}};
        exp = {0, 1};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);
    }

    {
        n = 3;

        edges = {{0, 1}, {0, 2}};
        exp = {0};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);

        edges = {{0, 1}, {1, 2}};
        exp = {1};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);

        edges = {{0, 2}, {1, 2}};
        exp = {2};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);
    }

    {
        n = 4;

        edges = {{1, 0}, {1, 2}, {1, 3}};
        exp = {1};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);
    }

    {
        n = 6;

        edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
        exp = {3, 4};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);

        edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
        exp = {3};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);
    }

    {
        // TODO: debug
        n = 7;

        edges = {{0,1},{1,2},{1,3},{2,4},{3,5},{4,6}};
        exp = {1, 2};
        ans = solution.findMinHeightTrees(n, edges); assert(ans == exp);
    }

    return 0;
}