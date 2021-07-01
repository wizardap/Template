/* 
  Modified by WizardAP
  Verification : 
    - https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/submission/119465053  ( Join group) 
    
 */
const int matrix_size = 3;
const int mod = 1e9 + 7;
struct matrix {
    LL v[matrix_size][matrix_size];
    matrix() {memset(v, 0, sizeof v);}
    void print()
    {
        for (int i = 0; i < 2; i++, cout << "\n")
            for (int j = 0; j < 2; j++) cout << v[i][j] << " ";
    }
};
matrix One()
{
    matrix c;
    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            c.v[i][j] = (i == j ? 1 : 0);
    return c;
}
matrix operator*(matrix a, matrix b)
{
    matrix c;
    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
        {
            c.v[i][j] = 0;
            for (int k = 0; k < matrix_size; k++)
                c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j]) % mod;
        }
    return c;
}
matrix operator^(matrix a, LL k)
{
    matrix res = One();
    for (; k > 0; k >= 1ll, a = a * a)
        if (k & 1ll) res = res * a;
    return res;
}
