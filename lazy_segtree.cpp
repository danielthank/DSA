// https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_d
#include <bits/stdc++.h>
// #include <atcoder/all>

// using namespace atcoder;
using namespace std;
using ll = long long;

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
public:
  lazy_segtree() : lazy_segtree(0) {}
  lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
  lazy_segtree(const vector<S>& v) : _n(int(v.size())) {
    log = 0;
    while ((1U) << log < (unsigned int)_n) log++;
    size = 1 << log;
    d = std::vector<S>(2 * size, e());
    lz = std::vector<F>(size, id());
    for (int i = 0; i < _n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) {
      update(i);
    }
  }

  void apply(int l, int r, F f) {
    if (l == r) return;

    l += size, r += size;
    // ensure all lazy is propagated in the path
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    // apply f
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }

    // update data due to data change
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  S prod(int l, int r) {
    if (l == r) return e();

    l += size, r += size;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push(r >> i);
    }

    S sml = e(), smr = e();
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }

    return op(sml, smr);
  }
private:
  int _n, size, log;
  vector<S> d;
  vector<F> lz;

  // Update data due to children data updated
  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  // Apply f to both data and lazy
  void all_apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if (k < size) lz[k] = composition(f, lz[k]);
  }
  // guarantee that lz is propagated
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }
};

struct S {
  ll v;
  int cnt;
  S(ll v, ll cnt) : v(v), cnt(cnt) {};
};

S op(S a, S b) {
  return S(a.v + b.v, a.cnt + b.cnt);
}

S e() {
  return S(0, 1);
}

struct F {
  bool r;
  ll v;
  F(bool r, ll v) : r(r), v(v) {};
};

S mapping (F f, S x) {
  if (f.r) return S(f.v * x.cnt, x.cnt);
  return S(x.v + f.v * x.cnt, x.cnt);
}

F composition(F f, F g) {
  if (f.r) return f;
  return F(g.r, f.v + g.v);
}

F id() {
  return F(false, 0);
}

int main() {
  int n, m;
  cin >> n >> m;
  lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
  int pre = 0;
  ll ans = 0;
  while (m--) {
    int t, l, r;
    cin >> t >> l >> r;
    --l;
    seg.apply(0, n, F(false, t-pre));
    ans += seg.prod(l, r).v;
    seg.apply(l, r, F(true, 0));
    pre = t;
  }
  printf("%lld\n", ans);
  return 0;
}
