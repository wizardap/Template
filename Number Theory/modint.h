/*
	Resource : https://github.com/drken1215/algorithm/blob/master/MathCombinatorics/mod.cpp
*/
template<long long Modulus=mod> struct modint {
    long long val;
    constexpr modint(long long v = 0) noexcept : val(v % Modulus) {
        if (val < 0) val += Modulus;
    }
    constexpr int getmod() const { return Modulus; }
    constexpr modint operator - () const noexcept {
        return val ? Modulus - val : 0;
    }
    constexpr modint operator + (const modint& r) const noexcept { return modint(*this) += r; }
    constexpr modint operator - (const modint& r) const noexcept { return modint(*this) -= r; }
    constexpr modint operator * (const modint& r) const noexcept { return modint(*this) *= r; }
    constexpr modint operator / (const modint& r) const noexcept { return modint(*this) /= r; }
    constexpr modint& operator += (const modint& r) noexcept {
        val += r.val;
        if (val >= Modulus) val -= Modulus;
        return *this;
    }
    constexpr modint& operator -= (const modint& r) noexcept {
        val -= r.val;
        if (val < 0) val += Modulus;
        return *this;
    }
    constexpr modint& operator *= (const modint& r) noexcept {
        val = val * r.val % Modulus;
        return *this;
    }
    constexpr modint& operator /= (const modint& r) noexcept {
        long long a = r.val, b = Modulus, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        val = val * u % Modulus;
        if (val < 0) val += Modulus;
        return *this;
    }
    constexpr bool operator == (const modint& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const modint& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr istream& operator >> (istream& is, modint<Modulus>& x) noexcept {
        is >> x.val;
        x.val %= Modulus;
        if (x.val < 0) x.val += Modulus;
        return is;
    }
    friend constexpr ostream& operator << (ostream& os, const modint<Modulus>& x) noexcept {
        return os << x.val;
    }
    friend constexpr modint<Modulus> modpow(const modint<Modulus>& r, long long n) noexcept {
        if (n == 0) return 1;
        if (n < 0) return modpow(modinv(r), -n);
        auto t = modpow(r, n / 2);
        t = t * t;
        if (n & 1) t = t * r;
        return t;
    }
    friend constexpr modint<Modulus> modinv(const modint<Modulus>& r) noexcept {
        long long a = r.val, b = Modulus, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        return modint<Modulus>(u);
    }
};

using mint = modint<mod>;

// Binomial coefficient
template<class T> struct BiCoef {
    vector<T> fact_, inv_, finv_;
    constexpr BiCoef() {}
    constexpr BiCoef(int n) noexcept : fact_(n, 1), inv_(n, 1), finv_(n, 1) {
        init(n);
    }
    constexpr void init(int n) noexcept {
        fact_.assign(n, 1), inv_.assign(n, 1), finv_.assign(n, 1);
        int Modulus = fact_[0].getmod();
        for(int i = 2; i < n; i++){
            fact_[i] = fact_[i-1] * i;
            inv_[i] = -inv_[Modulus%i] * (Modulus/i);
            finv_[i] = finv_[i-1] * inv_[i];
        }
    }
    constexpr T com(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return fact_[n] * finv_[k] * finv_[n-k];
    }
    constexpr T fact(int n) const noexcept {
        if (n < 0) return 0;
        return fact_[n];
    }
    constexpr T inv(int n) const noexcept {
        if (n < 0) return 0;
        return inv_[n];
    }
    constexpr T finv(int n) const noexcept {
        if (n < 0) return 0;
        return finv_[n];
    }
};
using bico = BiCoef<mint>;