#include <bits/stdc++.h>
using namespace std;

struct LCA { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<int>> jump;
    vector<vector<int>> edges;
    vector<int> depth;
    
    LCA() {}

    LCA(int N) {
        n = N+1;
        jump = vector<vector<int>>(__lg(n-1)+1, vector<int>(n));
        edges.resize(n);
        depth.resize(n);
    }

    void add_edge(int a, int b) {
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void dfs(int cur, int parent = -1, int cur_depth = 0) {
        depth[cur] = cur_depth;
        jump[0][cur] = parent;
        for (int i=1; i<jump.size(); i++) jump[i][cur] = jump[i-1][cur] == -1 ? -1 : jump[i-1][jump[i-1][cur]];
        for (int node : edges[cur]) {
            if (node != parent) dfs(node, cur, cur_depth+1);
        }
    }

    void build(int root = 1) {
        dfs(root);
    }

    int ancestor(int node, int k) { // find k-th ancestor of node
        for (int i=0; i<jump.size(); i++) {
            if ((k&(1<<i)) && node != -1) node = jump[i][node];
        }
        return node;
    }

    int lca(int x, int y) {
        if (depth[x] < depth[y]) swap(x, y);
        x = ancestor(x, depth[x]-depth[y]);
        if (x == y) return x;
        for (int i=jump.size()-1; i>=0; i--) {
            if (jump[i][x] != jump[i][y]) {
                x = jump[i][x];
                y = jump[i][y];
            }
        }
        return jump[0][x];
    }

    int dist(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

    int find_on_path(int x, int y, int k) {
        // Find the k-th (1-indexed) node on the path from x to y
        // Return -1 if no node exists
        int l = lca(x, y);
        int d = depth[x] + depth[y] - 2 * depth[l];
        if (k > d+1) return -1;
        if (depth[x] - depth[l] >= k) return ancestor(x, k-1);
        return ancestor(y, d-k+1);
    }
};