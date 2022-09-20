#include <cstdint>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <array>
#include <unordered_set>

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

class HashTable {
public:
    void add(const string& s)
    {
        m_table.emplace(s);
    }

    bool search(const string& s, vector<bool>* bCacheArray = nullptr) const
    {
        if (bCacheArray == nullptr)
        {
            bCacheArray = new vector<bool>(s.length(), false);
        }

        if (bCacheArray->at(s.length() - 1))
            return false;

        for (int32_t i = 1; i <= s.length(); ++i)
        {
            const string str = s.substr(0, i);

            if (m_table.find(str) == m_table.end())
                continue;
            
            if (i == s.length())
                return true;
            
            const string next = s.substr(i, s.length() - i);

            if (search(next, bCacheArray))
                return true;
        }

        // cache the result (false)
        bCacheArray->at(s.length() - 1) = true;

        return false;
    }

private:
    unordered_set<string> m_table;
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for (const string& s : wordDict)
            m_hashTable.add(s);

        return m_hashTable.search(s);
    }

public:
    HashTable m_hashTable;
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

#if 1
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
#endif

#if 1
    {
        s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
        wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
        test(s, wordDict, false);
    }
#endif

    return true;
}