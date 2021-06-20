/* 
    - Source: VNOI
    - Modified by WizardAP
    *) Verification: 
        - https://oj.vnoi.info/problem/substr
*/


//// The larger the number of modules, the slower the program runs
const int NMOD = 4;
const int base = 257;
const LL modulo[] = {(LL)1e9 + 2277, (LL)1e9 + 5277, (LL)1e9 + 8277, (LL)1e9 + 9277};
LL pw[NMOD][mxn];
void precompute(int Leng)
{
    for (int j = 0; j < NMOD; j++)
        for (int i = 0; i <= Leng; i++)
            pw[j][i] = i == 0 ? 1 : (pw[j][i - 1] * base) % modulo[j];
}
struct Hash
{
    LL value[NMOD];
    Hash()
    {
        memset(value, 0, sizeof value);
    }
    Hash(char c)
    {
        for (int j = 0; j < NMOD; j++) value[j] = c;
    }
    Hash operator+(const Hash &x) const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++) {
            res.value[j] = value[j] + x.value[j];
            if (res.value[j] >= modulo[j]) res.value[j] -= modulo[j];
        }
        return res;
    }
    Hash operator-(const Hash &x) const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++)
        {
            res.value[j] = value[j] - x.value[j];
            if (res.value[j] < 0) res.value[j] += modulo[j];
        }
        return res;
    }
    Hash operator*(LL k)const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++)
            res.value[j] = 1LL * value[j] * k % modulo[j];
        return res;
    }
    bool operator<(const Hash &x)const
    {
        for (int j = 0; j < NMOD; j++)
            if (value[j] != x.value[j]) return (value[j] < x.value[j]);
        return false;
    }
    bool operator==(const Hash &x)const
    {
        for (int j = 0; j < NMOD; j++)
            if (value[j] != x.value[j]) return false;
        return true;
    }
} NO_OPERATION;

struct PolyHash
{
    vector<Hash> hash;
    int n;
    void init_hash(const string &s)
    {
        n = (int)s.size();
        hash.resize(n + 1, NO_OPERATION);
        for (int i = 0; i < n; i++)
            hash[i + 1] = hash[i] * base + Hash(s[i]);
    }
    Hash gethash()
    {
        return hash[n];
    }
    Hash gethash(int l, int r)
    {
        for (int j = 0; j < NMOD; j++)
            hash[l - 1].value[j] = (hash[l - 1].value[j] * pw[j][r - l + 1]) % modulo[j];
        return hash[r] - hash[l - 1];
    }
};
