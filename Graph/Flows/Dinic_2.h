/* 
  * Source: Benjamin Qi (Benq) 
  * Modified by WizardAP
  * Verification :
        - https://oj.vnoi.info/problem/nkflow
	- Minmum Cut : https://cses.fi/problemset/task/1695
  * Description how minimum cut work(Source : from a comment on stackoverflow )  : 
	- Run any max flow algorithm on residual graph (Ford-Fulkerson, Edmonds Karp, Dinic, etc)
	- Do BFS from source node ignoring saturated edges (edges where flow value = edge capacity)
	- Now take all edges that go from vtsited nodes to unvtsited nodes
	- Those edges will be one of possible min cuts
*/
/// 0-based
template<class T> struct Dinic
{
	using IT = vt<int>::iterator;
	struct Edge {int to; T flow, cap;};
	const T INF = numeric_limits<T>::max(); /// Change this with 1e9 if type "T" is integer
	struct INFO
	{
		int u, v, id;
		INFO(int u = 0, int v = 0, int id = 0): u(u), v(v), id(id) {};
	};
	vt<pair<int, int>> CUTS;
	vt<INFO> LIST;/// Use this vector for tracing
	vt<Edge> eds; vt<vt<int>> adj; vt<int> lev; vt<IT> cur;
	queue<int> q;
	int n;
	void init(int _n) { n = _n; adj.clear(); adj.resize(n); cur.clear(); cur.resize(n);}
	void addEdge(int u, int v, T cap, T rcap = 0)
	{
		assert(min(cap, rcap) >= 0);
		LIST.pb(INFO(u, v, sz(eds)));
		adj[u].pb(sz(eds)); eds.pb({v, 0, cap});
		adj[v].pb(sz(eds)); eds.pb({u, 0, rcap});
	}
	bool bfs(int s, int t)
	{
		assert(q.empty());
		lev = vt<int>(n, -1); for (int i = 0; i < n; i++) cur[i] = begin(adj[i]);
		q.push(s); lev[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
		for (auto it : adj[u])
			{
				const Edge& e = eds[it];
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
	T minCut(int s, int t) /// Find minimum cut
	{
		T total = 0;
		bfs(s, t);
		for (auto it : LIST) {
			int u = it.u;
			int v = it.v;
			int id = it.id;
			if (lev[u] >= 0 && lev[v] == -1) {
				total += eds[id].cap;
				CUTS.pb(make_pair(u, v));
			}
		}
		return total;
	}
};