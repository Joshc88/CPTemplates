#include <bits/stdc++.h>
using namespace std;

struct hashes {
    int base, mod, sz;
    vector<long long> powers = {1}, psa = {0};

    hashes(string s, int m = 1000000007, int b = 131) {
        sz = s.size();
        base = b;
        mod = m;
        for (int i=0; i<s.size(); i++) {
            powers.push_back(powers.back()*base%mod);
            psa.push_back((psa.back()+s[i]*powers[i])%mod);
        }
    }

    hashes() {}
    
    long long get(int l, int r) {
        return (psa[r+1]-psa[l]+mod)*powers[sz-r]%mod;
    }
};

struct doublehash {
    hashes hash1, hash2;
    
    doublehash(string S, int mod1 = 1000000007, int mod2 = 998244353) {
        hash1 = hashes(S, mod1);
        hash2 = hashes(S, mod2);
    }
    
    pair<long long, long long> get(int l, int r) {
        return make_pair(hash1.get(l, r), hash2.get(l, r));
    }
};
