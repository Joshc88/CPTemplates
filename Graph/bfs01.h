#include <bits/stdc++.h>
using namespace std;

template <bool directed = true> struct BFS01 { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<pair<int, int>>> edges;

    BFS01() {}

    BFS01(int N) {
        n = N;
        edges.resize(n+1);
    }

    void add_edge(int from, int to, int weight) {
        edges[from].emplace_back(to, weight);
        if (!directed) edges[to].emplace_back(from, weight);
    }

    vector<int> dist(vector<int> sources) {
        vector<int> res(n+1, -1);
        deque<int> q;
        for (int i : sources) {
            res[i] = 0;
            q.push_back(i);
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            for (auto [node, weight] : edges[cur]) {
                if (res[node] == -1 || res[node] > res[cur]+weight) {
                    res[node] = res[cur]+weight;
                    if (weight) q.push_back(node);
                    else q.push_front(node);
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
        deque<int> q;
        res[source] = 0;
        q.push_back(source);
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            for (auto [node, weight] : edges[cur]) {
                if (res[node] == -1 || res[node] > res[cur]+weight) {
                    res[node] = res[cur]+weight;
                    before[node] = cur;
                    if (weight) q.push_back(node);
                    else q.push_front(node);
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