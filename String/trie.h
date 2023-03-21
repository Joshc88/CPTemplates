#include <bits/stdc++.h>
using namespace std;

template<char MIN_CHAR = 'a', int ALPHABET = 26> struct trie {
    vector<array<int, ALPHABET>> nodes = vector<array<int, ALPHABET>>(1);
    vector<int> prefix_of = {0}, ends_here = {0};

    trie(int elements = -1) { 
        if (elements >= 0) {
            nodes.reserve(elements * ALPHABET);
            prefix_of.reserve(elements * ALPHABET);
            ends_here.reserve(elements * ALPHABET);
        }
    }

    void update(string s, int delta) {
        int node = 0;
        for (char c : s) {
            int cur = c - MIN_CHAR;
            if (!nodes[node][cur]) {
                nodes[node][cur] = nodes.size();
                nodes.push_back(array<int, ALPHABET>());
                prefix_of.push_back(0);
                ends_here.push_back(0);
            }
            node = nodes[node][cur];
            prefix_of[node] += delta;
        }
        ends_here[node] += delta;
    }

    void insert(string s) {
        update(s, 1);
    }  

    void erase(string s) {
        update(s, -1);
    }

    int count(string s) {
        int node = 0;
        for (char c : s) {
            int cur = c - MIN_CHAR;
            if (nodes[node][cur] && prefix_of[nodes[node][cur]]) node = nodes[node][cur];
            else return 0;
        }
        return ends_here[node];
    }

    int prefix(string s) {
        int node = 0, res = 0;
        for (char c : s) {
            int cur = c - MIN_CHAR;
            if (nodes[node][cur] && prefix_of[nodes[node][cur]]) node = nodes[node][cur];
            else break;
            res += ends_here[node];
        }
        return res;
    }

    int startswith(string s) {
        int node = 0;
        for (char c : s) {
            int cur = c - MIN_CHAR;
            if (nodes[node][cur] && prefix_of[nodes[node][cur]]) node = nodes[node][cur];
            else return 0;
        }
        return prefix_of[node];
    }
};