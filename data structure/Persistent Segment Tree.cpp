int n, q, a[MAXN];
int m, b[MAXN];

struct node
{
    LL sum, ls, rs;
}tree[MAXN << 5];
LL tot = 0, rt[MAXN];

void build_tree(LL &u, LL l, LL r)
{
    u = ++tot;
    if(l == r) return;
    LL mid = (l + r) >> 1;
    build_tree(tree[u].ls, l, mid);
    build_tree(tree[u].rs, mid + 1, r);
}

LL clone(LL u)
{
    tree[++tot] = tree[u];
    return tot;
}

LL modify(LL u, LL l, LL r, LL qp)
{
    u = clone(u);
    tree[u].sum += 1;
    if(l == r) return u;
    LL mid = (l + r) >> 1;
    if(qp <= mid) tree[u].ls = modify(tree[u].ls, l, mid, qp);
    else tree[u].rs = modify(tree[u].rs, mid + 1, r, qp);
    return u;
}

LL query(LL u, LL v, LL l, LL r, LL k)
{
    if(l == r) return l;
    LL x = tree[tree[v].ls].sum - tree[tree[u].ls].sum;
    LL res = 0, mid = (l + r) >> 1;
    if(x >= k) res = query(tree[u].ls, tree[v].ls, l, mid, k);
    else res = query(tree[u].rs, tree[v].rs, mid + 1, r, k - x);
    return res;
}