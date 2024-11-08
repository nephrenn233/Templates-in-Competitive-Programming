int dfn[MAXN], low[MAXN], idx = 0;
stack<int> st;
vector<vector<int>> ans;

void tarjan(int u, bool is_root) {
    dfn[u] = low[u] = ++idx;
    st.push(u);
    if(is_root && g[u].size() == 0) {
        vector<int> res;
        res.push_back(u);
        ans.push_back(res);
        return;
    }
    for(auto v : g[u]) {
        if(!dfn[v]) {
            tarjan(v, 0);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                vector<int> res;
                int w;
                do {
                    w = st.top();
                    st.pop();
                    res.push_back(w);
                }while(w != v);
                res.push_back(u);
                ans.push_back(res);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void solve () {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        if(u == v) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) tarjan(i, 1);
    }

    cout << ans.size() << "\n";
    for(auto i : ans) {
        cout << i.size() << " ";
        for(auto j : i) cout << j << " ";
        cout << "\n";
    }
}