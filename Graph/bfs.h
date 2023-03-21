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