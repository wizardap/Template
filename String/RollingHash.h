/*
    - Resource : gspvh
    - Modified by WizardAP
    *) Verification:
        - https://oj.vnoi.info/problem/substr
        - https://oj.vnoi.info/problem/dtksub
*/


//// The larger the number of modules, the slower the program runs
///// WARNING ! : Please use "precompute" function , maybe you are wrong because you don't use that function( precompute's function)
const ll modulo[4] = {(ll)1e9 + 7, (ll)1e9 + 5277, (ll)1e9 + 8277, (ll)1e9 + 9277};
const int BASE = 257;
const int NMOD = 1;
const int mxn = 1e6 + 5; /// Depends on constraints
ll pw[NMOD][mxn], mod_inv[NMOD][mxn];
ll qpow(ll a, ll k, ll mdl)
{
	ll res = 1;
	for (; k; k >>= 1ll, a = a * a % mdl)
		if (k & 1ll) res = res * a % mdl;
	return res;
}
ll inverse(ll a, ll mdl)
{
	return qpow(a, mdl - 2, mdl);
}
void precompute(const int &Leng)
{
	for (int j = 0 ; j < NMOD; j++)
		for (int i = 0 ; i <= Leng; i++)
		{
			pw[j][i] = i == 0 ? 1 : pw[j][i - 1] * BASE % modulo[j];
			mod_inv[j][i] = i == 0 ? 1 : mod_inv[j][i - 1] * inverse(BASE, modulo[j]) % modulo[j];
		}
}
struct Hash {
	ll value[NMOD];
	Hash() {
		memset(value, 0, sizeof value);
	}
	Hash(char c) {
		for (int j = 0; j < NMOD; j++) value[j] = c;
	}
	Hash operator + (const Hash &x) const {
		Hash res;
		for (int j = 0; j < NMOD; j++) {
			res.value[j] = (value[j] + x.value[j]) % modulo[j];
		}
		return res;
	}
	Hash operator - (const Hash &x) const {
		Hash res;
		for (int j = 0; j < NMOD; j++) {
			res.value[j] = (value[j] - x.value[j] + modulo[j]) % modulo[j];
		}
		return res;
	}
	Hash operator * (int k) const {
		Hash res;
		for (int j = 0; j < NMOD; j++)
			res.value[j] = 1ll * value[j] * pw[j][k] % modulo[j];
		return res;
	}
	bool operator < (const Hash &x) const {
		for (int j = 0; j < NMOD; j++) if (value[j] != x.value[j])
				return value[j] < x.value[j];
		return false;
	}
	bool operator == (const Hash &x) const {
		for (int j = 0; j < NMOD; j++) if (value[j] != x.value[j]) return false;
		return true;
	}

};
struct RollingHash
{
	vector<Hash> hash;
	const Hash NO_OPERATION;
	int n;
	RollingHash()
	{
		hash.clear();
	}
	void init(const string &s)
	{
		n = s.size();
		hash.assign(n + 1, NO_OPERATION);
		for (int i = 0; i < n; i++)
			hash[i + 1] = hash[i] + Hash(s[i]) * i;
	}
	Hash operator()(int pos)
	{
		return hash[pos];
	}
	Hash operator()(int l, int r)
	{
		assert(l <= r);
		assert(l > 0);
		Hash res;
		for (int j = 0; j < NMOD; j++)
			res.value[j] = ((hash[r].value[j] - hash[l - 1].value[j] + modulo[j]) * mod_inv[j][l]) % modulo[j];
		return res;
	}
};
