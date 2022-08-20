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
    enum class State
    {
        kUnvisited,
        kSafe,
        kUnsafe,
    };

    bool dfs(vector<State>& states, const vector<vector<int32_t>>& graph, int32_t index)
    {
        if (states.at(index) != State::kUnvisited)
        {
            return (states.at(index) == State::kSafe) ? true : false;
        }

        states.at(index) = State::kUnsafe;

        for (const int32_t next_index : graph.at(index))
        {
            if (!dfs(states, graph, next_index))
                return false;
        }

        states.at(index) = State::kSafe;

        return true;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<State> states(graph.size());
        std::fill(states.begin(), states.end(), State::kUnvisited);

        vector<int32_t> ans;

        for (int32_t i = 0; i < graph.size(); ++i)
        {
            if (dfs(states, graph, i))
                ans.emplace_back(i);
        }

        return ans;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<vector<int32_t>> graph;
    vector<int32_t> ans;
    vector<int32_t> exp;

    {
        {
            graph = {{}, {}, {}};
            exp = {0, 1, 2};
            ans = solution.eventualSafeNodes(graph); assert(ans == exp);
        }

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