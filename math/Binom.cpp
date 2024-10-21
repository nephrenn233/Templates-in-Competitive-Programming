constexpr int N = 1e5;
constexpr i64 P = 1e9 + 7;
typedef ModInt<P> Z;
Z fac[N + 10], ifac[N + 10];
void init () {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fac[i] = fac[i - 1] * Z(i);
    }
    ifac[N] = ModInt<P>::inv(fac[N]);
    for (int i = N - 1; i >= 0; --i) {
        ifac[i] = ifac[i + 1] * Z(i + 1);
    }
}
Z binom (int n, int m) {
    return fac[n] * ifac[m] * ifac[n - m];
}