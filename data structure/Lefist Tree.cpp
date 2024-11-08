struct node
{
    int fa, lt, rt, val, dist;
}ltree[MAXN];

int n, m;
int opt, x, y;

int find(int x)
{
    return (fa(x) == x ? x : fa(x) = find(fa(x)));
}

int merge(int x, int y)
{
    if(!x | !y) return x | y; // 空结点

    if(val(x) > val(y)) swap(x, y);

    rs(x) = merge(rs(x), y);

    // 维护左偏树性质
    if(dist(ls(x)) < dist(rs(x))) swap(ls(x), rs(x));

    // 维护dist和并查集
    dist(x) = dist(rs(x)) + 1;
    fa(ls(x)) = fa(rs(x)) = fa(x) = x;

    return x;
}

void pop(int x)
{
    val(x) = -1;
    fa(ls(x)) = ls(x);
    fa(rs(x)) = rs(x);
    fa(x) = merge(ls(x), rs(x));
}