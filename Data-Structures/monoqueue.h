#include <bits/stdc++.h>
using namespace std;

template <class T, bool ismax = true> struct MQ {
    const T INF = numeric_limits<T>::max()/2;
    queue<int> q;
    deque<int> m;
    
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
