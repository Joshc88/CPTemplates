#include <bits/stdc++.h>
using namespace std;

template <class T> struct edge {
    int node;
    T weight;

    edge() {}

    edge(int _node, T _weight) : node(_node), weight(_weight) {}
};

template <class T, bool directed = true> struct dijkstra { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<edge<T>>> edges;
    const T INF = numeric_limits<T>::max()/2;

    dijkstra() {}

    dijkstra(int N) {
        n = N;
        edges.resize(n+1);
    }

    void add_edge(int from, int to, T dist) {
        edges[from].emplace_back(to, dist);
        if (!directed) edges[to].emplace_back(from, dist);
    }

    vector<T> dist(vector<int> sources) {
        vector<T> res(n+1, INF);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        for (int source : sources) {
            res[source] = 0;
            pq.push({0, source});
        }
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            if (cur.first > res[cur.second]) continue;
            for (auto e : edges[cur.second]) {
                if (res[e.node] > cur.first + e.weight) {
                    res[e.node] = cur.first + e.weight;
                    pq.push({res[e.node], e.node});
                }
            }
        }
        for (int i=0; i<=n; i++) {
            if (res[i] == INF) res[i] = -1;
        }
        return res;
    }

    T dist(int source, int dest) {
        return dist({source})[dest];
    }

    pair<T, vector<int>> path(int source, int dest) {
        // Return the distance from source to dest, along with a shortest path
        vector<T> res(n+1, INF);
        vector<int> before(n+1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        res[source] = 0;
        pq.push({0, source});
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            if (cur.first > res[cur.second]) continue;
            for (auto e : edges[cur.second]) {
                if (res[e.node] > cur.first + e.weight) {
                    res[e.node] = cur.first + e.weight;
                    before[e.node] = cur.second;
                    pq.push({res[e.node], e.node});
                }
            }
        }
        if (res[dest] == INF) return make_pair(-1, vector<int>());
        vector<int> path = {dest};
        while (path.back() != source) path.push_back(before[path.back()]);
        reverse(path.begin(), path.end());
        return make_pair(res[dest], path);
    }
};