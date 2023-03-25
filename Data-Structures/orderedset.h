#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

template <typename T> struct ordered_multiset {
    ordered_set<pair<int, T>> ost;
    map<T, int> freq;

    void insert(T val) {
        ost.insert(make_pair(val, ++freq[val]));
    }

    void erase(T val) {
        ost.erase(make_pair(val, freq[val]--));
    }

    int order_of_key(T val) {
        return ost.order_of_key(make_pair(val, -1));
    }

    T find_by_order(T val) {
        return ost.find_by_order(val)->first;
    }

    T bisect_left(T val) {
        auto it = ost.lower_bound(make_pair(val, -1));
        return it == ost.end() ? ost.size() : ost.order_of_key(*it);
    }

    T bisect_right(T val) {
        auto it = ost.lower_bound(make_pair(val, 1000000000));
        return it == ost.end() ? ost.size() : ost.order_of_key(*it);
    }

    int size() {
        return ost.size();
    }

    bool empty() {
        return ost.empty();
    }
};