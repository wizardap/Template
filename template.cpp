//np4s target ga vai
#include<bits/stdc++.h>
using namespace std;
#define ft                      first
#define sd                      second
#define pb                      push_back
#define pf                      push_front
#define eb                      emplace_back
#define sz(x)                   (int)(x).size()
#define all(x)                  (x).begin(),(x).end()
using ll = long long;
using ld = long double;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const int INF = 1e9;
const ld eps = 1e-9;

template<class T1, class T2> bool ckmin(T1 &x, T2 y) { return (x > y+eps ? x = y, 1 : 0);}
template<class T1, class T2> bool ckmax(T1 &x, T2 y) { return (x +eps< y ? x = y, 1 : 0);}

ll fmul(ll a, ll b, ll MOD = mod) {a %= MOD; b %= MOD; ll q = (ld)a * b / MOD; ll r = a * b - q * MOD; return (r % MOD + MOD) % MOD;}
///Head

signed main()
{
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   
   return 0;
}
