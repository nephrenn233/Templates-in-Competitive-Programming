template <typename T>
struct Matrix {
    int n, m; // n行 m列
    std::vector<vector<T>> a;

    Matrix () {}
    Matrix (int _n, int _m) : n(_n), m(_m) {
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i].resize(m);
            a[i].assign(m, 0);
        }
    }
    void unitilize () {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == j) a[i][j] = 1;
                else a[i][j] = 0;
            }
        }
    }
    friend std::istream &operator >> (std::istream &is, Matrix &mat) {
        for (int i = 0; i < mat.n; ++i) {
            for (int j = 0; j < mat.m; ++j) {
                is >> mat.a[i][j];
            }
        }
        return is;
    }
    friend std::ostream &operator << (std::ostream &os, Matrix &mat) {
        for (int i = 0; i < mat.n; ++i) {
            for (int j = 0; j < mat.m; ++j) {
                os << mat.a[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }
    // suppose valid
    Matrix &operator += (const Matrix &rhs) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] += rhs.a[i][j];
            }
        }
        return *this;
    }
    friend Matrix operator + (const Matrix &lhs, const Matrix &rhs) {
        Matrix res = lhs;
        res += rhs;
        return res;
    }
    Matrix &operator - () {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = -a[i][j];
            }
        }
        return *this;
    }
    Matrix &operator -= (Matrix rhs) {
        return *this += (-rhs);
    }
    friend Matrix operator - (const Matrix &lhs, const Matrix &rhs) {
        Matrix res = lhs;
        res -= rhs;
        return res;
    }
    friend Matrix operator * (const Matrix &lhs, const Matrix &rhs) {
        Matrix res(lhs.n, rhs.m);
        for (int i = 0; i < res.n; ++i) {
            for (int j = 0; j < res.m; ++j) {
                for (int k = 0; k < lhs.m; ++k) {
                    res.a[i][j] += lhs.a[i][k] * rhs.a[k][j];
                }
            }
        }
        return res;
    }
};

template <typename T>
Matrix<T> quick_pow (Matrix<T> a, i64 b) {
    Matrix<T> res (a.n, a.m);
    res.unitilize();
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}