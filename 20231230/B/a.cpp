#include <fstream>
#include <vector>
#include <functional>
#include <cstring>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pi;
const int N = 2e5 + 5, inf = 1e9;
ifstream cin("tree.in");
ofstream cout("tree.out");
struct sgt {
	int mx[N * 4], cnt[N * 4], tag[N * 4];
	void pushup(int d) {
		mx[d] = max(mx[(d * 2)], mx[(d * 2 + 1)]);
		cnt[d] = (mx[(d * 2)] == mx[d] ? cnt[(d * 2)] : 0) + (mx[(d * 2 + 1)] == mx[d] ? cnt[(d * 2 + 1)] : 0);
	} void f(int d, int nw) {
		mx[d] += nw;
		tag[d] += nw;
	} void pushdown(int d) {
		if (tag[d]) {
			f((d * 2), tag[d]);
			f((d * 2 + 1), tag[d]);
			tag[d] = 0;
		}
	} void Set(int d, int l, int r, int nd, int val) {
		if (l == r) {
			mx[d] = val;
			cnt[d] = 1;
			return;
		}
		pushdown(d);
		nd <= ((l + r) / 2) ? Set((d * 2), l, ((l + r) / 2), nd, val) : Set((d * 2 + 1), ((l + r) / 2) + 1, r, nd, val);
		pushup(d);
	} void add(int d, int l, int r, int nl, int nr, int nw) {
		if (nl <= l && r <= nr) {
			f(d, nw);
			return;
		}
		pushdown(d);
		if (nl <= ((l + r) / 2)) {
			add((d * 2), l, ((l + r) / 2), nl, nr, nw);
		}
		if (nr > ((l + r) / 2)) {
			add((d * 2 + 1), ((l + r) / 2) + 1, r, nl, nr, nw);
		}
		pushup(d);
	}
} T;
void solve() {
	int n, t;
	cin >> n >> t;
	vi f(n + 1, 0), a(n + 1, 0);
	vector<vi> G(n + 1);
	for (int i = (t + 1); i <= (n); i++) {
		cin >> f[i];
		G[f[i]].push_back(i);
	}
	for (int i = (1); i <= (n); i++) {
		cin >> a[i];
	}
	vi dfn(n + 1, 0), sz(n + 1, 0);
	int dfc = 0;
	memset(&T, 0, sizeof(T));
	function<void(int, int)> dfs0 = [&](int u, int cdis) {
		sz[u] = 1;
		dfn[u] = ++dfc;
		T.Set(1, 1, n, dfc, a[u] ? cdis : -inf);
		for (int v : G[u]) {
			dfs0(v, cdis + 1);
			sz[u] += sz[v];
		}
	};
	for (int i = (1); i <= (t); i++) {
		dfs0(i, min(i - 1, t + 1 - i));
	}
	vi dis(n + 1, 0);
	function<void(int)> dfs1 = [&](int u) {
		if (!a[u]) {
			dis[u] = T.mx[1];
		}
		for (int v : G[u]) {
			T.add(1, 1, n, 1, n, 1);
			T.add(1, 1, n, dfn[v], dfn[v] + sz[v] - 1, -2);
			dfs1(v);
			T.add(1, 1, n, 1, n, -1);
			T.add(1, 1, n, dfn[v], dfn[v] + sz[v] - 1, 2);
		}
	};
	for (int i = (1); i <= (t); i++) {
		dfs1(i);
		if (i == t) {
			break;
		}
		int ri = i + t / 2, le = ri + 1 + (t % 2 == 1);
		if (ri <= t) {
			T.add(1, 1, n, dfn[i + 1], dfn[ri] + sz[ri] - 1, -1);
		} else {
			T.add(1, 1, n, dfn[i + 1], n, -1);
			T.add(1, 1, n, 1, dfn[ri - t] + sz[ri - t] - 1, -1);
		}
		if (le <= t) {
			T.add(1, 1, n, dfn[le], n, 1);
			T.add(1, 1, n, 1, dfn[i] + sz[i] - 1, 1);
		} else {
			T.add(1, 1, n, dfn[le - t], dfn[i] + sz[i] - 1, 1);
		}
	}
	function<void(int, int)> dfs2 = [&](int u, int cdis) {
		T.Set(1, 1, n, dfn[u], a[u] ? -inf : cdis - dis[u]);
		for (int v : G[u]) {
			dfs2(v, cdis + 1);
		}
	};
	int ans = 0;
	function<void(int)> dfs3 = [&](int u) {
		if (a[u]) {
			if (T.mx[1] == 0) {
				ans = max(ans, T.cnt[1]);
			}
		}
		for (int v : G[u]) {
			T.add(1, 1, n, 1, n, 1);
			T.add(1, 1, n, dfn[v], dfn[v] + sz[v] - 1, -2);
			dfs3(v);
			T.add(1, 1, n, 1, n, -1);
			T.add(1, 1, n, dfn[v], dfn[v] + sz[v] - 1, 2);
		}
	};
	for (int i = (1); i <= (t); i++) {
		dfs2(i, min(i - 1, t + 1 - i));
	}
	for (int i = (1); i <= (t); i++) {
		dfs3(i);
		if (i == t) {
			break;
		}
		int ri = i + t / 2, le = ri + 1 + (t % 2 == 1);
		if (ri <= t) {
			T.add(1, 1, n, dfn[i + 1], dfn[ri] + sz[ri] - 1, -1);
		} else {
			T.add(1, 1, n, dfn[i + 1], n, -1);
			T.add(1, 1, n, 1, dfn[ri - t] + sz[ri - t] - 1, -1);
		}
		if (le <= t) {
			T.add(1, 1, n, dfn[le], n, 1);
			T.add(1, 1, n, 1, dfn[i] + sz[i] - 1, 1);
		} else {
			T.add(1, 1, n, dfn[le - t], dfn[i] + sz[i] - 1, 1);
		}
	}
	cout << ans << endl;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}