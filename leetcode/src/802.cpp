#include <cstdio>
#include <cstdint>
#include <vector>
#include <cassert>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

#define ENABLE_DPRINTF (1)

#if ENABLE_DPRINTF
#define DPRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

        vector<set<int32_t>> inGraph(graph.size());
        vector<set<int32_t>> outGraph(graph.size());
        {
            for (int32_t in = 0; in < graph.size(); ++in)
            {
                for (const int32_t out : graph.at(in))
                {
                    inGraph.at(out).emplace(in);
                    outGraph.at(in).emplace(out);
                }
            }
        }

        vector<int32_t> safeNodes;
        queue<int32_t> terminalNodes;
        {
            for (int32_t i = 0; i < graph.size(); ++i)
                if (outGraph.at(i).size() == 0)
                {
                    terminalNodes.emplace(i);
                    safeNodes.emplace_back(i);
                }
        }

        while (!terminalNodes.empty())
        {
            const int32_t node = terminalNodes.front();
            terminalNodes.pop();

            for (const int32_t inNode : inGraph.at(node))
            {
                outGraph.at(inNode).erase(node);

                if (outGraph.at(inNode).size() == 0)
                {
                    terminalNodes.emplace(inNode);
                    safeNodes.emplace_back(inNode);
                }
            }
        }

        std::sort(safeNodes.begin(), safeNodes.end());

        return safeNodes;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<vector<int32_t>> graph;
    vector<int32_t> ans;
    vector<int32_t> exp;

    {
        graph = {{}, {}, {}};
        exp = {0, 1, 2};
        ans = solution.eventualSafeNodes(graph); assert(ans == exp);

        {
            graph = {{}, {0}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {}, {0}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {}, {1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);
        }

        {
            graph = {{1, 2}, {}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0, 2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {}, {0, 1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);
        }

        {
            graph = {{1}, {0}, {}};
            exp = {2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {0}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0}, {0}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0}, {1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {2}, {0}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {2}, {1}};
            exp = {0};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {}, {0}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {}, {1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {}, {0}};
            exp = {1};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {}, {1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);
        }

        {
            graph = {{1}, {0}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {0}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {2}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {2}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {0}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {0}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {2}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {2}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);


            graph = {{1,2}, {0}, {}};
            exp = {2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1,2}, {2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1,2}, {}, {0}};
            exp = {1};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1,2}, {}, {1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {0, 2}, {}};
            exp = {2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {0, 2}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0, 2}, {0}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0, 2}, {1}};
            exp = {0};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1}, {}, {0, 1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{2}, {}, {0, 1}};
            exp = {1};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {0}, {0, 1}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{}, {2}, {0, 1}};
            exp = {0};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);


            graph = {{1, 2}, {0, 2}, {}};
            exp = {2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {}, {0, 1}};
            exp = {1};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {0}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {0}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {2}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {2}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);


            graph = {{1, 2}, {0, 2}, {0}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {0, 2}, {1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {0}, {0, 1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);

            graph = {{1, 2}, {2}, {0, 1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);


            graph = {{1, 2}, {0, 2}, {0, 1}};
            exp = {};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);
        }
    }

    return 0;
}