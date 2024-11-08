int n, m, a[MAXN];

struct node
{
    int ls, rs, val;
}tree[MAXN << 5];
int rt[MAXN], tot = 0;

int build_tree(int u, int l, int r)
{
    u = ++tot;
    if(l == r)
    {
        tree[u].val = INF;
        return u;
    }
    int mid = (l + r) >> 1;
    tree[u].ls = build_tree(tree[u].ls, l, mid);
    tree[u].rs = build_tree(tree[u].rs, mid + 1, r);
    return u;
}

void push_up(int u)
{
    tree[u].val = min(tree[tree[u].ls].val, tree[tree[u].rs].val);
}

int modify(int u, int l, int r, int qp, int k)
{
    tree[++tot] = tree[u];
    u = tot;
    if(l == r)
    {
        tree[u].val = k;
        return u;
    }
    int mid = (l + r) >> 1;
    if(qp <= mid) tree[u].ls = modify(tree[u].ls, l, mid, qp, k);
    else tree[u].rs = modify(tree[u].rs, mid + 1, r, qp, k);
    push_up(u);
    return u;
}

int query(int u, int l, int r, int x)
{
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(tree[tree[u].ls].val < x) return query(tree[u].ls, l, mid, x);
    else return query(tree[u].rs, mid + 1, r, x);
}

void solve()
{
    cin >> n >> m;
    // rt[0] = build_tree(rt[0], 0, N);
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        rt[i] = modify(rt[i - 1], 0, N, a[i], i);
    }
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(rt[r], 0, N, l) << "\n";
    }
}