const int MAXN = 110;
const double eps = 1e-6;

bool sgn (double x) {
    return x < -eps ? -1 : (x > eps ? 1 : 0);
}

int n;
double mat[MAXN][MAXN];

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            int x;
            std::cin >> x;
            mat[i][j] = x;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int mx = i;
        for (int j = i + 1; j <= n; ++j) {
            if (std::abs(mat[j][i]) > std::abs(mat[mx][i])) mx = j;
        }
        for (int j = 1; j <= n + 1; ++j) {
            std::swap(mat[mx][j], mat[i][j]);
        }
        if (sgn(mat[i][i]) == 0) {
            std::cout << "No Solution\n";
            return 0;
        }
        double div = mat[i][i];
        for (int j = 1; j <= n + 1; ++j) {
            mat[i][j] /= div;
        }
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            double r = mat[j][i] / mat[i][i];
            for (int k = 1; k <= n + 1; ++k) {
                mat[j][k] -= mat[i][k] * r;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << std::fixed << std::setprecision(2) << mat[i][n + 1] << "\n";
    }

    return 0;
}