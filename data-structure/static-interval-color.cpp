int n, a[MAXN], q;

int last[MAXN], nxt[MAXN];

struct node
{
	int ls, rs, val;
}tree[MAXN << 5];
int rt[MAXN], tot = 0;

int modify(int u, int l, int r, int x)
{
	tree[++tot] = tree[u];
	u = tot;
	tree[u].val += 1;

	if(l == r) return u;
	int mid = (l + r) >> 1;
	if(x <= mid) tree[u].ls = modify(tree[u].ls, l, mid, x);
	else tree[u].rs = modify(tree[u].rs, mid + 1, r, x);
	return u;
}

int query(int u, int v, int l, int r, int x)
{
	if(l == r) return tree[v].val - tree[u].val;
	int mid = (l + r) >> 1;
	if(x <= mid) return query(tree[u].ls, tree[v].ls, l, mid, x) + tree[tree[v].rs].val - tree[tree[u].rs].val;
	else return query(tree[u].rs, tree[v].rs, mid + 1, r, x);
}

void solve()
{
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];

	fill(nxt + 1, nxt + 1 + n, n + 1);
	for(int i = 1; i <= n; ++i)
	{
		if(last[a[i]]) nxt[last[a[i]]] = i;
		last[a[i]] = i;
	}

	for(int i = 1; i <= n; ++i)
	{
		rt[i] = modify(rt[i - 1], 1, n + 1, nxt[i]);
	}

	cin >> q;
	while(q--)
	{
		int l, r;
		cin >> l >> r;
		cout << query(rt[l - 1], rt[r], 1, n + 1, r + 1) << "\n";
	}
}