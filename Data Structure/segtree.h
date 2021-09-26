/*
    Verification:
        - https://oj.vnoi.info/problem/lites
        - https://oj.vnoi.info/problem/qmax2
    Usage:
            - Despite of the problem, you can change some function to solve those problems
            - This is 1-based Segment Tree + Lazy Propagate
*/

template<class T> struct SegTree
{
	const T neutral_element = 0, no_operation = 0, non_available_value = 0;
	vector<T> seg, lazy;
	T comb(T x, T y) {return x + y;}
	T lazy_comb(T x, T y) {if (x == no_operation) return y; return x + y;}
	int N;
	void init_tree(int _N) { N = 1; while (N < _N) N *= 2; seg.assign(N * 2 + 1, neutral_element); lazy.assign(N * 2 + 1, no_operation);}
	void push(int id, int l, int r) {
		if (lazy[id] == no_operation) return ;
		seg[id] += (r - l + 1) * lazy[id];
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
