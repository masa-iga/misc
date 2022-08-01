#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int32_t>> graph(numCourses);
        {
            for (const vector<int32_t>& direction : prerequisites)
            {
                assert(direction.size() == 2);
                const int32_t src = direction.at(1);
                const int32_t dst = direction.at(0);
                graph.at(src).push_back(dst);
            }
        }

        vector<int32_t> indegrees(numCourses);
        {
            for (const vector<int32_t>& direction : prerequisites)
            {
                const int32_t dst = direction.at(0);
                indegrees.at(dst)++;
            }
        }

        for (uint32_t i = 0; i < numCourses; ++i)
        {
            uint32_t j = 0;

            for ( ; j < numCourses; ++j)
            {
                if (indegrees.at(j) == 0)
                    break;
            }

            if (j == numCourses)
                return false;
            
            indegrees.at(j) += -1;

            for (const int32_t dst : graph.at(j))
            {
                indegrees.at(dst) += -1;
            }
        }

        return true;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t numCourses = 0;
    vector<vector<int32_t>> prerequisites;

    {
        numCourses = 2;
        prerequisites = {{1, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 2;
        prerequisites = {{0, 1}, {1, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == false);
    }

    {
        numCourses = 2;
        prerequisites = {};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{2, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);

    }

    {
        numCourses = 3;
        prerequisites = {{2, 1}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {1, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {2, 1}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {1, 2}, {0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {1, 2}, {2, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == false);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {2, 1}, {0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {2, 1}, {2, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {1, 2}, {0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {1, 2}, {2, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {2, 1}, {0, 2}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == false);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {2, 1}, {2, 0}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    {
        numCourses = 7;
        prerequisites = {{1, 0}, {0, 3}, {0, 2}, {3, 2}, {2, 5}, {4, 5}, {5, 6}, {2, 4}};
        const bool ans = solution.canFinish(numCourses, prerequisites);
        assert(ans == true);
    }

    return 0;
}