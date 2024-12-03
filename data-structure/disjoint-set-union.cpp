class DSU {
// 1-indexed
private:
    std::vector<int> f, sz;
public:
    DSU () {}
    DSU (int _n) {
        init(_n);
    }

    void init (int _n) {
        f.resize(_n + 1);
        std::iota(f.begin(), f.end(), 0);
        sz.assign(_n + 1, 1);
        sz[0] = 0;
    }

    int find (int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same (int x, int y) {
        return find(x) == find(y);
    }

    bool merge (int x, int y) {
        // merge y to x
        x = find(x), y = find(y);
        if (x == y) return false;
        sz[x] += sz[y];
        f[y] = x;
        return true;
    }
    
    int size (int x) {
        return sz[find(x)];
    }
};