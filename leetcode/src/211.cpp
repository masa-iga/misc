#include <cstdio>
#include <cstdint>
#include <cassert>
#include <string>
#include <array>
#include <vector>

using namespace std;

#define DPRINTF(...) \
do { \
    printf("L%d: ", __LINE__); \
    printf(__VA_ARGS__); \
} while (false)

#define ENABLE_ASSERT (1)

#if ENABLE_ASSERT
#define ASSERT(...) \
do { \
    assert(__VA_ARGS__); \
} while (false)
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

class Trie {
public:
    Trie()
    {
        for (auto &n : m_nodes)
            n = nullptr;
    }
    Trie(char c) : Trie() { m_char = c; }

    void addWord(const string& word, int32_t pos)
    {
        ASSERT(pos <= word.size());

        if (pos == word.size())
        {
            m_terminate = true;
            return;
        }
        
        const char c = word.at(pos);
        const int32_t idx = getIndex(c);

        if (m_nodes.at(idx) == nullptr)
        {
            m_nodes.at(idx) = new Trie(c);
        }

        m_nodes.at(idx)->addWord(word, pos + 1);
    }

    bool search(const string& word, int32_t pos) const
    {
        ASSERT(pos <= word.size());

        if (pos == word.size())
            return m_terminate;
        
        const char c = word.at(pos);

        if (c == '.')
        {
            for (const Trie* n : m_nodes)
            {
                if (n == nullptr)
                    continue;

                if (n->search(word, pos + 1))
                    return true;
            }

            return false;
        }

        const int32_t idx = getIndex(c);

        if (m_nodes.at(idx))
            return m_nodes.at(idx)->search(word, pos + 1);

        return false;
    }

    void printWords(string temp) const
    {
        for (const Trie* n : m_nodes)
        {
            if (n == nullptr)
                continue;

            if (m_char == '0')
                n->printWords(temp);
            else
                n->printWords(temp + m_char);
        }

        if (m_terminate)
        {
            temp.push_back(m_char);
            DPRINTF("%s\n", temp.c_str());
        }
    }

private:
    int32_t getIndex(char c) const
    {
        ASSERT('a' <= c && c <= 'z');
        return c - 'a';
    }

    static constexpr size_t kNumOfElements = 26;

    array<Trie*, kNumOfElements> m_nodes;
    char m_char = '0';
    bool m_terminate = false;
};

class WordDictionary {
public:
    WordDictionary() {
        ;
    }
    
    void addWord(string word) {
        trie.addWord(word, 0);
    }
    
    bool search(string word) {
        return trie.search(word, 0);
    }

    void printWords() {
        trie.printWords(string(""));
    }

private:
    Trie trie;
};

void test(const vector<string>& ops, const vector<string>& words, const vector<string>& outputs)
{
    ASSERT(ops.size() == words.size());
    ASSERT(ops.size() == outputs.size());

    WordDictionary* dict = nullptr;

    for (int32_t i = 0; i < ops.size(); ++i)
    {
        const string& op = ops.at(i);

        if (op == "WordDictionary")
        {
            dict = new WordDictionary();
        }
        else if (op == "addWord")
        {
            ASSERT(dict != nullptr);
            dict->addWord(words.at(i));
        }
        else if (op == "search")
        {
            ASSERT(dict != nullptr);
            ASSERT(outputs.at(i) == "true" || outputs.at(i) == "false");

            const bool ret = dict->search(words.at(i));
            const bool exp = outputs.at(i) == "true" ? true : false;

            ASSERT(ret == exp);
        }
        else
        {
            ASSERT(false);
        }
    }

    dict->printWords();
}

int32_t main(int32_t argc, char* argv[])
{
    test(
        {"WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"},
        {{}, {"bad"}, {"dad"}, {"mad"}, {"pad"}, {"bad"}, {".ad"}, {"b.."}},
        {"null", "null", "null", "null", "false", "true", "true", "true"}
        );

    return 0;
}