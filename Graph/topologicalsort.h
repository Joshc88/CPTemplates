#include <bits/stdc++.h>
using namespace std;

template <bool oneindexed = true> struct topsort {
    vector<vector<int>> edges;
    vector<int> indeg;
    int n;

    topsort() {}

    topsort(int N) {
        n = N;
        edges.resize(n);
        indeg.resize(n);
    }

    void add_edge(int x, int y) {
        edges[x-oneindexed].push_back(y-oneindexed);
        indeg[y-oneindexed]++;
    }

    vector<int> order() {
        // Return a topological ordering, or an empty vector if there is none
        vector<int> res, cur;
        for (int i=0; i<n; i++) {
            if (indeg[i] == 0) cur.push_back(i);
        }
        while (!cur.empty()) {
            int node = cur.back();
            cur.pop_back();
            res.push_back(node+oneindexed);
            for (int i : edges[node]) {
                if (--indeg[i] == 0) cur.push_back(i);
            }
        }
        if (res.size() < n) res.clear();
        return res;
    }

    vector<int> minorder() {
        // Return the lexicographically minimal topological ordering, or an empty vector if there is none
        vector<int> res;
        priority_queue<int, vector<int>, greater<int>> cur;
        for (int i=0; i<n; i++) {
            if (indeg[i] == 0) cur.push(i);
        }
        while (!cur.empty()) {
            int node = cur.top();
            cur.pop();
            res.push_back(node+oneindexed);
            for (int i : edges[node]) {
                if (--indeg[i] == 0) cur.push(i);
            }
        }
        if (res.size() < n) res.clear();
        return res;
    }

    vector<int> maxorder() {
        // Return the lexicographically maximal topological ordering, or an empty vector if there is none
        vector<int> res;
        priority_queue<int> cur;
        for (int i=0; i<n; i++) {
            if (indeg[i] == 0) cur.push(i);
        }
        while (!cur.empty()) {
            int node = cur.top();
            cur.pop();
            res.push_back(node+oneindexed);
            for (int i : edges[node]) {
                if (--indeg[i] == 0) cur.push(i);
            }
        }
        if (res.size() < n) res.clear();
        return res;
    }
};