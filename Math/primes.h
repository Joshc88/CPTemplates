#include <bits/stdc++.h>
using namespace std;

struct Primes {
    vector<int> lpf, lpfcnt, primes, remaining;

    Primes(int n) {
        lpf.resize(n+1);
        lpfcnt.resize(n+1);
        remaining.resize(n+1);
        for (int i=2; i<=n; i++) {
            if (!lpf[i]) {
                lpf[i] = i;
                lpfcnt[i] = remaining[i] = 1;
                primes.push_back(i);
            }
            for (int j = 0; i * primes[j] <= n; j++) {
                int val = i * primes[j];
                lpf[val] = primes[j];
                lpfcnt[val] = lpfcnt[primes[j]] + (lpf[i] == primes[j] ? lpfcnt[i] : 0);
                remaining[val] = (lpf[i] == primes[j]) ? remaining[i] : i;
                if (primes[j] == lpf[i]) break;
            }
        }
    }

    bool isprime(long long x) {
        if (x < 2) return false;
        if (x < lpf.size()) return lpf[x] == x;
        for (long long i=2; i*i<=x; i++) {
            if (!(x%i)) return false;
        }
        return true;
    }

    vector<pair<int, int>> factorise(int x) {
        vector<pair<int, int>> factors;
        for (; x > 1; x = remaining[x]) factors.emplace_back(lpf[x], lpfcnt[x]);
        return factors;
    }
} primes(1e6);