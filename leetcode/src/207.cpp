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
        unordered_multimap<int32_t, int32_t> hashMap;

        for (const auto& e : prerequisites)
        {
            const int32_t src = e.at(1);
            const int32_t dst = e.at(0);
            hashMap.emplace(dst, src);
        }

        for (auto it = hashMap.cbegin(); it != hashMap.cend(); ++it)
        {
            const int32_t entryPoint = it->second;

            queue<int32_t> q;
            q.push(entryPoint);
            DPRINTF("Entry point: %d\n", entryPoint);

            vector<bool> visitedArray;
            visitedArray.resize(numCourses);

            while (!q.empty())
            {
                const int32_t dst = q.front();
                q.pop();

                if (visitedArray.at(dst))
                {
                    DPRINTF("already visited. (%d)\n", dst);
                    continue;
                }

                visitedArray.at(dst) = true;

                auto keys = hashMap.equal_range(dst);

                for (auto it = keys.first; it != keys.second; ++it)
                {
                    const int32_t src = it->second;

                    if (src == entryPoint)
                        return false;

                    q.push(src);
                    DPRINTF("%d -> %d\n", src, dst);
                }
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