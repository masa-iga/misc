#include <cstdint>
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>

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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* makeNodeLists(vector<int32_t> vals)
{
    if (vals.empty())
        return nullptr;
    
    ListNode* top = new ListNode(vals.at(0));
    ListNode* current = top;

    for (int32_t i = 1; i < vals.size(); ++i)
    {
        current->next = new ListNode(vals.at(i));
        current = current->next;
    }

    return top;
}

bool isIdentical(const ListNode* l, const ListNode* r)
{
    while (l != nullptr && r != nullptr)
    {
        if (l->val != r->val)
        {
            assert(false);
            return false;
        }

        l = l->next;
        r = r->next;
    }

    if (l == nullptr && r == nullptr)
        return true;
    
    assert(false);
    return false;
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto comp = [](const ListNode* l, const ListNode* r)
        {
            return l->val > r->val;
        };

        priority_queue<const ListNode*, vector<const ListNode*>, decltype(comp)> pq(comp);

        for (const ListNode* node : lists)
        {
            if (node != nullptr)
                pq.emplace(node);
        }

        ListNode* top = nullptr;
        ListNode* current = nullptr;

        while (!pq.empty())
        {
            const ListNode* n = pq.top();
            pq.pop();

            if (n->next)
            {
                pq.emplace(n->next);
            }

            if (top == nullptr)
            {
                top = new ListNode(n->val);
                current = top;
                continue;
            }

            current->next = new ListNode(n->val);
            current = current->next;
        }

        return top;
    }
};

int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    vector<ListNode*> inpv;
    ListNode* ans = nullptr;

    {
        inpv = {};
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, nullptr));

        inpv = {{}};
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, nullptr));
    }

    {
        inpv = {
            {makeNodeLists({1})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({1})));

        inpv = {
            {makeNodeLists({0, 0})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({0, 0})));

        inpv = {
            {makeNodeLists({1, 2, 3})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({1, 2, 3})));

        inpv = {
            {makeNodeLists({-3, -2, -1})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-3, -2, -1})));

        inpv = {
            {makeNodeLists({-1, 0, 1})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-1, 0, 1})));

        inpv = {
            {makeNodeLists({-10000, 10000})}
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-10000, 10000})));
    }

    {
        inpv = {
            {makeNodeLists({-1, 0, 1})},
            {makeNodeLists({2, 3, 4})},
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-1, 0, 1, 2, 3, 4})));

        inpv = {
            {makeNodeLists({-10, 0, 10})},
            {makeNodeLists({-8, 3, 4})},
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-10, -8, 0, 3, 4, 10})));

        inpv = {
            {makeNodeLists({-10, 0, 10})},
            {makeNodeLists({-10, 3, 4})},
        };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({-10, -10, 0, 3, 4, 10})));
    }

    {
        inpv = {
            {makeNodeLists({1, 4, 5})},
            {makeNodeLists({1, 3, 4})},
            {makeNodeLists({2, 6})},
            };
        ans = solution.mergeKLists(inpv);
        assert(isIdentical(ans, makeNodeLists({1, 1, 2, 3, 4, 4, 5, 6})));
    }

    return 0;
}