#include <bits/stdc++.h>
using namespace std;

template <class T = int> struct fenwick { // 0 or 1-indexed, doesn't matter
    vector<T> bit, val;
    int n;

    fenwick() {};

    fenwick(int N) { // Maximum position allowed in fenwick tree
        n = N+1; // we will offset all positions by 1 to handle 0-indexed
        bit.resize(n+1);
        val.resize(n+1);
    }

    void add(int pos, T delta) {
        val[pos] += delta;
        for (pos++; pos <= n; pos += pos&-pos) bit[pos] += delta;
    }

    void set(int pos, T v) {
        add(pos, v - val[pos]);
    }

    T query(int pos) { // return sum of positions <= x
        T res = 0;
        for (pos++; pos; pos -= pos&-pos) res += bit[pos];
        return res;
    }

    T query(int l, int r) { // return sum between [l, r]
        return query(r) - query(l-1);
    }
};