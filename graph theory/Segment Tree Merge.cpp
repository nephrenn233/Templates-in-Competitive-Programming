#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const int MAXM = MAXN * 60;

int n, m;
vector<int> g[MAXN];

int fa[MAXN][22], dep[MAXN];

void dfs1(int u) {
    for(int i = 0; fa[u][i]; ++i) fa[u][i + 1] = fa[fa[u][i]][i];
    dep[u] = dep[fa[u][0]] + 1;
    for(auto v : g[u]) {
        if(v == fa[u][0]) continue;
        fa[v][0] = u;
        dfs1(v);
    }
}

int query_lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int d = dep[u] - dep[v], i = 0; d; d >>= 1, ++i) {
        if(d & 1) u = fa[u][i];
    }
    if(u == v) return u;
    for(int i = 18; i >= 0; --i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int rt[MAXN], ls[MAXM], rs[MAXM], sum[MAXM], typ[MAXM], tot = 0, rR = 0;

void push_up(int u) {
    if(!ls[u] || !rs[u]) {
        sum[u] = sum[ls[u]] + sum[rs[u]];
        typ[u] = typ[ls[u]] + typ[rs[u]];
    } else {
        if(sum[ls[u]] >= sum[rs[u]]) {
            sum[u] = sum[ls[u]];
            typ[u] = typ[ls[u]];
        } else {
            sum[u] = sum[rs[u]];
            typ[u] = typ[rs[u]];
        }
    }
}

int modify(int u, int l, int r, int qp, int k) {
    if(!u) u = ++tot;
    if(l == r) {
        sum[u] += k;
        typ[u] = l;
        return u;
    }
    int mid = (l + r) >> 1;
    if(qp <= mid) ls[u] = modify(ls[u], l, mid, qp, k);
    else rs[u] = modify(rs[u], mid + 1, r, qp, k);
    push_up(u);
    return u;
}

int merge(int u, int v, int l, int r) {
    if(!u || !v) return u + v;
    if(l == r) {
        sum[u] += sum[v];
        typ[u] = l;
        return u;
    }
    int mid = (l + r) >> 1;
    ls[u] = merge(ls[u], ls[v], l, mid);
    rs[u] = merge(rs[u], rs[v], mid + 1, r);
    push_up(u);
    return u;
}

struct query {
    int x, y, z;
} q[MAXN];
int ans[MAXN];

void solve(int u, int f) {
    for(auto v : g[u]) {
        if(v == f) continue;
        solve(v, u);
        rt[u] = merge(rt[u], rt[v], 1, rR);
    }
    if(sum[rt[u]]) ans[u] = typ[rt[u]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1);

    for(int i = 1; i <= m; ++i) {
        cin >> q[i].x >> q[i].y >> q[i].z;
        rR = max(rR, q[i].z);
    }

    for(int i = 1; i <= m; ++i) {
        auto [x, y, z] = q[i];
        int lca = query_lca(x, y);
        rt[x] = modify(rt[x], 1, rR, z, 1);
        rt[y] = modify(rt[y], 1, rR, z, 1);
        rt[lca] = modify(rt[lca], 1, rR, z, -1);
        if(fa[lca][0]) rt[fa[lca][0]] = modify(rt[fa[lca][0]], 1, rR, z, -1);
    }

    solve(1, 0);

    for(int i = 1; i <= n; ++i) cout << ans[i] << "\n";
}