#include <bits/stdc++.h>
using namespace std;

struct hashes {
    int base, inv, mod, sz;
    vector<long long> powers = {1}, invpowers = {1}, psa = {0};

    hashes(string s, int m = 1000000007, int b = 131) {
        sz = s.size();
        base = b;
        mod = m;

        inv = 1;
        long long cur = base;
        int exp = m - 2;
        for (int exp=m-2; exp; exp>>=1) {
            if (exp&1) inv = inv * cur % m;
            cur = cur * cur % m;
        }

        for (int i=0; i<s.size(); i++) {
            powers.push_back(powers.back()*base%mod);
            invpowers.push_back(invpowers.back()*inv%mod);
            psa.push_back((psa.back()+s[i]*powers[i])%mod);
        }
    }

    hashes() {}
    
    long long get(int l, int r) {
        return (psa[r+1]-psa[l]+mod)*invpowers[l]%mod;
    }
};

struct doublehash {
    hashes hash1, hash2;
    
    doublehash(string S, int base1 = 131, int base2 = 149, int mod1 = 1000000007, int mod2 = 998244353) {
        hash1 = hashes(S, mod1, base1);
        hash2 = hashes(S, mod2, base2);
    }
    
    pair<long long, long long> get(int l, int r) {
        return make_pair(hash1.get(l, r), hash2.get(l, r));
    }
};