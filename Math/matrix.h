#include <bits/stdc++.h>
using namespace std;

using matrix = vector<vector<long long>>;
const int MOD = 1e9 + 7;

matrix multiply(matrix a, matrix b) {
    matrix res(a.size(), vector<long long>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD; 
        }
    }
    return res;
}

matrix eye(int n) {
    matrix res(n, vector<long long>(n));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    return res;
}

matrix pow(matrix base, long long exp) {
    matrix res = eye(base.size()), cur = base;
    for (; exp; exp >>= 1) {
        if (exp & 1) res = multiply(res, cur);
        cur = multiply(cur, cur);
    }
    return res;
}

void print(matrix a) {
    for (auto& row : a) {
        for (int i = 0; i < row.size(); i++) printf("%lld%c", row[i], " \n"[i + 1 == row.size()]);
    }
}

// @param base {V(0), V(1), ..., V(N-1)}
// @param coefficients V(X) = V(X-1) * coefficients[0] + V(X-2) * coefficients[1] ...
long long linear(vector<long long> base, vector<long long> coefficients, long long k) {
    int n = base.size();
    if (k < n) return base[k];
    matrix transition(n, vector<long long>(n));
    for (int i = 0; i < n - 1; i++) transition[i + 1][i] = 1;
    for (int i = 0; i < n; i++) transition[i][n - 1] = coefficients[n - i - 1];
    return multiply({base}, pow(transition, k - n + 1))[0][n - 1];
}