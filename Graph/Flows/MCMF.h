/*
  
  Source : skyvn97
  Modified by WizardAP
  Requirement:
    - No negative cycles
    - No duplicate edge with same weight
  Verification : 
      - https://oj.vnoi.info/problem/mincost
*/
/// Warning ! : Need to make a fake sink and source to use this template 
struct mcmf  
{
private:
	const ll INFINITIVE = LLONG_MAX;
public:
	struct Edge
	{
		int u, v;
		ll flow, cap, cost;
		Edge(int u = 0, int v = 0, ll cap = 0, ll cost = 0) : u(u), v(v), flow(0), cap(cap), cost(cost) {};
		ll rem() { return cap - flow;}
	};
	vt<ll> dist;
	vt<bool> inq;
	vt<vt<int>> adj;
	vt<Edge> eds;
	vt<int> trace;
	queue<int> q;
	int n;
	mcmf (int _n = 0)
	{
		n = _n;
		adj.assign(n + 7, vt<int>());
		dist.assign(n + 7, 0);
		inq.assign(n + 7, 0);
		trace.assign(n + 7, -1);
		eds.clear();
	}
	void addEdge(int u, int v, ll cap, ll cost)
	{
		adj[u].pb(sz(eds)); eds.pb(Edge(u, v, cap, cost));
		adj[v].pb(sz(eds)); eds.pb(Edge(v, u, 0, -cost));
	}
	bool path(int s, int t) /// SPFA
	{
		for (int i = 0; i <= n; i++)
		{
			dist[i] = INFINITIVE;
			trace[i] = -1;
			inq[i] = false;
		}
		assert(q.empty());
		q.push(s);
		inq[s] = true;
		dist[s] = 0;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			inq[u] = false;
		for (auto id : adj[u])
			if (eds[id].rem() > 0)
			{
				int v = eds[id].v;
				ll w = eds[id].cost;
				if (ckmin(dist[v], dist[u] + w))
				{
					if (!inq[v])
					{
						q.push(v);
						inq[v] = true;
					}
					trace[v] = id;
				}
			}
		}
		return trace[t] != -1;
	}
	pair<ll, ll> answer(int s, int t)
	{
		ll totflow = 0, totcost = 0;
		while (path(s, t))
		{
			ll minflow = INFINITIVE;
			for (int u = t; u != s; u = eds[trace[u]].u) ckmin(minflow, eds[trace[u]].rem());
			for (int u = t; u != s; u = eds[trace[u]].u) {
				eds[trace[u]].flow += minflow;
				eds[trace[u] ^ 1].flow -= minflow;
			}
			totflow += minflow;
			totcost += minflow * dist[t];
		}

		return make_pair(totflow, totcost);
	}
};