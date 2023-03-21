#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1000000007;
 
ll power(int base, int exp = MOD-2) {
    if (!exp) return 1;
    ll res = power(base, exp>>1);
    res = (res*res)%MOD;
    if (exp&1) res = (res*base)%MOD;
    return res;
}