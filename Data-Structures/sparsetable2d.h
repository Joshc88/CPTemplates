#include <bits/stdc++.h>
using namespace std;

template <class T = int> struct sparseTable2d { // 0-indexed
    T op(T a, T b) {
        return min(a, b);
    } 

    vector<vector<vector<vector<T>>>> st;
    
    sparseTable2d() {}

    sparseTable2d(vector<vector<T>> v) {
        int n = v.size(), m = v[0].size();
        st = vector<vector<vector<vector<T>>>>(__lg(n)+1, vector<vector<vector<T>>>(__lg(m)+1, vector<vector<T>>(n, vector<T>(m))));
        st[0][0] = v;
        for (int i=0; i<n; i++) {
            for (int j=1; j<st[0].size(); j++) {
                for (int i2=0; i2+(1<<j)<=m; i2++) st[0][j][i][i2] = op(st[0][j-1][i][i2], st[0][j-1][i][i2+(1<<(j-1))]);
            }
        }
        for (int k=1; k<st.size(); k++) {
            for (int i=0; i+(1<<k)<=n; i++) {
                for (int l=0; l<st[0].size(); l++) {
                    for (int j=0; j+(1<<l)<=m; j++) st[k][l][i][j] = op(st[k-1][l][i][j], st[k-1][l][i+(1<<(k-1))][j]);
                }
            }
        }
    } 

    T query(int l1, int r1, int l2, int r2) { // inclusive range
        int a = __lg(r1-l1+1), b = __lg(r2-l2+1);
        return op(op(st[a][b][l1][l2], st[a][b][r1-(1<<a)+1][l2]), op(st[a][b][l1][r2-(1<<b)+1], st[a][b][r1-(1<<a)+1][r2-(1<<b)+1]));
    }
};