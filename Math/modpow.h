#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
 
long long power(int base, int exp = MOD-2) {
    if (!exp) return 1;
    long long res = power(base, exp>>1);
    res = (res*res)%MOD;
    if (exp&1) res = (res*base)%MOD;
    return res;
}