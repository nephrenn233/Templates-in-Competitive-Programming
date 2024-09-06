template <typename T>
struct Fenwick {
// 1-indexed
private:
    int n;
    std::vector<T> tr;
public:
    Fenwick (int _n = 0) {
        init(_n);
    }
    void init (int _n) {
        n = _n;
        tr.resize(n + 1);
        tr.assign(n + 1, T(0));
    }
    void add (int p, const T &v) {
        for (int i = p; i <= n; i += i & -i) {
            tr[i] += v;
        }
    }
    T sum (int p) {
        T res (0);
        for (int i = p; i >= 1; i -= i & -i) {
            res += tr[i];
        }
        return res;
    }
};