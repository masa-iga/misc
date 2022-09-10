#include <cstdint>
#include <cstdio>
#include <string>
#include <cassert>
#include <array>
#include <vector>
#include <string>

using namespace std;

#define DPRINTF(...) \
do { \
    printf("%d: ", __LINE__); \
    printf(__VA_ARGS__); \
} while (false)

#define ASSERT(...) \
do { \
    assert(__VA_ARGS__); \
} while (false)

class Trie {
private:
    class Node {
    public:
        Node() : Node('0') { }

        Node(char c) : m_c(c)
        {
            for (Node *&n : m_nodes)
                n = nullptr;
        }

        void insert(const string& word, int32_t pos)
        {
            ASSERT(0 <= pos && pos <= word.length());

            if (word.length() == pos)
            {
                m_hasTerminate = true;
                return;
            }

            const char c = word.at(pos);
            const int32_t idx = convertIndex(c);

            if (m_nodes.at(idx) == nullptr)
            {
                m_nodes.at(idx) = new Node(word.at(pos));
                m_hasChild = true;
            }

            m_nodes.at(idx)->insert(word, pos + 1);
        }

        bool search(const string& word, int32_t pos)
        {
            ASSERT(0 <= pos && pos <= word.length());

            if (word.length() == pos)
            {
                return m_hasTerminate;
            }
            
            const int32_t idx = convertIndex(word.at(pos));

            if (m_nodes.at(idx) == nullptr)
                return false;
            
            return m_nodes.at(idx)->search(word, pos + 1);
        }

        bool startsWith(const string& prefix, int32_t pos)
        {
            ASSERT(0 <= pos && pos <= prefix.length());

            if (prefix.length() == pos)
            {
                if (m_hasChild)
                    return true;
                
                if (m_hasTerminate)
                    return true;
                
                return false;
            }

            const int32_t idx = convertIndex(prefix.at(pos));

            if (m_nodes.at(idx) == nullptr)
                return false;

            return m_nodes.at(idx)->startsWith(prefix, pos + 1);
        }

    private:
        int32_t convertIndex(char c)
        {
            ASSERT('a' <= c && c <= 'z');
            return c - 'a';
        }

        static constexpr size_t kNumElements = 'z' - 'a' + 1;

        array<Node*, kNumElements> m_nodes;
        char m_c = '0';
        bool m_hasTerminate = false;
        bool m_hasChild = false;
    };

public:
    Trie() {
        ;
    }

    void insert(string word) {
        ASSERT(!word.empty());
        topNode.insert(word, 0);
    }
    
    bool search(string word) {
        if (word.empty())
            return false;

        return topNode.search(word, 0);
    }
    
    bool startsWith(string prefix) {
        if (prefix.empty())
            return false;

        return topNode.startsWith(prefix, 0);
    }

private:
    Node topNode;
};

void test(const vector<string>& commands, const vector<string>& words, const vector<string>& exps)
{
    ASSERT(commands.size() == words.size());
    ASSERT(commands.size() == exps.size());

    Trie* trie = nullptr;

    for (int32_t i = 0; i < commands.size(); ++i)
    {
        const string& command = commands.at(i);
        if (command == "Trie")
        {
            trie = new Trie();
        }
        else if (command == "insert")
        {
            ASSERT(trie != nullptr);
            trie->insert(words.at(i));
        }
        else if (command == "search")
        {
            const bool ret = trie->search(words.at(i));
            ASSERT(exps.at(i) == "true" || exps.at(i) == "false");
            const bool exp = exps.at(i) == "true" ? true : false;
            ASSERT(ret == exp);
        }
        else if (command == "startsWith")
        {
            const bool ret = trie->startsWith(words.at(i));
            ASSERT(exps.at(i) == "true" || exps.at(i) == "false");
            const bool exp = exps.at(i) == "true" ? true : false;
            ASSERT(ret == exp);
        }
        else
        {
            ASSERT(false); // should not reach here
            break;
        }
    }
}

int32_t main(int32_t argc, char* argv[])
{
    {
        test(
            {"Trie", "insert", "search", "search", "startsWith", "insert", "search"},
            {{}, {"apple"}, {"apple"}, {"app"}, {"app"}, {"app"}, {"app"}},
            { "null", "null", "true", "false", "true", "null", "true" }
            );
    }

#if 0
    {
        Trie trie;
        trie.insert("apple");
        ASSERT(trie.search("apple"));
        ASSERT(!trie.search("app"));
        ASSERT(trie.startsWith("app"));
        trie.insert("app");
        ASSERT(trie.search("app"));
    }

    {
        Trie trie;
        ASSERT(!trie.search(""));
        ASSERT(!trie.startsWith(""));
    }

    {
        Trie trie;
        ASSERT(!trie.search("a"));
        ASSERT(!trie.startsWith("a"));
        ASSERT(!trie.search("b"));
        ASSERT(!trie.startsWith("b"));
        ASSERT(!trie.search("z"));
        ASSERT(!trie.startsWith("z"));

        trie.insert("a");
        ASSERT(trie.search("a"));
        ASSERT(trie.startsWith("a"));
        ASSERT(!trie.search("b"));
        ASSERT(!trie.startsWith("b"));
        ASSERT(!trie.search("z"));
        ASSERT(!trie.startsWith("z"));

        trie.insert("b");
        ASSERT(trie.search("a"));
        ASSERT(trie.startsWith("a"));
        ASSERT(trie.search("b"));
        ASSERT(trie.startsWith("b"));
        ASSERT(!trie.search("z"));
        ASSERT(!trie.startsWith("z"));
    }

    {
        Trie trie;
        trie.insert("ab");
        ASSERT(!trie.search("a"));
        ASSERT(!trie.search("b"));
        ASSERT(trie.startsWith("a"));
        ASSERT(!trie.startsWith("b"));
        ASSERT(trie.search("ab"));
        ASSERT(trie.startsWith("ab"));

        trie.insert("ac");
        ASSERT(!trie.search("a"));
        ASSERT(!trie.search("b"));
        ASSERT(trie.startsWith("a"));
        ASSERT(!trie.startsWith("b"));
        ASSERT(trie.search("ab"));
        ASSERT(trie.startsWith("ab"));
        ASSERT(trie.search("ac"));
        ASSERT(trie.startsWith("ac"));
    }

    {
        Trie trie;
        trie.insert("abc");
        ASSERT(!trie.search("a"));
        ASSERT(trie.startsWith("a"));
        ASSERT(!trie.search("ab"));
        ASSERT(trie.startsWith("ab"));
        ASSERT(trie.search("abc"));
        ASSERT(trie.startsWith("abc"));
    }
#endif

    return 0;
}