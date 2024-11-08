LL n, q, s;
vector<LL> g[MAXN];

LL dep[MAXN], sz[MAXN], mxson[MAXN], fa[MAXN];
void dfs1(LL u, LL f)
{
	dep[u] = dep[f] + 1;
	sz[u] = 1;
	fa[u] = f;

	LL tt = -1;
	for(LL v : g[u])
	{
		if(v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];

		if(sz[v] > tt)
		{
			tt = sz[v];
			mxson[u] = v;
		}
	}
}

LL top[MAXN], id[MAXN], tot;
void dfs2(LL u, LL f)
{
	top[u] = f;
	id[u] = ++tot;

	if(mxson[u] == 0) return;

	dfs2(mxson[u], f);

	for(LL v : g[u])
	{
		if(v == mxson[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

void solve()
{
	cin >> n >> q >> s;
	for(LL i = 1, u = 0, v = 0; i <= n - 1; ++i)
	{
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs1(s, 0);
	dfs2(s, s);

	while(q--)
	{
		LL u, v;
		cin >> u >> v;

		while(top[u] != top[v])
		{
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}

		if(dep[u] < dep[v]) cout << u << "\n";
		else cout << v << "\n";
	}
}