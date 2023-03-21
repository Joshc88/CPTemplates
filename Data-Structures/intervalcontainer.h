#include <bits/stdc++.h>
using namespace std;

template <typename T> struct IntervalContainer {
    set<pair<T, T>> intervals;
    T total = 0;

    void add(T l, T r) {
        while (true) {
            auto it = intervals.lower_bound(make_pair(l, l));
            if (it == intervals.end() || it->first > r+1) break;
            r = max(r, it->second);
            l = min(l, it->first);
            total -= it->second - it->first + 1;
            intervals.erase(it);
        }
        while (true) {
            auto it = intervals.lower_bound(make_pair(l, l));
            if (it == intervals.begin()) break;
            it--;
            if (it->second < l-1) break;
            r = max(r, it->second);
            l = min(l, it->first);
            total -= it->second - it->first + 1;
            intervals.erase(it);
        }
        intervals.insert(make_pair(l, r));
        total += r - l + 1;
    }

    void remove(T l, T r) {
        while (true) {
            auto it = intervals.lower_bound(make_pair(l, l));
            if (it == intervals.end() || it->first > r) break;
            auto [l2, r2] = *it;
            intervals.erase(it);
            total -= min(r2, r) - l2 + 1;
            if (r2 > r) {
                intervals.insert(make_pair(r+1, r2));
                break;
            }
        }
        while (true) {
            auto it = intervals.lower_bound(make_pair(l, l));
            if (it == intervals.begin()) break;
            it--;
            if (it->second < l) break;
            auto [l2, r2] = *it;
            intervals.erase(it);
            total -= min(r, r2) - l + 1;
            if (l2 < l) intervals.insert(make_pair(l2, l-1));
            if (r2 > r) intervals.insert(make_pair(r+1, r2)); 
            break;
        }
    }

    bool intersects(T l, T r) {
        auto it = intervals.lower_bound(make_pair(l, l));
        if (it != intervals.end() && it->first <= r) return true;
        return it != intervals.begin() && (--it)->second >= l;
    }

    bool contains(T l, T r) {
        auto it = intervals.lower_bound(make_pair(l+1, l));
        if (it == intervals.begin()) return false;
        it--;
        return it->first <= l && r <= it->second;
    }
};