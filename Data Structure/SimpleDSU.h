/*
    Modified by WizardAP
    Verification:
        - https://acm.timus.ru/problem.aspx?space=1&num=1671
*/
///0-based or 1-based is okay 
struct DSU
{
    vector<int> p, size;
    DSU(int n = 0): p(n + 1, -1), size(n + 1, 1) {};
    int root(int x) { return p[x] == -1 ? x : p[x] = root(p[x]);}
    bool unite(int u, int v)
    {
        u = root(u);
        v = root(v);
        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);
        size[u] += size[v];
        p[v] = u;
        return true;
    }
    bool same(int u, int v) { return (root(u) == root(v));}
};
