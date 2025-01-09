#include <algorithm>
#include <iostream>

typedef long long ll;
const int MAX = 5e4 + 5;
const int MAXX = 5e5 + 5;

int n, m, s, K, k, l, r, cnt, _cnt, mn = MAX, mx = -MAX;
ll res, ans;
int f[MAX];

struct E {
  int u, v, w;
} e[MAXX];

inline bool cmp(E a, E b) { return a.w < b.w; }

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

void init() {
  _cnt = cnt = res = 0;
  std::sort(e + 1, e + m + 1, cmp);
  for (int i = 1; i <= n; ++i) {
    f[i] = i;
  }
}

void solve() {
  init();
  for (int i = 1; i <= m && _cnt < n - 1; ++i) {
    int fu = find(e[i].u), fv = find(e[i].v);
    if (fu == fv) {
      continue;
    }
    ++_cnt;
    res += e[i].w;
    cnt += (e[i].u == s || e[i].v == s);
    f[fv] = fu;
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &s, &K);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    r = std::max(r, e[i].w);
  }
  l = -r;
  while (l <= r) {
    k = l + ((r - l) >> 1);
    for (int i = 1; i <= m; ++i) {
      if (e[i].u == s || e[i].v == s) {
        e[i].w += k;
      }
    }
    solve();
    if (cnt < K) {
      r = k - 1;
    } else {
      ans = res - k * K;
      l = k + 1;
    }
    mx = std::max(mx, cnt), mn = std::min(mn, cnt);
    for (int i = 1; i <= m; ++i) {
      if (e[i].u == s || e[i].v == s) {
        e[i].w -= k;
      }
    }
  }
  if (K > mx || K < mn) {
    printf("Impossible");
    return 0;
  }
  printf("%lld", ans);
}
