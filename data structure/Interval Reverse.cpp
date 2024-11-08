std::random_device seed;
std::mt19937 rnd(seed());

int n, q;

struct node
{
	int sz, key, val, ls, rs, lazy;
}tree[MAXN];
int rt, tot, t1, t2, t3;

int new_node(int v)
{
	tree[++tot] = {1, int(rnd()), v, 0, 0, 0};
	return tot;
}

void push_up(int u)
{
	tree[u].sz = tree[tree[u].ls].sz + tree[tree[u].rs].sz + 1;
}

void push_down(int u)
{
	if(tree[u].lazy)
	{
		std::swap(tree[u].ls, tree[u].rs);
		if(tree[u].ls) tree[tree[u].ls].lazy ^= 1;
		if(tree[u].rs) tree[tree[u].rs].lazy ^= 1;
		tree[u].lazy = 0;
	}
}

void split_by_rnk(int u, int k, int &x, int &y)
{
	if(!u)
	{
		x = y = 0;
		return;
	}
	int t = tree[tree[u].ls].sz + 1;
	push_down(u);

	if(tree[tree[u].ls].sz + 1 <= k)
	{
		x = u;
		split_by_rnk(tree[u].rs, k - tree[tree[u].ls].sz - 1, tree[u].rs, y);
	}
	else
	{
		y = u;
		split_by_rnk(tree[u].ls, k, x, tree[u].ls);
	}

	push_up(u);
}

int merge(int x, int y)
{
	if(!x || !y) return x + y;

	if(tree[x].key > tree[y].key)
	{
		push_down(x);
		tree[x].rs = merge(tree[x].rs, y);
		push_up(x);
		return x;
	}
	else
	{
		push_down(y);
		tree[y].ls = merge(x, tree[y].ls);
		push_up(y);
		return y;
	}
}

void dfs(int u)
{
	if(!u) return;
	push_down(u);
	dfs(tree[u].ls);
	std::cout << tree[u].val << " ";
	dfs(tree[u].rs);
}

void solve()
{
	std::cin >> n >> q;
	for(int i = 1; i <= n; ++i)
	{
		rt = merge(rt, new_node(i));
	}

	while(q--)
	{
		int l, r;
		std::cin >> l >> r;
		split_by_rnk(rt, r, t1, t2);
		split_by_rnk(t1, l - 1, t1, t3);
		tree[t3].lazy ^= 1;
		rt = merge(merge(t1, t3), t2);
	}

	dfs(rt);
}