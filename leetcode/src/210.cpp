#include <cstdint>
#include <cstdio>
#include <vector>
#include <cassert>

#define ENABLE_DPRINTF (1)

using namespace std;

#if ENABLE_DPRINTF
    #define DPRINTF(...) \
    do {\
        printf(__VA_ARGS__); \
    } while (false)
#else
    #define DPRINTF(...)
#endif // #if ENABLE_DPRINTF

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int32_t>> graph(numCourses);
        {
            for (const vector<int32_t>& directions : prerequisites)
            {
                assert(directions.size() == 2);
                const int32_t src = directions.at(1);
                const int32_t dst = directions.at(0);
                graph.at(src).emplace_back(dst);
            }
        }

        vector<int32_t> indegrees(numCourses, 0);
        {
            for (const vector<int32_t>& directions : prerequisites)
            {
                assert(directions.size() == 2);
                const int32_t dst = directions.at(0);
                indegrees.at(dst) += 1;
            }
        }

        vector<int32_t> ans;
        for (int32_t i = 0; i < numCourses; ++i)
        {
            int32_t j = 0;

            for ( ; j < numCourses; ++j)
            {
                if (indegrees.at(j) == 0)
                    break;
            }

            if (j == numCourses)
                return vector<int32_t>();

            ans.emplace_back(j);
            indegrees.at(j) -= 1;

            for (int32_t dst : graph.at(j))
            {
                assert(0 <= dst && dst < numCourses);
                indegrees.at(dst) -= 1;
            }
        }

        return ans;
    }
};

void checkDependency(const vector<vector<int32_t>>& prerequisites, const vector<int32_t>& path);

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    int32_t numCourses = 0;
    vector<vector<int32_t>> prerequisites;
    vector<int32_t> ans;

    {
        numCourses = 1;
        prerequisites = {};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({0}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 2;
        prerequisites = {};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 2;
        prerequisites = {{0, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({1, 0}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 2;
        prerequisites = {{1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({0, 1}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 2;
        prerequisites = {{0, 1}, {1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 2}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{2, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {0, 2}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {1, 2}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({2, 1, 0}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {2, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({1, 0, 2}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 1}, {2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}, {1, 2}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}, {1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({2, 0, 1}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}, {2, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{0, 2}, {2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({1, 2, 0}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 2}, {1, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 2}, {2, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({0, 2, 1}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 2}, {2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {2, 0}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{1, 0}, {2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans == vector<int32_t>({0, 1, 2}));
        checkDependency(prerequisites, ans);
    }

    {
        numCourses = 3;
        prerequisites = {{2, 0}, {2, 1}};
        ans = solution.findOrder(numCourses, prerequisites);
        assert(ans != vector<int32_t>());
        checkDependency(prerequisites, ans);
    }

    return 0;
}

void checkDependency(const vector<vector<int32_t>>& prerequisites, const vector<int32_t>& path)
{
    for (const vector<int32_t> &dir : prerequisites)
    {
        assert(dir.size() == 2);
        const int32_t src = dir.at(1);
        const int32_t dst = dir.at(0);

        bool bVisitedSrc = false;

        for (const int32_t course : path)
        {
            if (course == src)
            {
                assert(bVisitedSrc == false);
                bVisitedSrc = true;
            }

            if (course == dst)
            {
                assert(bVisitedSrc == true);
                break;
            }
        }
    }
}