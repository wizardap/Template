/*
    Verification:
        - https://oj.vnoi.info/problem/lites
        - https://oj.vnoi.info/problem/qmax2
    Usage: 
            - Despite of the problem, you can change some function to solve those problems
            - This is 1-based Segment Tree + Lazy Propagate
*/

template<int sz, typename seg_t>
struct LazyTree
{
  seg_t seg[4 * sz];
  seg_t lz[4 * sz];
  const seg_t NO_OPERATION = -1;
  const seg_t NEUTRAL_OPERATION = 0;
  const seg_t INIT_VAL = 0;
  int N;
  void init_tree(int n)
  {
    N = n;
    for (int i = 0; i <= 4 * N; i++) {
      seg[i] = INIT_VAL;
      lz[i] = NO_OPERATION;
    }
  }
  seg_t comb(seg_t x, seg_t y)
  {
    return x + y;
  }
  seg_t modify(seg_t a, seg_t b, int len)
  {
    if (a == NO_OPERATION) return b;
    if (b == NO_OPERATION) return a;
    return a ^ b;
  }
  void push(int id, int l, int r)
  {
    if (lz[id] == NO_OPERATION) return ;
    if (lz[id] == 1)  seg[id] = (r - l + 1) - seg[id];
    if (l != r) for (int i = 0; i < 2; i++) lz[2 * id + i] = modify(lz[2 * id + i], lz[id], 1);
    lz[id] = NO_OPERATION;
  }
  void build(seg_t *a, int id, int l, int r)
  {
    if (l == r) { seg[id] = a[l]; return; };
    int mid = (l + r) >> 1;
    build(a, id * 2, l, mid); build(a, id * 2 + 1, mid + 1, r);
    seg[id] = comb(seg[id * 2], seg[id * 2 + 1]);
  }
  void upd(int u, int v, seg_t val, int id, int l, int r)
  {
    push(id, l, r);
    if (v < l || r < u) return;
    if (u <= l && r <= v)
    {
      lz[id] = modify(lz[id], val, 1);
      push(id, l, r);
      return ;
    }
    int mid = (l + r) >> 1;
    upd(u, v, val, id * 2, l, mid);
    upd(u, v, val, id * 2 + 1, mid + 1, r);
    seg[id] = comb(seg[id * 2], seg[id * 2 + 1]);
  }
  seg_t get(int u, int v, int id , int l , int r)
  {
    push(id, l, r);
    if (v < l || r < u) return NEUTRAL_OPERATION;
    if (u <= l && r <= v) return seg[id];
    int mid = (l + r) >> 1;
    return comb(get(u, v, id * 2, l, mid), get(u, v, id * 2 + 1, mid + 1, r));
  }
  void build(seg_t *a) { build(a, 1, 1, N);}
  void upd(int u, int v, seg_t val) { upd(u, v, val, 1, 1, N);}
  seg_t get(int u, int v) { return get(u, v, 1, 1, N);}
};


/// Example : LazyTree<100004,int > st;
