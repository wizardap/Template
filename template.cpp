///WizardAP - 当你休息的时候，很多人比你付出更多的努力！不放弃 ！
#include<bits/stdc++.h>
using namespace std;
#define Nothing                 ""
#define ft                      first
#define sd                      second
#define pb                      push_back
#define pf                      push_front
#define eb                      emplace_back
#define sz(x)                   (int)(x).size()
#define vt                      vector
#define all(x)                  (x).begin(),(x).end()
#define aln(x,y)                (x)+1,(x)+1+(y)
#define cntone(x)          __builtin_popcountll((x))
#define each(x,y)          for (auto &x: y)
#define KwanJi                  freopen(Nothing".inp","r",stdin),freopen(Nothing".out","w",stdout)
#define Mitsuha                 ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)

template<class T, class Y> T offbit(T mask, Y pos) { return (mask & ~((T)1 << pos));}
template<class T, class Y> T onbit(T mask, Y pos) {return (mask | ((T)1 << pos));}
template<class T, class Y> T getbit(T mask, Y pos) {return ((mask >> (T)pos) & (T)1);}
template<class T1, class T2> bool ckmin(T1 &x, T2 y) { return (x > y ? x = y, 1 : 0);}
template<class T1, class T2> bool ckmax(T1 &x, T2 y) { return (x < y ? x = y, 1 : 0);}
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using ll = long long;
using ull = unsigned long long;
using ld = long double;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const int INF = 1e9;
const ld eps = 1e-9;
const ld PI = acos(-1.0);
ll fmul(ll a, ll b, ll MOD = mod) {a %= MOD; b %= MOD; ll q = (ld)a * b / MOD; ll r = a * b - q * MOD; return (r % MOD + MOD) % MOD;}
///Head

void Solve()
{
   
}
signed main()
{
   Mitsuha;
   int TC=1;
   cin >> TC;
   while (TC--) Solve();

}
/// 1d1l1p!