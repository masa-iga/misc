#include <cstdio>
#include <cstdint>
#include <vector>
#include <memory>
#include <queue>
#include <cstring>
#include <utility>
#include <unordered_map>
#include <set>
#include "../include/debug.h"

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* createNode(vector<vector<int32_t>> adjList);
void printAdjacency(Node* head);

// TODO: read DFS algorithm。早いのか？
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr)
            return nullptr;

        unordered_map<int32_t, Node*> nodePointers;

        Node* head = new Node(node->val);
        nodePointers[node->val] = head;

        queue<pair<Node *, Node *>> q({make_pair(node, head)});

        while (!q.empty())
        {
            auto [src, dst] = q.front();
            q.pop();

            for (const auto& nsrc : src->neighbors)
            {
                if (nodePointers.find(nsrc->val) != nodePointers.end())
                {
                    Node* ndst = nodePointers.at(nsrc->val);
                    dst->neighbors.push_back(ndst);
                    continue;
                }

                Node* ndst = new Node(nsrc->val);
                nodePointers[nsrc->val] = ndst;
                dst->neighbors.push_back(ndst);
                q.push(make_pair(nsrc, ndst));
            }
        }

        return head;
    }
};


int32_t main(int32_t argc, char* argv[])
{
    Solution solution;
    const Node* head = nullptr;

    {
        Node *node = createNode({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
        Node *ans = solution.cloneGraph(node);
        printf("--- input ---\n");
        printAdjacency(node);
        printf("--- cloned ---\n");
        printAdjacency(ans);
    }

    return 0;
}

Node* createNode(vector<vector<int32_t>> adjList)
{
    const uint32_t numNode = adjList.size();

    if (numNode == 0)
        return nullptr;

    vector<Node*> nodes;

    for (uint32_t i = 0; i < numNode; ++i)
    {
        Node* n = new Node(i + 1);
        nodes.push_back(n);
    }

    for (uint32_t i = 0; i < numNode; ++i)
        for (const auto& neighbor : adjList[i])
            nodes[i]->neighbors.push_back(nodes.at(neighbor - 1));

    return nodes.at(0);
}

void printAdjacency(Node* head)
{
    if (head == nullptr)
        return;

    constexpr size_t kMax = 100;

    array<bool, kMax> bVisitedFlags;
    bVisitedFlags.fill(false);

    array<vector<pair<int32_t, uintptr_t>>, kMax> connected;

    queue<const Node*> q({head});

    while (!q.empty())
    {
        const size_t num = q.size();

        for (size_t i = 0; i < num; ++i)
        {
            const Node* n = q.front();
            q.pop();

            if (bVisitedFlags.at(n->val))
                continue;
            
            bVisitedFlags.at(n->val) = true;

            for (const auto& next : n->neighbors)
            {
                connected.at(n->val).push_back(make_pair(next->val, (uintptr_t)next));
                q.push(next);
            }
        }
    }

    for (uint32_t i = 0; i < kMax; ++i)
    {
        string s;

        for (const auto& e : connected.at(i))
        {
            s += to_string(e.first) + " (" + to_string(e.second) + ") ";
        }

        if (!s.empty())
        {
            printf("%d -> %s\n", i, s.c_str());
        }
    }
}
