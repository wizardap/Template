/* 
  * Source: benq
  * Modified by WizardAP
  * Verification :
        - https://oj.vnoi.info/problem/nkflow
*/
/// 0-based
template<class T> struct Dinic
{
#define vi  vector
    using IT = vi<int>::iterator;
    struct Edge {int to; T flow, cap;};
    const T INF = 1e18; /// Change this with 1e9 if type "T" is integer
    vi<Edge> eds; vi<vi<int>> adj; vi<int> lev; vi<IT> cur;
    queue<int> q;
    int n;
    void init(int _n) { n = _n; adj.clear(); adj.resize(n); cur.clear(); cur.resize(n);}
    void addEdge(int u, int v, T cap, T rcap = 0)
    {
        assert(min(cap, rcap) >= 0);
        adj[u].pb(sz(eds)); eds.pb({v, 0, cap});
        adj[v].pb(sz(eds)); eds.pb({u, 0, rcap});
    }
    bool bfs(int s, int t)
    {
        assert(q.empty());
        lev = vi<int>(n, -1); for (int i = 0; i < n; i++) cur[i] = begin(adj[i]);
        q.push(s); lev[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            rof(it, adj[u])
            {
                const Edge& e = eds[*it];
                int v = e.to;
                if (lev[v] < 0 && e.flow < e.cap)
                {
                    lev[v] = lev[u] + 1;
                    q.push(v);
                }
            }
        }
        return lev[t] >= 0;

    }
    T dfs(int u, int t, T flow)
    {
        if (u == t) return flow;
        for (; cur[u] != end(adj[u]); cur[u]++)
        {
            Edge& e = eds[*cur[u]];
            int v = e.to;
            if (lev[v] != lev[u] + 1 || e.flow == e.cap) continue;
            T minflow = dfs(v, t, min(flow, e.cap - e.flow));
            if (!minflow) continue;
            eds[*cur[u]].flow += minflow;
            eds[*cur[u] ^ 1].flow -= minflow;
            return minflow;
        }
        return 0;
    }
    T maxflow(int s, int t)
    {
        T tot = 0 ; while (bfs(s, t)) {
            T flow;
            while (flow = dfs(s, t, INF))
                tot += flow;
        }
        return tot ;
    }
#undef vi
};
