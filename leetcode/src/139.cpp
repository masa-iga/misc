#include <cstdint>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <array>

using namespace std;

#define ENABLE_ASSERT (1)
#define ENABLE_PRINTF (1)

#if ENABLE_ASSERT
#define ASSERT(...) \
do { \
    assert(__VA_ARGS__); \
} while (false)
#else
#define ASSERT(...)
#endif // #if ENABLE_ASSERT

#if ENABLE_PRINTF
#define DPRINTF(...) \
do { \
    printf("L%d: ", __LINE__); \
    printf(__VA_ARGS__); \
} while (false)
#else
#define DPRINTF(...)
#endif // #if ENABLE_PRINTF

class Trie
{
public:
    Trie()
    {
        for (Trie*& n : m_nodes)
            n = nullptr;
    }
    Trie(char c) : Trie() { m_c = c; }

    bool findWord(const string& word, int32_t pos) const
    {
        ASSERT(pos <= word.size());

        if (pos == word.size())
            return m_terminate;
        
        const int32_t idx = getIndex(word.at(pos));

        if (m_nodes.at(idx) == nullptr)
            return false;

        return m_nodes.at(idx)->findWord(word, pos + 1);
    }

    void addWord(const string& word, int32_t pos)
    {
        ASSERT(pos <= word.size());

        if (word.size() == pos)
        {
            m_terminate = true;
            return;
        }
        
        const int32_t idx = getIndex(word.at(pos));

        if (m_nodes.at(idx) == nullptr)
            m_nodes.at(idx) = new Trie(word.at(pos));
        
        m_nodes.at(idx)->addWord(word, pos + 1);
    }

private:
    static constexpr size_t kNumOfElements = 'z' - 'a' + 1;

    int32_t getIndex(char c) const
    {
        ASSERT('a' <= c && c <= 'z');
        return c - 'a';
    }

    array<Trie*, kNumOfElements> m_nodes;
    char m_c = '0';
    bool m_terminate = false;
};

class Solution {
public:
    bool wordBreak(const string& s, vector<string>& wordDict) {
        for (const string& w : wordDict)
            m_trie.addWord(w, 0);

        return wordSearch(s);
    }

private:
    bool wordSearch(const string& s)
    {
        if (s.empty())
            return true;

        const int32_t maxLen = s.size();
        ASSERT(maxLen > 0);

        for (int32_t i = maxLen; i > 0; --i)
        {
            const string str = s.substr(0, i);

            if (m_trie.findWord(str, 0))
            {
                const string newStr = s.substr(i, maxLen);

                if (wordSearch(newStr))
                    return true;
            }
        }

        return false;
    }

    Trie m_trie;
};

void test(const string& s, vector<string>& wordDict, bool exp)
{
    Solution solution;
    ASSERT(solution.wordBreak(s, wordDict) == exp);
}

int32_t main(int32_t argc, char*  argv[])
{
    string s;
    vector<string> wordDict;

    {
        s = "leetcode";
        wordDict = {"leet", "code"};
        test(s, wordDict, true);
    }

    {
        s = "applepenapple";
        wordDict = {"apple","pen"};
        test(s, wordDict, true);
    }

    {
        s = "catsandog";
        wordDict = {"cats","dog","sand","and","cat"};
        test(s, wordDict, false);
    }

    {
        s = "a";
        wordDict = {"a","b","c"};
        test(s, wordDict, true);

        wordDict = {"b","c", "d"};
        test(s, wordDict, false);
    }

    {
        s = "ab";
        wordDict = {"a","b","c"};
        test(s, wordDict, true);

        wordDict = {"a","c","d"};
        test(s, wordDict, false);

        wordDict = {"b","c","d"};
        test(s, wordDict, false);
    }

    {
        s = "abc";
        wordDict = {"a","b","c"};
        test(s, wordDict, true);

        wordDict = {"b","c","d"};
        test(s, wordDict, false);

        wordDict = {"ab","c","d"};
        test(s, wordDict, true);

        wordDict = {"ae","c","d"};
        test(s, wordDict, false);

        wordDict = {"ab","bc","a"};
        test(s, wordDict, true);
    }

#if 0
    {
        s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
        wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
        test(s, wordDict, true);
    }
#endif

    return true;
}