#include <bits/stdc++.h>
using namespace std;

template <typename T> struct CoordCompress {
    vector<T> vals;
    map<T, int> index;

    void add(T val) {
        vals.push_back(val);
    }

    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int i=0; i<vals.size(); i++) index[vals[i]] = i;
    }

    int encode(T val) {
        return index[val];
    }

    T decode(int idx) {
        return vals[idx];
    }
};