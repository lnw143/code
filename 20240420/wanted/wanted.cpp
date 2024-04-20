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
#define endl '\n'

using namespace std;

using ll = long long;
using ull = long long unsigned;
using uint = unsigned int;
using db = double;
using ldb = long double;
using i128 = __int128;
using ui128 = unsigned __int128;

template<typename T> constexpr T inf = 0;
template<> constexpr int inf<int> = 1e9;
template<> constexpr ll inf<ll> = 1e18;
template<> constexpr db inf<db> = 1e18;
template<> constexpr ldb inf<ldb> = 1e18;
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

void Yes(bool f=true) { cout<<(f?"Yes":"No")<<endl; }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { cout<<(f?"yes":"no")<<endl; }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { cout<<(f?"YES":"NO")<<endl; }
void NO(bool f=true) { YES(!f); }

template<typename Tp1,typename Tp2> bool umx(Tp1 &x,Tp2 y) { return y>x?x=y,true:false; }
template<typename Tp1,typename Tp2> bool umn(Tp1 &x,Tp2 y) { return y<x?x=y,true:false; }

ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=(i128)a*a%p) if(n&1) x=(i128)x*a%p;
	return x;
}

template<int P> struct ModInt {
  public:
	using mint = ModInt<P>;
	using mintp = mint&;

	operator const int&() { return x; }

	mint operator+(const int& t) const { return x+t>=P?x+t-P:x+t; }
	mint operator-(const int& t) const { return x<t?x-t+P:x-t; }
	mintp operator+=(const int& t) { return ((x+=t)>=P)&&(x-=P),(*this); }
	mintp operator-=(const int& t) { return ((x-=t)<0)&&(x+=P),(*this); }

	mint operator++(int) { return (++x>=P)?x=0,P-1:x-1;}
	mint operator--(int) { return (--x<0)?x=P-1,0:x+1;}
	mintp operator++() { return (++x>=P)?x=0,(*this):(*this);}
	mintp operator--() { return (--x<0)?x=P-1,(*this):(*this);}

	mint operator*(const int& t) const { return (ll)x*t%P; }
	mintp operator*=(const int& t) { return x=(ll)x*t%P,(*this); }

	int v() { return x; }

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
	N = 1e5,
	logN = 19,
	M = N << 2,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

using mint = ModInt<P>::mint;

// #define MULTITEST
#define FILE_IO_NAME "wanted"

int n,q;
struct edge { int v,w; edge(int v,int w):v(v),w(w) {} };
vec<edge> e[N + 2];
ll dep[N + 2];

int dfc,dfn[N + 2],Log2[N * 2 + 2];
ll st[logN][N * 2 + 2];

void dfs(int u,int p) {
	st[0][dfn[u]=++dfc]=dep[u];
	for(auto [v,w] : e[u])
		if(v!=p) {
			dep[v]=dep[u]+w;
			dfs(v,u);
			st[0][++dfc]=dep[u];
		}
}

ll lcaDep(int x,int y) {
	x=dfn[x],y=dfn[y];
	if(x>y) swap(x,y);
	int k=Log2[y-x+1];
	return min(st[k][x],st[k][y-(1<<k)+1]);
}

ll dist(int x,int y) {
	if(!x||!y) return 0;
	return dep[x]+dep[y]-2*lcaDep(x,y);
}

namespace segtree {
	struct sol {
		ll val;
		int u,v;
		bool operator<(const sol& x) const {
			if(val!=x.val) return val<x.val;
			if(u!=x.u) return u<x.u;
			return v<x.v;
		}
		sol(ll a,int b,int c):val(a),u(b),v(c) {}
	};
	struct val {
		int a,b;
		val operator+(const val& x) const {
			const auto& [u,v]=x;
#define f(a,b) sol(dist(a,b),a,b)
			const auto [t,l,r]=max({f(a,u),f(a,v),f(b,u),f(b,v),f(a,b),f(u,v)});
#undef f
			return {l,r};
		}
	};
	val tr[M];
#define mid ((l+r)>>1)
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int x,int l,int r) {
		if(l==r) {
			tr[x]={l,0};
			return ;
		}
		build(li);
		build(ri);
		tr[x]=tr[ls]+tr[rs];
	}
	val query(int x,int l,int r,int u,int v) {
		if(r<u||v<l) return {0,0};
		if(u<=l&&r<=v) return tr[x];
		return query(li,u,v)+query(ri,u,v);
	}
}

void _main() {
	cin>>n>>q;
	rep_(i,1,n) {
		int x,y,z;
		cin>>x>>y>>z;
		e[x].ebk(y,z);
		e[y].ebk(x,z);
	}
	dfs(1,1);
	rep_(j,1,logN)
		rep(i,1,dfc-(1<<j)+1)
			st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	rep(i,2,dfc)
		Log2[i]=Log2[i>>1]+1;
	segtree::build(1,1,n);
	rep(i,1,q) {
		int l1,r1,l2,r2;
		cin>>l1>>r1>>l2>>r2;
		using namespace segtree;
		auto u=query(1,1,n,l1,r1),v=query(1,1,n,l2,r2);
		cout<<max({dist(u.a,v.a),dist(u.a,v.b),dist(u.b,v.a),dist(u.b,v.b)})<<endl;
	}
}

void _init() {

}

int main() {
#if defined(FILE_IO_NAME) && !defined(CPH)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	_init();
	int T=1;
#if defined(MULTITEST)
	cin>>T;
#endif
	while(T--) _main();
	return 0;
}