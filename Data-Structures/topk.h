#include <bits/stdc++.h>
using namespace std;

template <class Compare = less<long long>> struct topK {
    multiset<long long, Compare> s;
    int k;
    long long total = 0;
    typename multiset<long long, Compare>::iterator it;

    topK() {}
    topK(int _k) : k(_k) {}

    void insert(long long x) {
        s.insert(x);
        if (s.size() <= k) total += x;
        else if (Compare{}(x, *it)) total += x - *it--;
        if (s.size() == k) it = prev(s.end());
    }

    void erase(long long x) {
        if (s.size() <= k) s.erase(s.lower_bound(x)), total -= x;
        else {
            auto it2 = s.lower_bound(x);
            if (!Compare{}(*it, x)) total += *++it - x;
            s.erase(it2);
        } 
    }
};