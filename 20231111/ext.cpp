#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
#define N 100010
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
ll n, m;

ll qpow(ll n, ll p) {
	if(p == 0) return 1;
	if(p % 2 == 1) return n*qpow(n, p-1);
	ll tmp = qpow(n, p/2);
	return tmp*tmp;
}

struct node {
	ll mx, siz;
} t[4*N];

node add(node x, node y) {
	x.mx = max(x.mx, y.mx);
	x.siz += y.siz;
	return x;
}

ll lazy[4*N];	// 翻了多少倍

/* 捋一下思路：两颗线段树
  线段树1我打算维护区间数量最多的那种细胞的数量，然后二分判定实际位置
  然后我先要打线段树2，线段树2维护区间开始位置，用于线段树1的二分*/

/*前面思路完全错误，想到一个更好的，维护区间长度和区间最大，二分即可
  太优秀了，nlog^2n，n=10^5*/

void pushup(ll pos) {
	t[pos].mx = max(t[ls(pos)].mx, t[rs(pos)].mx);
	t[pos].siz = t[ls(pos)].siz + t[rs(pos)].siz;
}

void f(ll k, ll pos) {
	t[pos].mx *= qpow(2, k);
	t[pos].siz *= qpow(2, k);
	lazy[pos] += k;
}

void pushdown(ll pos) {
	f(lazy[pos], ls(pos));
	f(lazy[pos], rs(pos));
	lazy[pos] = 0;
}

void build(ll l, ll r, ll pos) {
	if(l == r) {
		t[pos].mx = t[pos].siz = 1;
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(pos));
	build(mid + 1, r, rs(pos));
	
	pushup(pos);
}

void update(ll nl, ll nr, ll l, ll r, ll pos) {
	if(nl <= l && r <= nr) {
		t[pos].mx *= 2;
		t[pos].siz *= 2;
		lazy[pos]++;
		return;
	}
	pushdown(pos);
	
	ll mid = (l + r) >> 1;
	
	if(nl <= mid)
		update(nl, nr, l, mid, ls(pos));
	if(mid < nr)
		update(nl, nr, mid + 1, r, rs(pos));
	
	pushup(pos);
}

void updateone(ll x, ll l, ll r, ll pos, ll k) {
	if(x <= l && r <= x) {
		t[pos].mx += k;
		t[pos].siz += k;
		return;
	}
	pushdown(pos);
	
	ll mid = (l + r) >> 1;
	
	if(x <= mid)
		updateone(x, l, mid, ls(pos), k);
	if(mid < x)
		updateone(x, mid + 1, r, rs(pos), k);
	
	pushup(pos);
}

node query(ll nl, ll nr, ll l, ll r, ll pos) {
	if(nl > nr) return node({0, 0});
	if(nl <= l && r <= nr) {
		return t[pos];
	}
	pushdown(pos);
	
	ll mid = (l + r) >> 1;
	
	node res;res.mx = 0, res.siz = 0;
	
	if(nl <= mid)
		res = add(res, query(nl, nr, l, mid, ls(pos)));
	if(mid < nr)
		res = add(res, query(nl, nr, mid + 1, r, rs(pos)));
	
	return res;
}

ll gt(ll x, ll l, ll r, ll pos) {
	if(l == r) {
		return l;
	}
	
	pushdown(pos);
	ll mid = (l + r) >> 1;
	
	if(x <= t[ls(pos)].siz)
		return gt(x, l, mid, ls(pos));
	else
		return gt(x - t[ls(pos)].siz, mid + 1, r, rs(pos));
}



int main() {
	freopen("experiment.in","r",stdin);
	freopen("experiment.ans","w",stdout);
//	freopen("C://experiment4.in", "r", stdin);
	scanf("%lld %lld", &n, &m);
	build(1, n, 1);
	while(m--) {
		char op[10];
		ll l, r;
		scanf("%s %lld %lld", op, &l, &r);
		if(op[0] == 'D') {
			ll st = gt(l, 1, n, 1), ed = gt(r, 1, n, 1);
			if(l > query(1, st - 1, 1, n, 1).siz + 1) st++;
			if(query(1, ed, 1, n, 1).siz > r) ed--;
//			printf("Debug:%lld %lld\n", st, ed);
			//       st的起点 - 查询的起点 = 多算的点数        查询的终点 - ed的终点 = 多算的点数
			ll a = (query(1, st - 1, 1, n, 1).siz + 1) - l, b = r - (query(1, ed, 1, n, 1).siz);
			if(st <= ed) update(st, ed, 1, n, 1);
			if(st - 1 == ed + 1) updateone(st - 1, 1, n, 1, r-l+1);	// 是同一个，但我不知道怎么修，直接特判吧
			else {
				if(st - 1 >= 1) updateone(st - 1, 1, n, 1, a);
				if(ed + 1 <= n) updateone(ed + 1, 1, n, 1, b);
			}
		} else if(op[0] == 'Q') {
			ll st = gt(l, 1, n, 1), ed = gt(r, 1, n, 1);
			if(l > query(1, st - 1, 1, n, 1).siz + 1) st++;
			if(query(1, ed, 1, n, 1).siz > r) ed--;
//			printf("Debug:%lld %lld\n", st, ed);
			ll a = (query(1, st - 1, 1, n, 1).siz + 1) - l, b = r - (query(1, ed, 1, n, 1).siz);
			ll ans = query(st, ed, 1, n, 1).mx;
			if(st - 1 == ed + 1) ans = max(ans, r - l + 1);	// 是同一个，但我不知道怎么修，直接特判吧
			else {
				ans = max(ans, a);
				ans = max(ans, b);
			}
			printf("%lld\n", ans);
		}
//		for(ll i = 1; i <= n; i++) {
//			printf("%lld ", query(i, i, 1, n, 1).siz);
//		}
//		printf("\n");
	}
}
