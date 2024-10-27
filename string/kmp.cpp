// string: 0-indexed
// f: 1-indexed
std::vector<int> kmp(std::string s) {
    int n = s.size();
    std::vector<int> f(n + 1);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = f[j];
        j += (s[i] == s[j]);
        f[i + 1] = j;
    }
    return f;
}

// 洛谷 P3375 【模板】KMP
auto z = kmp(s2);
for (int i = 0, j = 0; i < s1.size(); ++i) {
    while (j && s2[j] != s1[i]) j = z[j];
    j += (s2[j] == s1[i]);
    if (j == s2.size()) {
        std::cout << i + 2 - s2.size() << "\n";
    }
}

for (int i = 1; i <= s2.size(); ++i) {
    std::cout << z[i] << " ";
}
std::cout << "\n";