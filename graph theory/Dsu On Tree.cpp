int n, a[MAXN];
std::vector<int> g[MAXN];
 
int sz[MAXN], mxson[MAXN];
 
void dfs(int u, int f) {
    sz[u] = 1;
 
    int mx = -1;
    for(auto v : g[u]) {
        if(v == f) continue;
        dfs(v, u);
        sz[u] += sz[v];
 
        if(sz[v] > mx) {
            mx = sz[v];
            mxson[u] = v;
        }
    }
}
 
i64 cnt[MAXN], ans[MAXN], sum, mx, tmp;
 
void calc(int u, int f, int k) {
    cnt[a[u]] += k;
    if(cnt[a[u]] > mx) {
        mx = cnt[a[u]];
        sum = a[u];
    } else if(cnt[a[u]] == mx) {
        sum += a[u];
    }
    for(auto v : g[u]) {
        if(v == f || v == tmp) continue;
        calc(v, u, k); 
    }
}
 
void dsu(int u, int f, int keep) {
    for(auto v : g[u]) {
        if(v == f || v == mxson[u]) continue;
        dsu(v, u, 0);
    }
    if(mxson[u]) {
        dsu(mxson[u], u, 1);
        tmp = mxson[u];
    }
    calc(u, f, 1);
    tmp = 0;
    ans[u] = sum;
    if(!keep) {
        calc(u, f, -1);
        sum = mx = 0;
    }
}
 
void solve () {
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> a[i];
    for(int i = 1; i <= n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    dfs(1, 0);
    dsu(1, 0, 0);
    for(int i = 1; i <= n; ++i) {
        std::cout << ans[i] << " ";
    }
}