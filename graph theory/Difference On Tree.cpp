// 边差分
d[u] += 1, d[v] += 1;
d[lca(u, v)] -= 2;

// 点差分
d[u] += 1, d[v] += 1;
d[lca(u, v)] -= 1;
d[fa[lca(u, v)]] -= 1;