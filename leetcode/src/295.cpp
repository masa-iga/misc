#include <cstdint>
#include <cstdio>
#include <cassert>
#include <queue>

using namespace std;

#define DPRINTF(...) \
do { \
    printf(__VA_ARGS__); \
} while (false)

#define ASSERT(...) \
do { \
    assert(__VA_ARGS__); \
} while (false)

class MedianFinder {
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if (hq_min.empty())
        {
            hq_min.emplace(num);
            return;
        }

        if (hq_min.size() == hq_max.size())
        {
            if (num > hq_max.top())
            {
                hq_min.emplace(num);
            }
            else
            {
                hq_min.emplace(hq_max.top());
                hq_max.pop();
                hq_max.emplace(num);
            }

            return;
        }

        if (num < hq_min.top())
        {
            hq_max.emplace(num);
        }
        else
        {
            const int32_t temp = hq_min.top();
            hq_min.pop();
            hq_min.emplace(num);
            hq_max.emplace(temp);
        }
    }
    
    double findMedian() {
        ASSERT(hq_min.size() > 0 || hq_max.size() > 0);

        if (hq_max.empty())
        {
            ASSERT(hq_min.size() == 1);
            return hq_min.top();
        }

        if (hq_min.size() == hq_max.size())
        {
            return (static_cast<double>(hq_min.top()) + static_cast<double>(hq_max.top())) / 2.0f;
        }

        ASSERT(hq_min.size() == hq_max.size() + 1);

        return static_cast<double>(hq_min.top());
    }

private:
    priority_queue<int32_t, vector<int32_t>, greater<int32_t>> hq_min;
    priority_queue<int32_t> hq_max;
};

int32_t main(int32_t argc, char* argv[])
{
    float ans = 0.0f;
    
    {
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        ans = mf.findMedian(); ASSERT(ans == 1.5f);
        mf.addNum(3);
        ans = mf.findMedian(); ASSERT(ans == 2.0f);
    }

    {
        MedianFinder mf;
        mf.addNum(1);
        ans = mf.findMedian(); ASSERT(ans == 1.0f);
        mf.addNum(2);
        ans = mf.findMedian(); ASSERT(ans == 1.5f);
        mf.addNum(3);
        ans = mf.findMedian(); ASSERT(ans == 2.0f);
        mf.addNum(4);
        ans = mf.findMedian(); ASSERT(ans == 2.5f);
    }

    {
        MedianFinder mf;

        for (int32_t i = 0; i < 50 * 1000; ++i)
        {
            mf.addNum(i);
        }
        ans = mf.findMedian(); ASSERT(ans == (24999.f + 25000.f)/2.f);
    }

    return 0;
}