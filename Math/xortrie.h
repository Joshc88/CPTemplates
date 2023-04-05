#include <bits/stdc++.h>
using namespace std;

template<class T = int, int NUM_BITS = 31> struct xortrie {
    vector<array<int, 2>> trie = {{0, 0}};
    vector<int> cnt = {0};

    xortrie() {}

    xortrie(int bits, int elements = -1) {
        NUM_BITS = bits;
        if (elements != -1) {
            trie.reserve(elements*bits);
            cnt.reserve(elements*bits);
        }
    }

    void update(T val, int delta) {
        int node = 0;
        for (int i = NUM_BITS-1; i>=0; i--) {
            int c = val&(1ll<<i) ? 1 : 0;
            if (!trie[node][c]) {
                trie[node][c] = trie.size();
                trie.push_back({0, 0});
                cnt.push_back(0);
            }
            node = trie[node][c];
            cnt[node] += delta;
        }
    }

    void insert(T val) {
        update(val, 1);
    }

    void erase(T val) {
        update(val, -1);
    }

    T max(T val) { 
        // Find max of val XOR element
        T res = 0;
        int node = 0;
        for (int i = NUM_BITS-1; i>=0; i--) {
            int c = val&(1ll<<i) ? 0 : 1;
            if (trie[node][c] && cnt[trie[node][c]]) {
                res ^= 1ll << i;
                node = trie[node][c];
            } else node = trie[node][c^1];
        }
        return res;
    }

    T min(T val) { 
        // Find min of val XOR element
        T res = 0;
        int node = 0;
        for (int i = NUM_BITS-1; i>=0; i--) {
            int c = val&(1ll<<i) ? 1 : 0;
            if (trie[node][c] && cnt[trie[node][c]]) node = trie[node][c];
            else {
                res ^= 1ll << i;
                node = trie[node][c^1];
            }
        }
        return res;
    }

    int less_than(T val, T limit) { 
        // How many elements satisfy val XOR element < limit ?
        int res = 0, node = 0;
        for (int i = NUM_BITS-1; i>=0; i--) {
            int c = val&(1ll<<i) ? 1 : 0;
            if (limit&(1ll<<i)) {
                res += cnt[trie[node][c]];
                if (trie[node][c^1] && cnt[trie[node][c^1]]) node = trie[node][c^1];
                else break;
            } else {
                if (trie[node][c] && cnt[trie[node][c]]) node = trie[node][c];
                else break;
            }
        }
        return res;
    }
};