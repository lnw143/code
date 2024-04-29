#pragma GCC optimize("O3,unroll-loops")

#include<cstdio>
#include<cmath>
#include<cstdint>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
#include<bitset>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdlib>
#include<complex>
#include<deque>
#include<functional>
#include<iostream>
#include<limits>
#include<numeric>
#include<iomanip>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>

#define rep(i,l,r) for(int i(l),i##End(r); i<=i##End; ++i)
#define rep_(i,l,r) for(int i(l),i##End(r); i<i##End; ++i)
#define per(i,l,r) for(int i(r),i##End(l); i>=i##End; --i)
#define per_(i,l,r) for(int i(r),i##End(l); i>i##End; --i)

#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define mkt make_tuple
#define debug(format,args...) fprintf(stderr,format,##args)

using namespace std;

using ll = long long;
using ull = long long unsigned;
using uint = unsigned int;
using db = double;
using ldb = long double;
using i128 = __int128;
using ui128 = unsigned __int128;

char address_head;
template<typename T> constexpr T inf = 0;
template<> constexpr int inf<int> = 1e9;
template<> constexpr ll inf<ll> = 1ll << 60;
template<> constexpr i128 inf<i128> = i128(1) << 120;

constexpr db eps = 1e-12;

#define vec vector
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
db randpr(db l=0,db r=1) { return uniform_real_distribution<db>(l,r)(rnd); }

void Yes(bool f=true) { printf(f?"Yes\n":"No\n"); }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { printf(f?"yes\n":"no\n"); }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { printf(f?"YES\n":"NO\n"); }
void NO(bool f=true) { YES(!f); }

template<typename Tp1,typename Tp2> bool umx(Tp1 &x,Tp2 y) { return y>x?x=y,true:false; }
template<typename Tp1,typename Tp2> bool umn(Tp1 &x,Tp2 y) { return y<x?x=y,true:false; }

ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=(i128)a*a%p) if(n&1) x=(i128)x*a%p;
	return x;
}

const vec<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

template<typename ...Args> string formatStr(const char* __format,Args ...args) {
	static char buf[1<<16];
	sprintf(buf,__format,args...);
	return buf;
}

template<int P> struct ModInt {
  public:
	using mint = ModInt<P>;
	using mintp = mint&;

	operator int() const { return x; }

	mint operator+(int t) const { return x+t>=P?x+t-P:x+t; }
	mint operator-(int t) const { return x<t?x-t+P:x-t; }
	mintp operator+=(int t) { return ((x+=t)>=P)&&(x-=P),(*this); }
	mintp operator-=(int t) { return ((x-=t)<0)&&(x+=P),(*this); }

	mint operator++(int) { return (++x>=P)?x=0,P-1:x-1;}
	mint operator--(int) { return (--x<0)?x=P-1,0:x+1;}
	mintp operator++() { return (++x>=P)?x=0,(*this):(*this);}
	mintp operator--() { return (--x<0)?x=P-1,(*this):(*this);}

	mint operator*(int t) const { return (ll)x*t%P; }
	mintp operator*=(int t) { return x=(ll)x*t%P,(*this); }

	ModInt():x(0) {}
	template<typename Tp> ModInt(Tp y) {
		if(y<0) x=y%P+P;
		else if(y<P) x=y;
		else x=y%P;
	}
  private:
	int x;
};

constexpr int
	N = 2e5,
	M = N << 2,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

using mint = ModInt<P>::mint;

// #define MULTITEST
// #define FILE_IO_NAME ""

ll invP(ll x) { return qpow(x,P-2,P); }

int n,q,p[N + 2],a[N + 2];
vec<int> e[N + 2];
int dfc,dfn[N + 2],sz[N + 2],wson[N + 2],top[N + 2],low[N + 2],rnk[N + 2];
mint f[N + 2],g[N + 2];

void dfs(int u) {
	sz[u]=1;
	if(e[u].size()==0) f[u]=a[u];
	else {
		f[u]=1;
		for(auto v : e[u]) {
			dfs(v);
			sz[u]+=sz[v];
			f[u]*=f[v];
			if(sz[v]>sz[wson[u]]) wson[u]=v;
		}
		f[u]+=a[u];
	}
}

void dfs2(int u,int tp) {
	dfn[u]=++dfc;
	rnk[dfc]=u;
	top[u]=tp;
	if(wson[u]) dfs2(wson[u],tp);
	else {
		low[u]=low[tp]=dfn[u];
		return ;
	}
	low[u]=low[tp];
	g[u]=1;
	for(auto v : e[u])
		if(v!=wson[u]) {
			dfs2(v,v);
			g[u]*=f[v];
		}
}

struct matrix {
	int n,m;
	mint a[5][5];
	mint* operator[](int x) { return a[x]; }
	const mint* operator[](int x) const { return a[x]; }
};
matrix operator*(const matrix& a,const matrix& b) {
	matrix c;
	c.n=a.n;
	c.m=b.m;
	assert(a.m==b.n);
	for(int i=1; i<=c.n; ++i)
		for(int j=1; j<=c.m; ++j) {
			c[i][j]=0;
			for(int k=1; k<=a.m; ++k)
				c[i][j]+=a[i][k]*b[k][j];
		}
	return c;
}
matrix mat2x2(ll a,ll b,ll c,ll d) {
	matrix x;
	x.n=x.m=2;
	x[1][1]=a;
	x[1][2]=b;
	x[2][1]=c;
	x[2][2]=d;
	return x;
}
const matrix E = mat2x2(1,0,0,1);
namespace segtree {
	matrix tr[M];
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			tr[u]=mat2x2(g[rnk[l]],0,a[rnk[l]],1);
			return ;
		}
		build(li);
		build(ri);
		tr[u]=tr[rs]*tr[ls];
	}
	matrix query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return E;
		if(x<=l&&r<=y) return tr[u];
		return query(ri,x,y)*query(li,x,y);
	}
	template<typename F> void modify(int u,int l,int r,int x,F f) {
		if(r<dfn[x]||dfn[x]<l) return ;
		if(l==r) {
			f(tr[u]);
			return ;
		}
		if(dfn[x]<=mid) modify(li,x,f);
		else modify(ri,x,f);
		tr[u]=tr[rs]*tr[ls];
	}
}

mint get_ans(int x) {
	matrix s;
	s.n=1;
	s.m=2;
	s[1][1]=a[rnk[low[x]]];
	s[1][2]=1;
	return (s*segtree::query(1,1,n,dfn[top[x]],low[x]-1))[1][1];
}

mint update(int x) {
	x=top[x];
	using namespace segtree;
	mint cur=get_ans(x);
	if(x==1) return cur;
	modify(1,1,n,p[x],[=](matrix &t) {
		t[1][1]*=cur;
		t[1][1]*=qpow(f[x],P-2,P);
	});
	f[x]=cur;
	return update(p[x]);
}

void _main() {
	scanf("%d%d",&n,&q);
	rep(i,2,n) scanf("%d",&p[i]),e[p[i]].ebk(i);
	rep(i,1,n) scanf("%d",&a[i]);
	dfs(1);
	dfs2(1,1);
	using namespace segtree;
	build(1,1,n);
	rep(i,1,q) {
		int x,y;
		scanf("%d%d",&x,&y);
		modify(1,1,n,x,[=](matrix &t){
			t[2][1]=y;
		});
		a[x]=y;
		printf("%d\n",update(x));
		debug("%d\n",get_ans(1));
	}
}

void _init() {

}

char address_tail;

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	_init();
	int T=1;
	debug("Memory:%.8lfMib\n",double(&address_tail-&address_head)/pow(2,20));
#if defined(MULTITEST)
	scanf("%d",&T);
#endif
	while(T--) _main();
	return 0;
}