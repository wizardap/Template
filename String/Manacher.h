/*
  Resource: cp-algorithm
  Verification: 
    - https://oj.vnoi.info/problem/paliny
 */

int manacher(string s)
{
  int res = 0; string y = ".";
  for (int i = 0; i < s.size(); i++)y += s[i], y += ".";
  int n = (int)y.size();
  vector<int> f(n + 1);
  for (int i = 1, r = 0, c = 0; i < n; i++)
  {
    f[i] = i < r ? min(r - i, f[2 * c - i]) : 0;
    while (y[i + f[i] + 1] == y[i - f[i] - 1] && i + f[i] + 1 < n && i - f[i] - 1 >= 0) f[i]++;
    res = max(res, f[i]);
    if (i + f[i] > r) {c = i; r = i + f[i];}
  }
  return res;
}
