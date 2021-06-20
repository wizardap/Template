/*
  Source: VNOI
  Modified by WizardAP
  Verification: 
      - https://oj.vnoi.info/problem/substr
 */
/// This is made for 1-based range
const int base=29;
const LL MOD=1e9+7;
LL pw[mxn];
void precompute(int Leng)
{
    for (int i = 0; i <= Leng; i++)
        pw[i] = i == 0 ? 1 : (pw[i - 1] * base) % MOD;
}
struct PolyHash
{
    vector<LL> hash;
    int n;
    void init_hash(const string& s)
    {
        n = (int)s.size();
        hash.resize(n + 5, 0);
        for (int i = 0; i < n; i++)
            hash[i + 1] = (hash[i] * base + (s[i] - 'a' + 1) ) % MOD;
    }
    LL gethash(int pos) {
        return hash[pos];
    }
    LL gethash(int l, int r)
    {
        return ((hash[r] - hash[l - 1] * pw[r - l + 1]) % MOD + MOD) % MOD;
    }
};
