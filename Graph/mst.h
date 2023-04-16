#include <bits/stdc++.h>
using namespace std;

// Source: https://github.com/atcoder/ac-library

struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

template <class T, bool oneindexed = true> struct MST {
    int n;
    vector<pair<T, pair<int, int>>> chosen;
    vector<pair<T, pair<int, int>>> edges;
    dsu d;

    MST() {}

    MST(int N) {
        n = N;
        edges.reserve(n);
        d = dsu(n+1);
    }

    void add_edge(int x, int y, T z) {
        edges.push_back({z, {x, y}});
    }

    T mst() {
        sort(edges.begin(), edges.end());
        T res = 0;
        for (auto edge : edges) {
            if (!d.same(edge.second.first, edge.second.second)) {
                chosen.push_back(edge);
                res += edge.first;
                d.merge(edge.second.first, edge.second.second);
            }
        }
        return (d.size(oneindexed) == n) ? res : -1;
    }
};