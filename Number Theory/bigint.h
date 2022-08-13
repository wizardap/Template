/*
	Resource : Benjamin Qi (benq)
	Link : https://github.com/wizardap/USACO/blob/master/Implementations/content/numerical/Arithmetic/BigInt.h
	Verification : 
		- https://oj.vnoi.info/problem/bignum

*/


const int base = 1e9, base_digits = 9;
struct bigint { // value == 0 is represented by empty z
#define F0R(a,b) for(int (a) = 0;(a)<(b);(a)++)
#define R0F(a,b) for(int (a) = (b) - 1;(a)>=0;(a)--)
	vt<int> z; // digits
	int sign; // sign == 1 <==> value >= 0
	bigint() : sign(1) {} // sign == -1 <==> value < 0
	bigint(ll v) { *this = v; }
	bigint &operator=(ll v) {
		sign = v < 0 ? -1 : 1; v *= sign; // make v positive
		z.clear(); for (;v;v/=base) z.pb(v%base);
		return *this;
	}
	bigint(const string &s) { read(s); } // add char by char

	bigint &operator+=(const bigint &other) {
		if (sign == other.sign) {
			for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
				if (i == sz(z)) z.pb(0);
				z[i] += carry+(i<sz(other.z)?other.z[i]:0);
				carry = z[i] >= base; if (carry) z[i] -= base;
			}
		} else if (other != 0 /* prevent infinite loop */) *this -= -other;
		return *this;
	}
	friend bigint operator+(bigint a, const bigint &b) { return a += b; }
	bigint &operator-=(const bigint &other) {
		if (sign == other.sign) {
			if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
				for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
					z[i] -= carry+(i<sz(other.z)?other.z[i]:0);
					carry = z[i]<0; if (carry) z[i] += base;
				}
				trim();
			} else { // result will change sign
				*this = other-*this;
				this->sign = -this->sign;
			}
		} else *this += -other;
		return *this;
	}
	friend bigint operator-(bigint a, const bigint &b) { return a -= b; }

	bigint &operator*=(int v) { // oops make sure not to multiply by ll ...
		if (v < 0) sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < sz(z) || carry; ++i) {
			if (i == sz(z)) z.pb(0);
			ll cur = (ll)z[i]*v+carry;
			carry = cur/base; z[i] = cur%base;
		}
		trim(); return *this;
	}
	bigint operator*(int v) const { return bigint(*this) *= v; }
	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base/(b1.z.back()+1);
		bigint a = a1.abs()*norm, b = b1.abs()*norm, q, r; // make last element of b big
		q.z.resize(sz(a.z));
		R0F(i,sz(a.z)) {
			r *= base; r += a.z[i];
			int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
			int s2 = sz(b.z)-1 < sz(r.z) ? r.z[sz(b.z)-1] : 0;
			int d = ((ll)s1*base+s2)/b.z.back(); // best approximation
			r -= b*d; while (r < 0) r += b, --d;
			q.z[i] = d;
		}
		q.sign = a1.sign*b1.sign; r.sign = a1.sign;
		q.trim(); r.trim(); return {q,r/norm};
	}
	friend bigint sqrt(const bigint &a1) {
		bigint a = a1; while (!sz(a.z) || sz(a.z)&1) a.z.pb(0);
		int n = sz(a.z), firstDigit = ::sqrt((double)a.z[n-1]*base+a.z[n-2]);
		int norm = base/(firstDigit+1); a *= norm; a *= norm;
		while (!sz(a.z) || sz(a.z)&1) a.z.pb(0);
		bigint r = (ll)a.z[n-1]*base+a.z[n-2];
		firstDigit = (int)::sqrt((double)a.z[n-1]*base+a.z[n-2]);
		int q = firstDigit; bigint res;
		R0F(j,n/2) {
			for (;; --q) {
				bigint r1 = (r-(res*2*base+q)*q)*base*base +
							(j>0?(ll)a.z[2*j-1]*base+a.z[2*j-2]:0);
				if (r1 >= 0) { r = r1; break; }
			}
			res *= base; res += q; // add a bit to sqrt
			if (j > 0) {
				int d1 = sz(res.z)+2 < sz(r.z) ? r.z[sz(res.z)+2] : 0; // always 0/1?
				int d2 = sz(res.z)+1 < sz(r.z) ? r.z[sz(res.z)+1] : 0;
				int d3 = sz(res.z) < sz(r.z) ? r.z[sz(res.z)] : 0;
				q = ((ll) d1*base*base+(ll)d2*base+d3)/(firstDigit*2);
			}
		}
		res.trim(); return res/norm;
	}
	bigint operator/(const bigint &v) const { return divmod(*this, v).first; }
	bigint operator%(const bigint &v) const { return divmod(*this, v).second; }
	bigint &operator/=(int v) {
		if (v < 0) sign = -sign, v = -v;
		for (int i = sz(z)-1, rem = 0; i >= 0; --i) {
			ll cur = z[i]+rem*(ll)base;
			z[i] = cur/v; rem = cur%v;
		}
		trim(); return *this;
	}
	bigint operator/(int v) const { return bigint(*this) /= v; }
	int operator%(int v) const {
		if (v < 0) v = -v;
		int m = 0; R0F(i,sz(z)) m = (z[i]+m*(ll)base)%v;
		return m*sign; }
	bigint &operator*=(const bigint &v) { return *this = *this*v; }
	bigint &operator/=(const bigint &v) { return *this = *this/v; }

	bool operator<(const bigint &v) const {
		if (sign != v.sign) return sign < v.sign;
		if (sz(z) != sz(v.z)) return sz(z)*sign < sz(v.z) * v.sign;
		R0F(i,sz(z)) if (z[i] != v.z[i]) return z[i]*sign < v.z[i]*sign;
		return 0; // equal
	}
	bool operator>(const bigint &v) const { return v < *this; }
	bool operator<=(const bigint &v) const { return !(v < *this); }
	bool operator>=(const bigint &v) const { return !(*this < v); }
	bool operator==(const bigint &v) const { return !(*this < v) && !(v < *this); }
	bool operator!=(const bigint &v) const { return *this < v || v < *this; }
	void trim() {
		while (sz(z) && z.back() == 0) z.pop_back();
		if (!sz(z)) sign = 1; // don't output -0
	}
	bool isZero() const { return !sz(z); }
	friend bigint operator-(bigint v) {
		if (sz(v.z)) v.sign = -v.sign;
		return v; }
	bigint abs() const { return sign == 1 ? *this : -*this; }
	ll longValue() const {
		ll res = 0; R0F(i,sz(z)) res = res*base+z[i];
		return res*sign; }
	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b); } // euclidean algo
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a/gcd(a, b) * b; }

	void read(const string &s) {
		sign = 1; z.clear(); int pos = 0;
		while (pos < sz(s) && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-') sign = -sign;
			++pos; } // account for sign
		for (int i = sz(s)-1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i-base_digits+1); j <= i; j++)
				x = x*10+s[j]-'0';
			z.pb(x);
		}
		trim();
	}
	friend istream &operator>>(istream &is, bigint &v) {
		string s; is >> s; v.read(s); return is; }
	friend ostream &operator<<(ostream &os, const bigint &v) {
		if (v.sign == -1) os << '-';
		os << (!sz(v.z) ? 0 : v.z.back());
		R0F(i,sz(v.z)-1) os << setw(base_digits) << setfill('0') << v.z[i];
		return os; // pad with zeroes
	}
	static vt<int> convert_base(const vt<int> &a, int old_digits, int new_digits) {
		vt<ll> p(max(old_digits, new_digits) + 1); // blocks of 10^{old} -> 10^{new}
		p[0] = 1; for (int i =1;i<sz(p);i++) p[i] = p[i-1]*10;
		vt<int> res; ll cur = 0; int cur_digits = 0;
		for (int v:a) {
			cur += v*p[cur_digits]; cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.pb(cur%p[new_digits]);
				cur /= p[new_digits]; cur_digits -= new_digits;
			}
		}
		res.pb(cur); while (sz(res) && res.back() == 0) res.pop_back();
		return res;
	}
	static vt<ll> karatMul(const vt<ll> &a, const vt<ll> &b) { // karatsuba
		int n = sz(a); vt<ll> res(2*n);
		if (n <= 32) { // naive multiply
			F0R(i,n) F0R(j,n) res[i+j] += a[i]*b[j];
			return res; }
		int k = n/2;
		vt<ll> a1(begin(a),begin(a)+k), a2(k+all(a));
		vt<ll> b1(begin(b),begin(b)+k), b2(k+all(b));
		vt<ll> a1b1 = karatMul(a1, b1), a2b2 = karatMul(a2, b2);
		F0R(i,k) a2[i] += a1[i], b2[i] += b1[i];
		vt<ll> r = karatMul(a2, b2); // three instead of four products
		F0R(i,sz(a1b1)) r[i] -= a1b1[i];
		F0R(i,sz(a2b2)) r[i] -= a2b2[i];
		F0R(i,sz(r)) res[i+k] += r[i];
		F0R(i,sz(a1b1)) res[i] += a1b1[i];
		F0R(i,sz(a2b2)) res[i+n] += a2b2[i];
		return res;
	}
	bigint operator*(const bigint &v) const {
		if (min(sz(z),sz(v.z)) < 150) return mul_simple(v);
		bigint res; res.sign = sign*v.sign; // should work as long as # of digits isn't too large (> LLONG_MAX/10^{12})
		vt<int> a6 = convert_base(this->z, base_digits, 6); // blocks of 10^6 instead of 10^9
		vt<int> b6 = convert_base(v.z, base_digits, 6);
		vt<ll> a(all(a6)), b(all(b6));
		while (sz(a) < sz(b)) a.pb(0);
		while (sz(b) < sz(a)) b.pb(0);
		while (sz(a)&(sz(a)-1)) a.pb(0), b.pb(0); // make size power of 2
		vt<ll> c = karatMul(a, b);
		ll cur = 0; for (int i =0 ;i<sz(c);i++) { // process carries
			cur += c[i]; res.z.pb(cur%1000000); cur /= 1000000; } 
		res.z = convert_base(res.z,6,base_digits); 
		res.trim(); return res;
	}
	bigint mul_simple(const bigint &v) const {
		bigint res; res.sign = sign*v.sign;
		res.z.resize(sz(z)+sz(v.z));
		F0R(i,sz(z)) if (z[i]) {
			ll cur = 0; for (int j = 0; j < sz(v.z) || cur; ++j) {
				cur += res.z[i+j]+(ll)z[i]*(j<sz(v.z)?v.z[j]:0);
				res.z[i+j] = cur%base; cur /= base;
			}
		}
		res.trim(); return res;
	}
#undef F0R
#undef R0F
};