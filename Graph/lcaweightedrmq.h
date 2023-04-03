#include <bits/stdc++.h>
using namespace std;

// Performs LCA on a weighted tree

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

template<class T = int> struct LCA { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<pair<int, T>>> edges;
    vector<int> depth, tin, tout;
    vector<pair<int, int>> tour;
    sparseTable<pair<int, int>> st;
    vector<T> distance;
    
    LCA() {}

    LCA(int N) {
        n = N+1;
        edges.resize(n);
        depth.resize(n);
        tin.resize(n);
        tout.resize(n);
        distance.resize(n);
    }

    void add_edge(int a, int b, T c) {
        edges[a].emplace_back(b, c);
        edges[b].emplace_back(a, c);
    }

    void dfs(int cur, int parent = -1, int cur_depth = 0, T cur_dist = 0) {
        tin[cur] = tout[cur] = tour.size();
        tour.emplace_back(cur_depth, cur);
        depth[cur] = cur_depth;
        distance[cur] = cur_dist;
        for (auto [node, length] : edges[cur]) {
            if (node != parent) {
                dfs(node, cur, cur_depth+1, cur_dist + length);
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

    T dist(int x, int y) {
        return distance[x] + distance[y] - 2 * distance[lca(x, y)];
    }

    bool is_ancestor(int x, int y) {
        // Returns whether x is an ancestor of y
        return tin[x] <= tin[y] && tin[y] <= tout[x];
    }

    // Returns a vector of nodes, and a vector of (parent, child) in virtual tree
    pair<vector<int>, vector<pair<int, int>>> virtual_tree(vector<int> nodes) {
        auto &&sort_by_preorder = [&](int a, int b) { return tin[a] < tin[b]; };
        sort(nodes.begin(), nodes.end(), sort_by_preorder);
        int sz = nodes.size();
        for (int i=0; i+1<sz; i++) nodes.push_back(lca(nodes[i], nodes[i+1]));
        sort(nodes.begin(), nodes.end(), sort_by_preorder);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> res;
        res.reserve(nodes.size() - 1);
        for (int i=1; i<nodes.size(); i++) res.emplace_back(lca(nodes[i-1], nodes[i]), nodes[i]);
        return make_pair(nodes, res);
    }
};