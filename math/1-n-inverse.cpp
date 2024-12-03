const int N = 1e5, P = 998244353;
int inv[N + 10];
inv[1] = 1;
for (int i = 2; i <= n; ++i) {
    inv[i] = (P - P / i) * inv[P % i] % P;
}