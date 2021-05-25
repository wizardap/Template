///All template are helped to find maximum value at point x in line y=a*x+b


//// Based Codeforces users : xfce66666
struct ConvexHull {
	struct Line
	{
		LL a, b;
		Line() : a(0), b(0) {}
		Line(LL a, LL b) : a(a), b(b) {}
		LL eval(LL x) { return a * x + b;}
	};
	int size = 0;
	vector<Line> hull;
	ConvexHull(int maxSize) {
		hull.resize(maxSize++, Line(0, 0));
	}
	LL Div( LL a, LL b) {
		return a / b - (a % b && ((a < 0) ^ (b < 0) )) ;
	}
	bool is_bad(int curr, int prev, int next) {
		Line c = hull[curr], p = hull[prev], n = hull[next];
		return Div(c.b - n.b, n.a - c.a) <= Div(p.b - c.b, c.a - p.a);
	}


	void add(LL a, LL b) {
		hull[size++] = (Line) {a, b};
		while (size > 2 && is_bad(size - 2, size - 3, size - 1))
		{
			hull[size - 2] = hull[size - 1];
			size--;
		}
	}

	LL query(LL x) {
		int l = -1, r = size - 1;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if (hull[m].eval(x) <= hull[m + 1].eval(x))
				l = m;
			else
				r = m;
		}
		return hull[r].eval(x);
	}
};
//// Short code from KACTL. Be careful !  This template can only be used from c++14 and above.
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
