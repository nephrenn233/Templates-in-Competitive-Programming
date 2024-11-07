const int MAXN = 1e5 + 10, N = 1e5;
int lg[MAXN];
void init () {
    lg[1] = 0;
    for (int i = 2; i <= N; ++i) lg[i] = lg[i / 2] + 1;
}

void build_st () {
    for (int i = 1; i <= n; ++i) st[i][0] = a[i];
    for (int j = 1; j <= lg[n]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query (int l, int r) {
    int s = lg[r - l + 1];
    return std::max(st[l][s], st[r - (1 << s) + 1][s]);
}