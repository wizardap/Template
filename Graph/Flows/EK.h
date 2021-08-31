/* 
	- Modified by WizardAP
	- Verification : 
		+ https://oj.vnoi.info/problem/nkflow
*/
struct EK
{
	struct Edge
	{
		int u , v;
		LL cap, flow;
		Edge(int u = 0 , int v = 0 , LL cap = 0) : u(u), v(v), cap(cap), flow(0) {};
		LL rem() {

			return cap - flow;
		}
	};
	vi<Edge> eds;
	vi<vi<int>> adj;
	vi<int> trace;
	vi<bool> vis;
	int n;
	EK(int _n = 0)
	{
		n = _n;
		eds.clear();
		adj.assign(n + 7, vi <int>());
		trace.assign(n + 7, -1);
		vis.assign(n + 7, false);
	}
	void addEdge(int u , int v, LL cap, bool isDirected = true)
	{
		adj[u].pb(sz(eds)); eds.pb(Edge(u, v, cap));
		adj[v].pb(sz(eds)); eds.pb(Edge(v, u, (isDirected ? 0 : cap)));
	}
	bool BFS(int s, int t)
	{
		for (int  i = 0 ; i <= n; i++) {
			vis[i] = false;
			trace[i] = -1;
		}
		queue<int> q;
		q.push(s);
		vis[s] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int id : adj[u])
				if (eds[id].rem() > 0)
				{
					int v = eds[id].v;
					if (!vis[v])
					{
						vis[u] = true;
						trace[v] = id;
						if (v == t) return true;
						q.push(v);
					}
				}
		}
		return false;
	}
	LL maxflow(int s, int t)
	{
		LL totflow = 0 ;
		while (BFS(s, t))
		{
			LL min_flow = inf;
			for (int  u = t; u != s; u = eds[trace[u]].u) minimize(min_flow, eds[trace[u]].rem());
			for (int u = t; u != s; u = eds[trace[u]].u)
			{
				eds[trace[u]].flow += min_flow;
				eds[trace[u] ^ 1].flow -= min_flow;
			}
			totflow += min_flow;
		}
		return totflow;
	}
};
