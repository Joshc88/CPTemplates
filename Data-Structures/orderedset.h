#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

template <typename T> struct ordered_multiset {
    ordered_set<pair<T, int>> ost;
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

    int size() {
        return ost.size();
    }

    bool empty() {
        return ost.empty();
    }
};