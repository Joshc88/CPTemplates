#include <bits/stdc++.h>
using namespace std;

template<typename T, bool R = true, bool LEFT_HASH = true>
struct hashes {
    mt19937 rng;
    const static int MOD = 1e9 + 7;
    static int global_base1, global_base2;
    static vector<long long> powers1, inv_powers1, powers2, inv_powers2;
    vector<long long> psa;

    hashes(T& s, int b = 131) : rng(chrono::steady_clock::now().time_since_epoch().count()), psa{0} {
        int& chosen_base = LEFT_HASH ? global_base1 : global_base2;
        vector<long long> &powers = LEFT_HASH ? powers1 : powers2,
            &inv_powers = LEFT_HASH ? inv_powers1 : inv_powers2;
        if (!chosen_base) {
            chosen_base = R ? uniform_int_distribution<int>(200, MOD - 1)(rng) : b;
            long long cur = chosen_base, inv = 1;
            for (int exp = MOD - 2; exp; exp >>= 1) {
                if (exp & 1) inv = inv * cur % MOD;
                cur = cur * cur % MOD;
            }
            powers.push_back(chosen_base);
            inv_powers.push_back(inv);
        }
        while (powers.size() < s.size()) {
            powers.push_back(powers.back() * chosen_base % MOD);
            inv_powers.push_back(inv_powers.back() * inv_powers[1] % MOD);
        }
        for (int i = 0; i < s.size(); i++) psa.push_back((psa.back() + s[i] * (LEFT_HASH ? powers1 : powers2)[i]) % MOD);
    }

    hashes() {}

    long long get(int l, int r) {
        return (psa[r + 1] - psa[l] + MOD) * (LEFT_HASH ? inv_powers1 : inv_powers2)[l] % MOD;
    }
};

template<typename T, bool R, bool LEFT_HASH> int hashes<T, R, LEFT_HASH>::global_base1 = 0;
template<typename T, bool R, bool LEFT_HASH> int hashes<T, R, LEFT_HASH>::global_base2 = 0;
template<typename T, bool R, bool LEFT_HASH> vector<long long> hashes<T, R, LEFT_HASH>::powers1 = {1};
template<typename T, bool R, bool LEFT_HASH> vector<long long> hashes<T, R, LEFT_HASH>::powers2 = {1};
template<typename T, bool R, bool LEFT_HASH> vector<long long> hashes<T, R, LEFT_HASH>::inv_powers1 = {1};
template<typename T, bool R, bool LEFT_HASH> vector<long long> hashes<T, R, LEFT_HASH>::inv_powers2 = {1};

template<typename T, bool R = true> 
struct double_hash {
    hashes<T, R, true> hash1;
    hashes<T, R, false> hash2;

    double_hash(T& s, int base1 = 131, int base2 = 173) : hash1(hashes<T, R, true>(s, base1)),
                                                                             hash2(hashes<T, R, false>(s, base2)) {}
    double_hash() {}

    long long get(int l, int r) {
        return (hash1.get(l, r) << 32) | hash2.get(l, r);
    }
};