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
		ll cap, flow;
		Edge(int u = 0 , int v = 0 , ll cap = 0) : u(u), v(v), cap(cap), flow(0) {};
		ll rem() {

			return cap - flow;
		}
	};
	vt<Edge> eds;
	vt<vt<int>> adj;
	vt<int> trace;
	vt<bool> vts;
	int n;
	EK(int _n = 0)
	{
		n = _n;
		eds.clear();
		adj.assign(n + 7, vt <int>());
		trace.assign(n + 7, -1);
		vts.assign(n + 7, false);
	}
	void addEdge(int u , int v, ll cap, bool isDirected = true)
	{
		adj[u].pb(sz(eds)); eds.pb(Edge(u, v, cap));
		adj[v].pb(sz(eds)); eds.pb(Edge(v, u, (isDirected ? 0 : cap)));
	}
	bool BFS(int s, int t)
	{
		for (int  i = 0 ; i <= n; i++) {
			vts[i] = false;
			trace[i] = -1;
		}
		queue<int> q;
		q.push(s);
		vts[s] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int id : adj[u])
				if (eds[id].rem() > 0)
				{
					int v = eds[id].v;
					if (!vts[v])
					{
						vts[u] = true;
						trace[v] = id;
						if (v == t) return true;
						q.push(v);
					}
				}
		}
		return false;
	}
	ll maxflow(int s, int t)
	{
		ll totflow = 0 ;
		while (BFS(s, t))
		{
			ll min_flow = inf;
			for (int  u = t; u != s; u = eds[trace[u]].u) ckmin(min_flow, eds[trace[u]].rem());
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