struct DSU
{
    vector<int> par, rnk;
    int n;
    void init_dsu(int N)
    {
        n = N;
        par.assign(n + 1, 0);
        rnk.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) par[i] = i;
    }
    int Find(int u) {return u == par[u] ? par[u] : par[u] = Find(par[u]);}
    bool same(int u, int v) {return Find(u) == Find(v);}
    bool Unite(int u, int v)
    {
        u = Find(u);
        v = Find(v);
        if (u == v) return false;
        if (rnk[u] < rnk[v]) swap(u, v);
        par[v] = u;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return true;
    }
} dsu;
