int up = __lg(n) + 2;
vector<vector<int>> fa(n + 1, vector<int>(up + 1, 0));
vector<int> dep(n + 1, 0);

auto dfs = [&](auto &&self, int u, int f) -> void {
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = 1; i <= up; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(auto v : g[u]) {
        if(v == f) continue;
        self(self, v, u);
    }
};

auto query_lca = [&](int x, int y) -> int {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 0, d = dep[x] - dep[y]; d; d >>= 1, ++i) {
        if(d & 1) x = fa[x][i];
    }
    if(x == y) return x;
    for(int i = up; i >= 0; --i) {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
};

dfs(dfs, s, 0);
