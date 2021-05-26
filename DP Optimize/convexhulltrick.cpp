///All template are helped to find maximum value at point x in line y=a*x+b


//// Based on Codeforces users : xfce66666
/// Modified by WizardAP
/// Use to query maximum value, if u wanna query minimum query , just change sign to (-) . Example : y=ax+b -> add(a,b), query(x) . After change sign , it will be : add(-a,-b),-query(x)
struct ConvexHull 
{
	int size = 0;
	struct Line
	{
		LL a, b;
		Line(): a(0), b(0) {};
		Line(LL a, LL b): a(a), b(b) {};
		LL eval(LL x) {return (a * x + b);}
	};
	struct roll_back
	{
		int pos, top;
		Line overwrite;
		roll_back(): pos(0), top(0), overwrite(Line(0, 0)) {};
		roll_back(int p, int t, Line o): pos(p), top(t), overwrite(o) {};
	};

	vector<Line> hull;
	vector<roll_back> backup;
	void restart(int maxSize)
	{
		hull.resize(maxSize + 5, Line(0, 0));
	}
	void undo()
	{
		roll_back prev = backup.back();
		backup.pop_back();
		size = prev.top;
		hull[prev.pos] = prev.overwrite;
	}
	LL Div(LL a, LL b)
	{
		return (a / b) - ((a ^ b) < 0 && a % b);
	}
	bool bad(Line cur, Line prev, Line next) {
		return Div(cur.b - next.b, next.a - cur.a) <= Div(prev.b - cur.b, cur.a - prev.a);
	}
	void insert(LL k, LL m)/// if u don't or can't sort slope
	{

		Line p = Line(k, m);
		int l = -1, r = size - 1;
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (!bad(hull[mid + 1], hull[mid], p)) l = mid;
			else r = mid;
		}
		int idx = r + 1;
		backup.pb(roll_back(idx, size, hull[idx]));
		size = idx;
		hull[size++] = p;
	}
	void add(LL k, LL m) /// if all slopes are sorted
	{
		hull[size++] = Line(k, m);
		while (size > 2 && bad(hull[size - 2], hull[size - 3], hull[size - 1]))
		{
			hull[size - 2] = hull[size - 1];
			size--;
		}
	}
	LL query(LL x)
	{
		int l = -1, r = size - 1;
		while (r - l > 1)
		{
			int mid = (l + r) >> 1;
			if (hull[mid].eval(x) <= hull[mid + 1].eval(x)) l = mid;
			else r = mid;
		}
		return hull[r].eval(x);
	}
} cht;
//// Short code from KACTL. Be careful !  This template can only be used from c++14 and above. And this code can't delete or roll back 
struct Line {
	mutable LL k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(LL x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const LL inf = LLONG_MAX;
	LL div(LL a, LL b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(LL k, LL m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	LL query(LL x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
