#include <bits/stdc++.h>
using namespace std;

vector<string> split(string s, char delim = ' ') {
    vector<string> res;
    string cur;
    for (char c : s) {
        if (c == delim) {
            res.push_back(cur);
            cur.clear();
        } else cur += c;
    }
    res.push_back(cur);
    return res;
}