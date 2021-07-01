/* 
  * Source: Chilli 
  * Verification: 
      - https://oj.vnoi.info/problem/fflow
      - https://oj.vnoi.info/problem/nkflow
  * Time complextity : O(V*E*log(U)) while U is the maximum capacity of all edges
*/ 

/// 0-based
template<class T> struct Dinic
{
#define vi vector
    struct Edge {int to, rev; T flow, cap;};
    bool SCALING = false;
    const T INF = 1e18;
    int N; queue<int> q;
    vi<int> lvl, cur;
    T lim;
    vi<vi<Edge>> adj;
    void init(int _N, bool NeedFaster = false ) { N = _N; adj.clear(); adj.resize(N); cur.clear(); cur.resize(N); SCALING = NeedFaster;   };
    void addEdge(int u, int v, T cap, bool isDirected = true)
    {
        adj[u].pb({v, sz(adj[v]), 0, cap});
        adj[v].pb({u, sz(adj[u]) - 1, 0, isDirected ? 0 : cap});
    }
    bool bfs(int s, int t)
    {
        assert(q.empty());
        lvl.assign(N, -1);
        q.push(s); lvl[s] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            rof(it, adj[u])
            {
                const Edge& e = *it;
                int v = e.to;
                if (lvl[v] < 0 && e.flow < e.cap & (!SCALING || e.cap - e.flow >= lim)) { lvl[v] = lvl[u] + 1; q.push(v);}
            }
        }
        return lvl[t] >= 0;
    }
    T dfs(int u, int t, T flow)
    {
        if (u == t || !flow) return flow;
        for (; cur[u] < sz(adj[u]); cur[u]++)
        {
            Edge& E = adj[u][cur[u]];
            int v = E.to;
            if (lvl[v] != lvl[u] + 1 || E.cap - E.flow < lim) continue;
            if (T pushed = dfs(v, t, min(flow, E.cap - E.flow))) {E.flow += pushed; adj[E.to][E.rev].flow -= pushed; return pushed;}
        }
        return 0;
    }
    T maxflow(int s, int t)
    {
        T tot = 0 ;
        for (lim = SCALING ? INF : 1 ; lim > 0; lim >>= 1ll)
            while (bfs(s, t))
            {
                cur.assign(N, 0);
                while (T pushed = dfs(s, t, INF)) tot += pushed;
            }
        return tot;
    }
};
