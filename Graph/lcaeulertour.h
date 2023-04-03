#include <bits/stdc++.h>
using namespace std;

template <class T> struct sparseTable { // 0-indexed
    T op(T a, T b) {
        return min(a, b);
    } 

    int n;
    vector<vector<T>> st;
    
    sparseTable() {}

    sparseTable(vector<T> v) {
        n = v.size();
        st = vector<vector<T>>(__lg(n)+1, vector<T>(n));
        st[0] = v;
        for (int i=1; i<st.size(); i++) {
            for (int j=0; j+(1<<i)<=n; j++) st[i][j] = op(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    } 

    T query(int l, int r) { // inclusive range
        int sz = __lg(r-l+1);
        return op(st[sz][l], st[sz][r-(1<<sz)+1]);
    }
};

struct LCA { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<int>> edges;
    vector<int> depth, tin, tout;
    vector<pair<int, int>> tour;
    sparseTable<pair<int, int>> st;
    
    LCA() {}

    LCA(int N) {
        n = N+1;
        edges.resize(n);
        depth.resize(n);
        tin.resize(n);
        tout.resize(n);
    }

    void add_edge(int a, int b) {
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void dfs(int cur, int parent = -1, int cur_depth = 0) {
        tin[cur] = tout[cur] = tour.size();
        tour.emplace_back(cur_depth, cur);
        depth[cur] = cur_depth;
        for (int node : edges[cur]) {
            if (node != parent) {
                dfs(node, cur, cur_depth+1);
                tout[cur] = tour.size();
                tour.emplace_back(cur_depth, cur);
            }
        }
    }

    void build(int root = 1) {
        dfs(root);
        st = sparseTable<pair<int, int>>(tour);
    }

    int lca(int x, int y) {
        int a = tin[x], b = tin[y];
        if (a > b) swap(a, b);
        return st.query(a, b).second;
    }

    int dist(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

    bool is_ancestor(int x, int y) {
        // Returns whether x is an ancestor of y
        return tin[x] <= tin[y] && tin[y] <= tout[x];
    }
};