int dep[N], sz[N], mxson[N], fa[N];
void dfs1(int u, int f)
{
	dep[u] = dep[f] + 1;
	sz[u] = 1;
	fa[u] = f;

	int mx = -1;
	for(int v : g[u])
	{
		if(v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];

		if(sz[v] > mx)
		{
			mx = sz[v];
			mxson[u] = v;
		}
	}
}

int top[N], id[N], mp[N], tot;
void dfs2(int u, int f)
{
	top[u] = f;
	id[u] = ++tot;
	mp[tot] = u;

	if(mxson[u] == 0) return;

	dfs2(mxson[u], f);

	for(int v : g[u])
	{
		if(v == mxson[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}


// 操作
while(top[x] != top[y])
{
	if(dep[top[x]] < dep[top[y]]) swap(x, y);
	modify(1, 1, n, id[top[x]], id[x], z);
	x = fa[top[x]];
}
if(dep[x] > dep[y]) swap(x, y);
modify(1, 1, n, id[x], id[y], z);

// 如果是边权的话，把边权下放到子节点上，并且改为
modify(1, 1, n, id[x] + 1, id[y], 1);
query(1, 1, n, id[x] + 1, id[y]);
