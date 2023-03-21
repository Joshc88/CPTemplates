#include <bits/stdc++.h>
using namespace std;

template <class T = int> struct fenwick2d { // 0 or 1-indexed, doesn't matter
    vector<vector<T>> bit, val;
    int n, m;

    fenwick2d() {};

    fenwick2d(int N, int M) { // Maximum position allowed in fenwick tree
        n = N+1, m = M+1; // we will offset all positions by 1 to handle 0-indexed
        bit = vector<vector<T>>(n+1, vector<T>(m+1));
        val = vector<vector<T>>(n+1, vector<T>(m+1));
    }

    void add(int x, int y, T delta) {
        val[x][y] += delta;
        for (x++; x <= n; x += x&-x) {
            for (int y1=y+1; y1 <= m; y1 += y1&-y1) bit[x][y1] += delta;
        }
    }

    void set(int x, int y, T v) {
        add(x, y, v - val[x][y]);
    }

    T query(int x, int y) { // return sum of positions with (<=x, <=y)
        T res = 0;
        for (x++; x; x -= x&-x) {
            for (int y1=y+1; y1; y1 -= y1&-y1) res += bit[x][y1];
        }
        return res;
    }

    T query(int l1, int r1, int l2, int r2) { // return rectangle sum
        return query(r1, r2) - query(l1-1, r2) - query(r1, l2-1) + query(l1-1, l2-1);
    }
};