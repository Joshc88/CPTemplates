#include <bits/stdc++.h>
using namespace std;

template <bool oneindexed = true> struct CycleDetection {
    int n;
    vector<int> colour; // Colour is 0 if unseen, 1 if in stack, 2 if processed
    vector<vector<int>> edges;
    vector<int> res, st;

    CycleDetection(int _n) : n(_n) {
        colour.resize(n);
        edges.resize(n);
        st.reserve(n);
    } 

    void add_edge(int x, int y) {
        edges[x-oneindexed].push_back(y-oneindexed);
    }

    void dfs(int cur) {
        for (int i : edges[cur]) {
            if (colour[i] == 2) continue;
            if (colour[i] && res.empty()) {
                int cur = 0;
                while (st[cur] != i) cur++;
                res = vector<int>(st.begin()+cur, st.end());
            } 
            if (!colour[i]) {
                colour[i] = 1;
                st.push_back(i);
                dfs(i);
            }
        }
        colour[cur] = 2;
        st.pop_back();
    }

    // Return the vertices in the cycle. None are repeated.
    vector<int> cycle() {
        for (int i=0; i<n; i++) {
            if (!colour[i] && res.empty()) {
                st.push_back(i);
                colour[i] = 1;
                dfs(i);
            }
        }
        if (oneindexed) {
            for (int& i : res) i++;
        }
        return res;
    }
};