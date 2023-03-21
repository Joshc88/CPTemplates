#include <bits/stdc++.h>
using namespace std;

template <bool oneindexed = true> struct bipartite {
    int n;
    vector<vector<int>> edges;
    vector<int> colour;

    bipartite() {}

    bipartite(int N) {
        n = N;
        edges.resize(n+oneindexed);
    }

    void add_edge(int x, int y) {
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    void dfs(int node, int cur, bool& res) {
        colour[node] = cur;
        for (int i : edges[node]) {
            if (colour[i] == cur) res = false;
            if (colour[i] == -1) dfs(i, cur^1, res);
        }
    }

    bool isBipartite() {
        colour = vector<int>(n+oneindexed, -1);
        bool res = true;
        for (int i=oneindexed; i<n+oneindexed; i++) {
            if (colour[i] == -1) dfs(i, 0, res);
        }
        return res;
    }
};