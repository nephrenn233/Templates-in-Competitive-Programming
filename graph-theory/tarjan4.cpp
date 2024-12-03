int dfn[MAXN], low[MAXN], tt = 0;
stack<int> st;
map<PII, bool> vis;

vector<vector<int>> ans;

void tarjan(int u, int f) {
    dfn[u] = low[u] = ++tt;
    st.push(u);
    for(auto [v, id] : g1[u]) {
        if(id == (f ^ 1)) continue;
        if(!dfn[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) {
        vector<int> res;
        res.push_back(u);
        while(st.size() && st.top() != u) {
            res.push_back(st.top());
            st.pop();
        }
        st.pop();
        ans.push_back(res);
    }
}

void solve () {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        if(u == v) continue;
        g1[u].push_back({v, i << 1});
        g1[v].push_back({u, i << 1 | 1});
    }

    for(int i = 1; i <= n; ++i) {
        if(!dfn[i]) tarjan(i, 0);
    }

    cout << ans.size() << "\n";
    for(auto i : ans) {
        cout << i.size() << " ";
        for(auto j : i) cout << j << " ";
        cout << "\n";
    }
}