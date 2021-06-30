/*
 Resource: https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/KMP.h
 Verification : 
    - https://codeforces.com/contest/1200/submission/88400452
    - https://oj.vnoi.info/problem/substr
*/
//// #define sz(x)      (int)(x).size()
//// define pb        push_back
vector<int> kmp(const string& a)
{
  int n = (int)a.size(); vector<int>p(n);
  for (int i = 1, k = 0; i < n; i++)
  {
    k = p[i - 1];
    while (k > 0 && a[k] != a[i]) k = p[k - 1];
    if (a[k] == a[i]) k++; p[i] = k;
  }
  return p;
}
vector<int> match(const string& s, const string& pat)
{
  vector<int> p = kmp(pat + "." + s), res;
  for (int i = sz(p) - sz(s); i < sz(p); i++)
    if (p[i] == sz(pat)) res.pb(i - 2 * sz(pat));
  return res;
}

