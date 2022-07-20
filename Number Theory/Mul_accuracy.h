/*
  Resource  : Darkkcyan
  Modified by WizardAP
  Description : Compare the accuracy of real numbers
  Verification : 
      - https://oj.vnoi.info/problem/product
*/

const ll modulo[] = {(ll)1e9 + 2277, (ll)1e9 + 5277, (ll)1e9 + 8277, (ll)1e9 + 9277};
const int NMOD = 1; /// if you want more accuracy , increase this variable !
struct RMD
{
	ll value[NMOD];
	const ll no_opt = -1;
	RMD()
	{
		memset(value, -1, sizeof value);
	}
	bool isEmpty()
	{
		for (int j = 0; j < NMOD; j++)
			if (value[j] != -1) return false;
		return true;
	}
	RMD(int x) { for (int j = 0; j < NMOD; j++) value[j] = x;}
	RMD operator*(const RMD &o)const
	{
		RMD res;
		for (int j = 0; j < NMOD; j++) res.value[j] = value[j] * o.value[j] % modulo[j];
		return res;
	}
	RMD operator+(const RMD &o)const
	{
		RMD res;
		for (int j = 0; j < NMOD; j++) res.value[j] = (value[j] + o.value[j]) % modulo[j];
		return res;
	}
	bool operator==(const RMD &o)const
	{
		for (int j = 0; j < NMOD; j++)
			if ( value[j] != o.value[j]) return false;
		return true;
	}
	bool operator!=(const RMD &o)const
	{
		for (int j = 0; j < NMOD; j++)
			if ( value[j] != o.value[j]) return true;
		return false;
	}
	RMD& operator=(const RMD &o)
	{
		for (int j = 0; j < NMOD; j++) value[j] = o.value[j];
		return *this;
	}
};
struct Tree
{
	vt<RMD> t;
	int n;
	void build(int id, int l, int r)
	{
		if (l == r)
		{
			t[id] = RMD(l);
			return ;
		}
		int mid = (l + r) >> 1;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		t[id] = t[id * 2] * t[id * 2 + 1];
	}
	void init(int N)
	{
		n = N;
		t.assign(4 * n + 1, RMD(1));
		build(1, 1, n);
	}
	RMD get(int u, int v, int id, int l, int r)
	{
		if (v < l || r < u) return RMD(1);
		if (u <= l && r <= v) return t[id];
		int mid = (l + r) >> 1;
		return get(u, v, id * 2, l, mid) * get(u, v, id * 2 + 1, mid + 1, r);
	}
	RMD get(int u, int v) {
		return get(u, v, 1, 1, n);
	}
} opt;
