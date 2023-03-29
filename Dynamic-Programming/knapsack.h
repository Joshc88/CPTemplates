#include <bits/stdc++.h>
using namespace std;

template <class T, bool ismax = true> struct MQ {
    const T INF = numeric_limits<T>::max()/2;
    queue<T> q;
    deque<T> m;
    
    MQ() {}

    MQ(vector<T> arr) {
        for (T i : arr) push(i);
    } 

    void push(T val) {
        q.push(val);
        if (ismax) {
            while (!m.empty() && m.back() < val) m.pop_back();
        } else {
            while (!m.empty() && m.back() > val) m.pop_back();
        }
        m.push_back(val);
    }

    void pop() {
        assert(!q.empty());
        if (q.front() == m.front()) m.pop_front();
        q.pop();
    }

    T get() {
        return m.empty() ? (ismax ? -INF : INF): m.front();
    }

    int size() {
        return q.size();
    }
};

template <typename T = long long> struct knapsack {
    struct item {
        T value;
        int weight, count;
    };

    vector<item> items;

    // Count = -1 represents unbounded
    void add_item(T value, int weight, int count = -1) {
        items.push_back(item{value, weight, count});
    }

    vector<T> solve(int MAX_W) {
        vector<T> dp(MAX_W + 1);
        for (item& i : items) {
            if (i.count == 1) {
                for (int j=MAX_W; j>=i.weight; j--) dp[j] = max(dp[j], dp[j-i.weight] + i.value);
            } else if (i.count == -1) {
                for (int j=i.weight; j<=MAX_W; j++) dp[j] = max(dp[j], dp[j-i.weight] + i.value);
            } 
            else {
                if (i.weight > MAX_W) continue;
                for (int j=0; j<i.weight; j++) {
                    MQ<T, true> mq;
                    for (int l=0, k=j; k<=MAX_W; l++, k+=i.weight) {
                        mq.push(dp[k] - l * i.value);
                        dp[k] = mq.get() + l * i.value;
                        if (mq.size() > i.count) mq.pop();
                    }
                }
            }
        }
        return dp;
    }
};