#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

long long mul(long long a, long long b) {
    return a * b % MOD;
}

long long power(long long base, long long exp = MOD-2) {
    long long res = 1, y = base;
    while (exp) {
        if (exp&1) res = mul(res, y);
        y = mul(y, y);
        exp >>= 1;
    }
    return res;
}

struct Math {
    vector<long long> fact, inv;
    
    Math(int n = 1) {
        fact.resize(n+1);
        inv.resize(n+1);
        fact[0] = inv[0] = 1;
        for (int i=1; i<=n; i++) fact[i] = mul(fact[i-1], i);
        inv[n] = power(fact[n]);
        for (int i=n; i>1; i--) inv[i-1] = mul(inv[i], i);
    }

    long long comb(int n, int k) {
        return mul(mul(fact[n], inv[k]), inv[n-k]);
    }

    long long perm(int n, int k) {
        return mul(fact[n], inv[n-k]);
    }
    
    long long multi(vector<int> v) {
        long long res = fact[accumulate(v.begin(), v.end(), 0)];
        for (int i : v) res = mul(res, inv[i]);
        return res;
    }

} math(100005); 