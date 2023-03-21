#include <bits/stdc++.h>
using namespace std;

template <bool directed, bool oneindexed = true> struct euler {
    vector<vector<pair<int, int>>> edges;
    vector<int> deg;
    int n, curedge = 0;

    euler() {}

    euler(int N) {
        n = N;
        edges.resize(n);
        deg.resize(n);
    }

    void add_edge(int x, int y) {
        x -= oneindexed;
        y -= oneindexed;
        edges[x].emplace_back(y, curedge);
        if (!directed) edges[y].emplace_back(x, curedge);
        deg[x]--;
        deg[y]++;
        curedge++;
    }

    vector<int> path(int s = -1, int t = -1) {
        vector<bool> used(curedge+1);
        if (s != -1) s -= oneindexed;
        if (t != -1) t -= oneindexed;
        vector<int> res;
        if (directed) {
            int start = -1, end = -1;
            for (int i=0; i<n; i++) {
                if (deg[i] == -1 && start == -1) start = i; 
                else if (deg[i] == 1 && end == -1) end = i;
                else if (deg[i]) return res;
            }
            if (start >= 0) {
                if ((s != -1 && s != start) || (t != -1 && t != end)) return res;
                s = start;
                t = end;
            } else {
                if (s >= 0 && t >= 0 && s != t) return res;
                else if (s >= 0) t = s;
                else if (t >= 0) s = t; 
                else s = t = 0;
            }
        } else {
            vector<int> odd;
            for (int i=0; i<n; i++) {
                if (deg[i]%2) odd.push_back(i);
            }
            if (!(odd.empty() || odd.size() == 2)) return res;
            if (odd.empty()) {
                if (s >= 0 && t >= 0 && s != t) return res;
                else if (s >= 0) t = s;
                else if (t >= 0) s = t; 
                else s = t = 0;
            } else {
                if ((s == -1 || s == odd[0]) && (t == -1 || t == odd[1])) {
                    s = odd[0];
                    t = odd[1];
                } else if ((s == -1 || s == odd[1]) && (t == -1 || t == odd[0])) {
                    s = odd[1];
                    t = odd[0];
                } else return res;
            }
        }
        if (s != t) {
            edges[t].emplace_back(s, curedge);
            if (!directed) edges[s].emplace_back(t, curedge);
        }
        stack<int> st;
        st.push(s);
        while (!st.empty()) {
            int v = st.top();
            while (!edges[v].empty() && used[edges[v].back().second]) edges[v].pop_back();

            if (edges[v].empty()) {
                res.push_back(v);
                st.pop();
            } else {
                auto [u, edge] = edges[v].back();
                edges[v].pop_back();
                used[edge] = true;
                st.push(u);
            }
        }
        for (int i=0; i<n; i++) {
            if (!edges[i].empty()) return vector<int>();
        }
        reverse(res.begin(), res.end());
        if (s != t) {
            for (int i=0; i+1<res.size(); i++) {
                if ((res[i] == t && res[i+1] == s) || (!directed && res[i] == s && res[i+1] == t)) {
                    vector<int> res2;
                    for (int j=i+1; j+1<res.size(); j++) res2.push_back(res[j]);
                    for (int j=0; j<=i; j++) res2.push_back(res[j]);
                    res = res2;
                    break;
                }
            }
        }
        if (s != res[0]) reverse(res.begin(), res.end());
        if (oneindexed) {
            for (int& i : res) i++;
        }
        return res;
    }
};