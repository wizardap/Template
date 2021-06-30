/*
	Resource : Ba Thai Pham 
	Verification : 
		- https://oj.vnoi.info/problem/elect
		- https://oj.vnoi.info/problem/twosat
		- https://cses.fi/problemset/task/1684
*/
struct TWO_SAT
{
	vector<vector<int> > e;
	int cnt, k;
	vector<int> num, low, lab;
	stack<int> st;
	TWO_SAT(int n)
	{
		e.resize(n * 2);
		num.resize(n * 2);
		low.resize(n * 2);
		lab.resize(n * 2);
		cnt = k = 0;
	}
	void add(int x, int tx, int y, int ty)
	{
		x = x << 1 ^ tx;
		y = y << 1 ^ ty;
		e[x ^ 1].pb(y);
		e[y ^ 1].pb(x);
	}
	void dfs(int u)
	{
		low[u] = num[u] = ++cnt;
		st.push(u);
		EACH(v, e[u])
		if (!lab[v])
		{
			if (num[v]) low[u] = min(low[u], num[v]);
			else
			{
				dfs(v);
				low[u] = min(low[u], low[v]);
			}
		}
		if (low[u] == num[u])
		{
			++k;
			while (1)
			{
				int v = st.top();
				st.pop();
				lab[v] = k;
				if (u == v) break;
			}
		}
	}
 
	vector<int> solve()
	{
		REP(i, sz(e))
		if (!num[i]) dfs(i);
		int n = sz(e) >> 1;
		vector<int> ans(n);
		REP(x, n)
		{
			if (lab[x << 1 ^ false] == lab[x << 1 ^ true]) return vector<int> (0);
			ans[x] = (lab[x << 1 ^ false] > lab[x << 1 ^ true]);
		}
		return ans;
	}
};
