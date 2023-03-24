#include <bits/stdc++.h>
using namespace std;

template <bool directed = true> struct BFS { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<int>> edges;

    BFS() {}

    BFS(int N) {
        n = N;
        edges.resize(n+1);
    }

    void add_edge(int from, int to) {
        edges[from].push_back(to);
        if (!directed) edges[to].push_back(from);
    }

    vector<int> dist(vector<int> sources) {
        vector<int> res(n+1, -1);
        queue<int> q;
        for (int i : sources) {
            res[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    q.push(i);
                }
            }
        }
        return res;
    }

    int dist(int source, int dest) {
        return dist({source})[dest];
    }

    pair<int, vector<int>> path(int source, int dest) {
        vector<int> res(n+1, -1);
        vector<int> before(n+1);
        queue<int> q;
        res[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    before[i] = cur;
                    q.push(i);
                }
            }
        }
        if (res[dest] == -1) return make_pair(-1, vector<int>());
        vector<int> path = {dest};
        while (path.back() != source) path.push_back(before[path.back()]);
        reverse(path.begin(), path.end());
        return make_pair(res[dest], path);
    }
};

template <bool oneindexed = true> struct TreeDiameter {
    BFS<false> graph;
    pair<int, int> endpoints = {oneindexed, oneindexed};
    int n, edges = 0, diameter = 0;
    
    TreeDiameter() {}

    TreeDiameter(int _n) : n(_n) {
        graph = BFS<false>(n);
    } 

    void add_edge(int x, int y) {
        graph.add_edge(x, y);
        if (++edges == n-1) {
            vector<int> dist1 = graph.dist({oneindexed});
            int node1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
            vector<int> dist2 = graph.dist({node1});
            int node2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
            diameter = dist2[node2];
            endpoints = {node1, node2};
        }
    }

    vector<int> path() {
        return graph.path(endpoints.first, endpoints.second).second;
    }

    int centre() {
        vector<int> p = path();
        return p[p.size()/2];
    }
};