/*
  Resource : https://cp-algorithms.com/graph/lca_binary_lifting.html
  Modified by WizardAP
  Verification: 
    - https://www.spoj.com/problems/LCA/
*/


struct LCA
{
    vector<int> depth, tin, tout;
    vector<vector<int> > par, adj;
    int lg, n, Time = 0;

    void init_lca(int N)
    {
        Time = 0;
        n = N;
        depth.resize(n + 1, 0);
        tin.resize(n + 1, 0);
        tout.resize(n + 1, 0);
        lg = log2(n) + 1;
        par.assign(n + 1, vector<int>(lg + 1, -1));
        adj.clear();
        adj.resize(n + 1);
    }
    void addEdge(int u, int v) {adj[u].pb(v); adj[v].pb(u); }
    void dfs(int u, int p)
    {
        tin[u] = ++Time;
        if (p < 0 ) par[u][0] = u;
        else par[u][0] = p;
        depth[u] = depth[p] + 1;
        for (int i = 1; i <= lg; i++) par[u][i] = par[par[u][i - 1]][i - 1];
        for (int v : adj[u])
            if (v != p) dfs(v, u);
        tout[u] = ++Time;
    }
    bool isAncestor(int u, int v)
    {
        return (tin[u] <= tin[v]  && tout[u] >= tout[v]);
    }
    int lca(int u, int v)
    {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;
        for (int i = lg; i >= 0; i--) if (!isAncestor(par[u][i], v) ) u = par[u][i];
        return par[u][0];
    }
    int dist(int u, int v)
    {
        return depth[u] + depth[v] - depth[lca(u, v)];
    }
};
