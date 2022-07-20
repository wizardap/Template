/*
  Resource: benq
  Modified by WizardAP
  Verification:
      - https://www.spoj.com/problems/QTREE/
      - https://oj.vnoi.info/problem/qtree3
   This template use 1-based
*/

template<class T> struct SegTree
{
	const T neutral_element = 0, no_operation = inf, non_available_value = -inf;
	vector<T> seg, lazy;
	T comb(T x, T y) {return max(x, y);}
	T lazy_comb(T x, T y) {if (x == no_operation) return y; return y;}
	int N;
	void init_tree(int _N) { N = _N; seg.assign(N * 4 + 1, neutral_element); lazy.assign(N * 4 + 1, no_operation);}
	void push(int id, int l, int r) {
		if (lazy[id] == no_operation) return ;
		seg[id] = lazy[id];
		if (l != r) for (int i = 0; i < 2; i++) lazy[id * 2 + i] = lazy_comb(lazy[id * 2 + i], lazy[id]);
		lazy[id] = no_operation;
	}
	void upd(int u, int v, T val, int id, int l, int r )
	{
		push(id, l, r); if (v < l || r < u) return;
		if (u <= l && r <= v) { lazy[id] = lazy_comb(lazy[id], val); push(id, l, r); return ;}
		int mid = (l + r) >> 1;
		upd(u, v, val, id * 2, l, mid); upd(u, v, val, id * 2 + 1, mid + 1, r);
		seg[id] = comb(seg[id * 2], seg[id * 2 + 1]);
	}
	T get(int u, int v, int id , int l , int r) {
		push(id, l, r); if (v < l || r < u) return non_available_value;
		if (u <= l && r <= v) return seg[id];
		int mid = (l + r) >> 1; return comb(get(u, v, id * 2, l, mid), get(u, v, id * 2 + 1, mid + 1, r));
	}
	void upd(int u, int v, T val) {upd(u, v, val, 1, 1, N);}
	T get(int u, int v) {return get(u, v, 1, 1, N);}
};
template<bool vte> struct hld
{
	vector<vector<int>> adj;
	vector<int> depth, parent, head, heavy, pos, size;
	int timer, N;
	SegTree<ll> TREE;
	void addEdge(int u, int v) {adj[u].pb(v); adj[v].pb(u);}
	void prepare(int _N)
	{
		N = _N;
		depth.assign(N + 1, 0); parent.assign(N + 1, 0); head.assign(N + 1, 0); heavy.assign(N + 1, -1); pos.assign(N + 1, 0); size.assign(N + 1, 0);
		adj.clear();
		adj.resize(N + 1);
		TREE.init_tree(N);
	}
	void dfs(int u, int p)
	{
		parent[u] = p;
		depth[u] = depth[p] + 1;
		size[u] = 1;
		int max_size = 0;
		rof(it, adj[u])
		{
			int v = *it;
			if (v == p) continue;
			dfs(v, u);
			size[u] += size[v];
			if (size[v] > max_size) {max_size = size[v]; heavy[u] = v;}
		}
	}
	void decompose(int u, int h)
	{
 
		head[u] = h; pos[u] = ++timer;
		if (heavy[u] != -1) decompose(heavy[u], h);
		rof(it, adj[u])
		{
			int v = *it; if (v == parent[u] || v == heavy[u]) continue;
			decompose(v, v);
		}
	}
	void init(int R = 1) {timer = 0; dfs(R, R); decompose(R, R);}
	int lca(int u, int v)
	{
		for (; head[u] != head[v]; v = parent[head[v]])
			if (depth[head[u]] > depth[head[v]]) swap(u, v);
		return (depth[u] < depth[v] ? u : v);
	}
	int dist(int u, int v) {
		return (depth[u] + depth[v] - 2 * depth[lca(u, v)]);
	}
	ll query(int u, int v)
	{
		ll res = 0;
		for (; head[u] != head[v]; v = parent[head[v]])
		{
			if (depth[head[u]] > depth[head[v]]) swap(u, v);
			res = max(res, TREE.get(pos[head[v]], pos[v]));
		}
		if (depth[u] > depth[v]) swap(u, v);
		res = max(res, TREE.get(pos[u] + vte, pos[v]));
		return res;
	}
	void upd(int u, int v, ll w)
	{
		for (; head[u] != head[v]; v = parent[head[v]])
		{
			if (depth[head[u]] > depth[head[v]]) swap(u, v);
			TREE.upd(pos[head[v]], pos[v], w);
		}
		if (depth[u] > depth[v]) swap(u, v);
		TREE.upd(pos[u] + vte, pos[v], w);
	}
};
