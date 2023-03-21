#include <bits/stdc++.h>
using namespace std;

template <class T = int> struct psa { // 0-indexed
    vector<T> prefix;

    psa() {}

    psa(vector<int> v) {
        prefix.resize(v.size()+1);
        for (int i=0; i<v.size(); i++) prefix[i+1] = prefix[i]+v[i];
    }

    psa(vector<long long> v) {
        prefix.resize(v.size()+1);
        for (int i=0; i<v.size(); i++) prefix[i+1] = prefix[i]+v[i];
    }

    T query(int l, int r) {
        return prefix[r+1] - prefix[l];
    }
};
