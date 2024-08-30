template <typename T>
struct Fenwick {
private:
    int n;
    std::vector<T> tr;
public:
    Fenwick (int _n = 0) {
        init(_n);
    }
    void init (int _n) {
        n = _n;
        tr.assign(n, T{});
    }
    void add (int p, const T &v) {
        for (int i = p + 1; i <= n; i += i & -i) {
            tr[i - 1] += v;
        }
    }
    T sum (int p) {
        T res {};
        for (int i = p; i > 0; i -= i & -i) {
            res += tr[i - 1];
        }
        return res;
    }
    int kth (const T &k) {
        int x = 0;
        T cur {};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + tr[x + i - 1] <= k) {
                x += i;
                cur += tr[x - 1];
            }
        }
        return x;
    }
};