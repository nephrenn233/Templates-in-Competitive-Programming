int dfn[MAXN], low[MAXN], tt = 0;

int ans[MAXN], tot = 0;

void tarjan(int u, bool is_root) {
    int ch = 0;
    dfn[u] = low[u] = ++tt;
    for(auto v : g[u]) {
        if(!dfn[v]) {
            tarjan(v, 0);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u] && !is_root) ans[u] = 1;
            if(is_root) ++ch;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(is_root && ch >= 2) {
        ans[u] = 1;
    }
}