// 洛谷 P3369 【模板】 普通平衡树
struct FHQTreap
{
	struct FHQTreap_node
	{
		int ls, rs, key, val, sz;
	}tree[MAXN];
	int tot = 0;
	int root = 0, t1, t2, t3;

	int new_node(int v)
	{
		tree[++tot] = {0, 0, (int)rnd(), v, 1};
		return tot;
	}

	void push_up(int u)
	{
		tree[u].sz = tree[tree[u].ls].sz + tree[tree[u].rs].sz + 1;
	}

	void split_by_val(int u, int v, int &x, int &y)
	{
		if(!u)
		{
			x = y = 0;
			return;
		}

		if(tree[u].val > v)
		{
			y = u;
			split_by_val(tree[u].ls, v, x, tree[u].ls);
		}
		else
		{
			x = u;
			split_by_val(tree[u].rs, v, tree[u].rs, y);
		}

		push_up(u);
	}

	int merge(int x, int y)
	{
		if(!x || !y) return x + y;
		
		if(tree[x].key > tree[y].key)
		{
			tree[x].rs = merge(tree[x].rs, y);
			push_up(x);
			return x;
		}
		else
		{
			tree[y].ls = merge(x, tree[y].ls);
			push_up(y);
			return y;
		}
	}

	void insert(int v)
	{
		split_by_val(root, v, t1, t2);
		root = merge(merge(t1, new_node(v)), t2);
	}

	void erase(int v)
	{
		split_by_val(root, v, t1, t2);
		split_by_val(t1, v - 1, t1, t3);
		t3 = merge(tree[t3].ls, tree[t3].rs);
		root = merge(merge(t1, t3), t2);
	}

	int query_rnk(int v)
	{
		split_by_val(root, v - 1, t1, t2);
		int res = tree[t1].sz + 1;
		root = merge(t1, t2);
		return res;
	}
	
	int query_kth(int k)
	{
		int u = root;
		while(u)
		{
			int t = tree[tree[u].ls].sz + 1;
			if(t == k) break;
			else if(k < t) u = tree[u].ls;
			else
			{
				k -= t;
				u = tree[u].rs;
			}
		}
		return tree[u].val;
	}

	int query_pre(int u, int v)
	{
		if(!u) return -INF;
		if(tree[u].val < v)
		{
			int res = query_pre(tree[u].rs, v);
			return res == -INF ? tree[u].val : res;
		}
		else
		{
			return query_pre(tree[u].ls, v);
		}
	}

	int query_nxt(int u, int v)
	{
		if(!u) return INF;
		if(tree[u].val > v)
		{
			int res = query_nxt(tree[u].ls, v);
			return res == INF ? tree[u].val : res;
		}
		else
		{
			return query_nxt(tree[u].rs, v);
		}
	}
}Treap;