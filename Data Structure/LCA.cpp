
///WizardAP
#include<bits/stdc++.h>
using namespace std;
#define Nothing					"LCA"
#define ft						first
#define sd						second
#define pb						push_back
#define pf						push_front
#define sz(x)					(int)(x).size()

#define cntone(x)				__builtin_popcountll((x))
#define each(x,y)				for (auto &x: y)
#define all(x)					(x).begin(),(x).end()
#define aln(x,y)				(x)+1,(x)+1+(y)
#define Bonnie					freopen(Nothing".inp","r",stdin),freopen(Nothing".out","w",stdout)
#define FastIO					ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
#define two(x)					(1ll<<(x))

template<class T, class Y> T offbit(T mask, Y pos) { return (mask & ~((T)1 << pos));}
template<class T, class Y> T onbit(T mask, Y pos) {return (mask | ((T)1 << pos));}
template<class T, class Y> T getbit(T mask, Y pos) {return ((mask >> (T)pos) & (T)1);}
template<class T> bool umax(T& x, T& y) { return x < y ? swap(x, y), 1 : 0;}
template<class T> bool umin(T& x, T& y) { return x > y ? swap(x, y), 1 : 0;}
template<class T> T Modulo(T &A, T B, T mod) { A += B; if (A >= mod) A -= mod; else if (A < 0) A += mod; return A;}
template<class T> T Mod(T &A, T mod) {if (A >= mod) A -= mod; else if (A < 0) A += mod; return A;}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using LL = int64_t;
using ULL = uint64_t;
using LD = long double;
const LL MOD = 1e9 + 7;
const LL inf = 1e18;
LL fmul(LL a, LL b, LL mod) {a %= mod; b %= mod; LL q = (LD)a * b / mod; LL r = a * b - q * mod; return (r % mod + mod) % mod;}

///Head


///Lowest Common Ancestor
const int mxn = 1e3 + 5;
const int maxLog = log2(mxn);
int n, q;
vector<int> adj[mxn];
int depth[mxn], par[mxn][maxLog + 5];
void dfs(int u, int p)
{
	par[u][0] = p;
	depth[u] = depth[p] + 1;
	for (int i = 1; i <= maxLog; i++)
		par[u][i] = par[par[u][i - 1]][i - 1];
	for (auto &v : adj[u])
		if (v != p) dfs(v, u);
}
int lca(int u, int v)
{
	if (depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
	for (int i = maxLog; i >= 0; i--)
		if ((diff >> i) & 1)
			u = par[u][i];
	if (u == v) return u;
	for (int i = maxLog; i >= 0; i--)
		if (par[u][i] != par[v][i])
		{
			u = par[u][i];
			v = par[v][i];
		}
	return par[u][0];
}
int dist(int u, int v)
{
	return depth[u] + depth[v] - depth[lca(u, v)];
}




signed main()
{
	FastIO;
	//Bonnie;
	int _;
	cin >> _;
	for (int i = 1; i <= _; i++)
	{
		cin >> n;
		for (int u = 1; u <= n; u++)
		{
			int x;
			cin >> x;
			while (x-- > 0)
			{
				int v;
				cin >> v;
				adj[u].pb(v);
				adj[v].pb(u);
			}

		}
		dfs(1, 1);
		cout << "Case " << i << ":" << "\n";
		cin >> q;
		while (q--)
		{
			int u, v;
			cin >> u >> v;
			cout << lca(u, v) << "\n";
		}
		for (int i = 1; i <= n; i++)
		{
			depth[i] = 0;
			par[i][0] = 0;
			adj[i].clear();
		}
	}

	return 0;
}

///Nothing to see !
