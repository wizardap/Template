/*
  Modified by WizardAP
  Verification: 
    - https://www.spoj.com/submit/LCA/
*/
struct LCA
{
    vector<int> depth;
    vector<vector<int> > par, adj;
    int lg, n;

    void init_lca(int N)
    {

        n = N;
        depth.assign(n + 1, 0);
        lg = log2(n) + 1;
        par.assign(n + 1, vector<int>(lg + 1, -1));
        adj.clear();
        adj.resize(n + 1);
    }
    void addEdge(int u, int v) {adj[u].pb(v); adj[v].pb(u); }
    void dfs(int u, int p)
    {
        if (p < 0) par[u][0] = u; else par[u][0] = p;
        for (int i = 1; i <= lg; i++)
            par[u][i] = par[par[u][i - 1]][i - 1];
        depth[u] = depth[p] + 1;
        for (int v : adj[u])
            if (v != p) dfs(v, u);
    }
    int lca(int u, int v)
    {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = lg; i >= 0; i--)
            if ((diff >> i) & 1)   u = par[u][i];
        if (u == v) return u;
        for (int i = lg; i >= 0; i--)
            if (par[u][i] != par[v][i]) { u = par[u][i]; v = par[v][i];}
        return par[u][0];
    }
    int dist(int u, int v)
    {
        return depth[u] + depth[v] - depth[lca(u, v)];
    }
};
