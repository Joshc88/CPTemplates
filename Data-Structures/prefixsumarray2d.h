#include <bits/stdc++.h>
using namespace std;

template <class T = int> struct psa2d { // 0-indexed
    vector<vector<T>> prefix;

    psa2d() {}

    psa2d(vector<vector<int>> v) {
        prefix = vector<vector<T>>(v.size()+1, vector<T>(v[0].size()+1));
        for (int i=0; i<v.size(); i++) {
            for (int j=0; j<v[0].size(); j++) prefix[i+1][j+1] = prefix[i+1][j] + prefix[i][j+1] - prefix[i][j] + v[i][j];
        }
    }

    psa2d(vector<vector<long long>> v) {
        prefix = vector<vector<T>>(v.size()+1, vector<T>(v[0].size()+1));
        for (int i=0; i<v.size(); i++) {
            for (int j=0; j<v[0].size(); j++) prefix[i+1][j+1] = prefix[i+1][j] + prefix[i][j+1] - prefix[i][j] + v[i][j];
        }
    }

    T query(int l1, int r1, int l2, int r2) {
        return prefix[r1+1][r2+1] - prefix[l1][r2+1] - prefix[r1+1][l2] + prefix[l1][l2];
    }
};