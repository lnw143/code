// Problem: G - 16 Integers
// Contest: AtCoder - AtCoder Beginner Contest 336
// URL: https://atcoder.jp/contests/abc336/tasks/abc336_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 1000100;
const int N = 1000000;
const ll mod = 998244353;

inline ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

ll b[19][19], in[19], out[19], fac[maxn], ifac[maxn], fa[19], id[19], di[19], m, a[19][19];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		fa[x] = y;
	}
}

inline ll det() {
	ll ans = 1;
	for (int i = 1; i < m; ++i) {
		for (int j = i; j < m; ++j) {
			if (a[j][i]) {
				if (i != j) {
					swap(a[i], a[j]);
					ans = (mod - ans) % mod;
				}
			}
		}
		if (!a[i][i]) {
			return 0;
		}
		ans = ans * a[i][i] % mod;
		ll t = qpow(a[i][i], mod - 2);
		for (int j = i; j < m; ++j) {
			a[i][j] = a[i][j] * t % mod;
		}
		for (int j = 1; j < m; ++j) {
			if (i == j) {
				continue;
			}
			ll t = (mod - a[j][i]) % mod;
			for (int k = i + 1; k < m; ++k) {
				a[j][k] = (a[j][k] + t * a[i][k]) % mod;
			}
		}
	}
	return ans;
}

inline void init() {
	fac[0] = 1;
	for (int i = 1; i <= N; ++i) {
		fac[i] = fac[i - 1] * i % mod;
	}
	ifac[N] = qpow(fac[N], mod - 2);
	for (int i = N - 1; ~i; --i) {
		ifac[i] = ifac[i + 1] * (i + 1) % mod;
	}
}

inline ll calc(int s, int t) {
	mems(a, 0);
	for (int i = 1; i <= m; ++i) {
		int x = i;
		if (i == s || i == m) {
			x ^= (s ^ m);
		}
		a[x][x] = (i == s ? in[di[i]] + 1 : in[di[i]]);
	}
	for (int i = 1; i <= m; ++i) {
		int x = i;
		if (i == s || i == m) {
			x ^= (s ^ m);
		}
		for (int j = 1; j <= m; ++j) {
			int y = j;
			if (j == s || j == m) {
				y ^= (s ^ m);
			}
			a[x][y] = (a[x][y] - b[di[i]][di[j]] + mod) % mod;
			if (i == t && j == s) {
				a[x][y] = (a[x][y] + mod - 1) % mod;
			}
		}
	}
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=m; ++j)
			printf("%d%c",a[i][j]," \n"[j==m]);
	ll ans = det();
	for (int i = 1; i <= m; ++i) {
		ans = ans * fac[(i == t ? out[di[i]] + 1 : out[di[i]]) - 1] % mod;
	}
	return ans;
}

void solve() {
	for (int i = 0; i < 16; ++i) {
		scanf("%lld", &b[i >> 1][i & 7]);
	}
	for (int i = 0; i < 8; ++i) {
		fa[i] = i;
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			out[j] += b[i][j];
			in[i] += b[i][j];
			if (b[i][j]) {
				merge(i, j);
			}
		}
	}
	int p = -1, s = -1, t = -1;
	for (int i = 0; i < 8; ++i) {
		if (!in[i] && !out[i]) {
			continue;
		}
		id[i] = ++m;
		di[m] = i;
		if (in[i] > out[i]) {
			if (in[i] > out[i] + 1 || t != -1) {
				puts("0");
				return;
			}
			t = m;
		} else if (in[i] < out[i]) {
			if (in[i] < out[i] - 1 || s != -1) {
				puts("0");
				return;
			}
			s = m;
		}
		if (p == -1) {
			p = find(i);
		} else if (p != find(i)) {
			puts("0");
			return;
		}
	}
	ll ans = 0;
	if (s != -1) {
		ans = calc(s, t);
	} else {
		for (int i = 1; i <= m; ++i) {
			ans = (ans + calc(i, i)) % mod;
		}
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			ans = ans * ifac[b[i][j]] % mod;
		}
	}
	printf("%lld\n", ans);
}

int main() {
	init();
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
