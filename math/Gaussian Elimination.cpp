const double eps = 1e-8;
int sgn (double x) {
    return x < -eps ? -1 : (x > eps ? 1 : 0);
}
// augmented matrix
// No Solution: -1, Infinity Solution: 0, Unique Solution: 1
std::pair<int, std::vector<double>> Gauss (Matrix<double> mat) {
    std::pair<int, std::vector<double>> res;
    auto [n, m, a] = mat;
    res.second.resize(n);
    res.second.assign(n, 0);

    int Line = 0;
    for (int k = 0; k < n; ++k) {
        int mx = Line;
        for (int i = Line + 1; i < n; ++i) {
            if (std::abs(a[i][k]) > std::abs(a[mx][k])) mx = i;
        }
        if (sgn(a[mx][k]) == 0) continue;
        for (int j = 0; j < m; ++j) {
            std::swap(a[Line][j], a[mx][j]);
        }
        for (int i = 0; i < n; ++i) {
            if (i == Line) continue;
            double r = a[i][k] / a[Line][k];
            for (int j = k; j < m; ++j) {
                a[i][j] -= a[Line][j] * r;
            }
        }
        ++Line;
    }
    if (Line < n) {
        while (Line < n) {
            if (sgn(a[Line++][n]) != 0) {
                res.first = -1;
                return res;
            }
        }
        res.first = 0;
        return res;
    }
    res.first = 1;
    for (int i = 0; i < n; ++i) {
        res.second[i] = a[i][m - 1] / a[i][i];
    }
    return res;
}