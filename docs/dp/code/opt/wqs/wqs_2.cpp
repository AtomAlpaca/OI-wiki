#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

const int MAX = 1e5 + 5;

int n, m, k, u, v, w, c, cnt, res, ans;
int f[MAX];
struct E { int u, v, w, c; } e[MAX];

int find(int x) { if (f[x] == x) { return x; } return f[x] = find(f[x]); }
bool cmp(E a, E b) { if (a.w == b.w) { return a.c < b.c; } return a.w < b.w; }

void check(int x)
{
	res = cnt = 0;
	for (int i = 1; i <= m; ++i) { if (e[i].c == 0) { e[i].w += x; } }
	for (int i = 1; i <= n; ++i) { f[i] = i; }
	std::sort(e + 1, e + m + 1, cmp);
	for (int i = 1, tmp = 0; i <= m and tmp != n - 1; ++i)
	{
		int fu = find(e[i].u), fv = find(e[i].v);
		if (fu == fv) { continue; }
		f[fv] = fu; if (e[i].c == 0) { ++cnt; } res += e[i].w; ++tmp;
	}
	for (int i = 1; i <= m; ++i) { if (e[i].c == 0) { e[i].w -= x; } }
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; ++i)
	{
		cin >> u >> v >> w >> c;
		e[i] = {u + 1, v + 1, w, c};
	}
	int l = -111, r = 111, mid = 0;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		check(mid);
		if (cnt < k) { r = mid - 1; } else { l = mid + 1; ans = res - k * mid; }
	}
	cout << ans;
	return 0;
}
