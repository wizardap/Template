/*
  Modified by WizardAP
  Verification:
    - https://oj.vnoi.info/problem/match1
    - https://oj.vnoi.info/problem/fmatch
*/
/// Time complexity: O(√m.n) (m : number of edges, n : number of vertices) 
class HopcroftKarp 
{
private:
    queue<int> q;
    vector<int> dist;
    vector<vector<int>> adj;
    const int NO_MATCHING = 1e9;
    const int DUMMY_VERTEX = 0;
public:
    int M, N;
    vector<int> mu, mv; /// Matching of u , Matching of v
    void init_graph(int _m, int _n)
    {
        M = _m;
        N = _n;
        dist.assign(M + 1, 0);
        adj = vector<vector<int>>(M + 1);
    }
    void addEdge(int u, int v) {adj[u].pb(v);}
    int Matching()
    {
        mu.assign(M + 1, 0);
        mv.assign(N + 1, 0);
        int cnt = 0;
        while (bfs())
            for (int u = 1; u <= M; u++)
                if (mu[u] == DUMMY_VERTEX && dfs(u))
                    cnt++;
        return cnt;
    }
    void printMatching()
    {
        for (int u = 1; u <= M; u++)
            if (mu[u] != DUMMY_VERTEX) cout << u << " " << mu[u] << "\n";
    }
private:
    bool bfs()/// Check the argument path is exist or not ?
    {
        assert(q.empty());
        for (int u = 1; u <= M; u++)
            if (mu[u] == 0)
            {
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = NO_MATCHING;
        dist[DUMMY_VERTEX] = NO_MATCHING;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == DUMMY_VERTEX) continue;
            for (int j = 0; j < (int)adj[u].size(); j++)
            {
                int v = adj[u][j];
                if (dist[mv[v]] == NO_MATCHING)
                {
                    dist[mv[v]] = dist[u] + 1;
                    q.push(mv[v]);
                }
            }
        }
        return dist[DUMMY_VERTEX] != NO_MATCHING;
    }
    bool dfs(int u) // Matching.....
    {
        if (u == 0) return true;
        for (int j = 0; j < (int)adj[u].size(); j++)
        {
            int v = adj[u][j];
            if (dist[mv[v]] == dist[u] + 1 && dfs(mv[v]))
            {
                mu[u] = v;
                mv[v] = u;
                return true;
            }

        }
        dist[u] = NO_MATCHING;
        return false;
    }
} cg;
