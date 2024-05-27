// #pragma GCC optimize("O3,unroll-loops")

// #pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
// #pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

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

char address_head;
template<typename T> constexpr T inf = 0;
template<> constexpr int inf<int> = 1e9;
template<> constexpr ll inf<ll> = 1ll << 60;

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
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

#if defined(__SIZEOF_INT128__)

using i128 = __int128;
using ui128 = unsigned __int128;
template<> constexpr i128 inf<i128> = i128(1) << 120;
ll qPow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=(i128)a*a%p) if(n&1) x=(i128)x*a%p;
	return x;
}

#endif

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
	N = 5e3,
	M = 0,
	K = 0,
	Q = 1e7,
	S = 0,
	P = 0x7fffffff
;

using mint = ModInt<P>::mint;

// #define MULTITEST
// #define FILE_IO_NAME ""

int n,q;
ll g,ra,rb,ans;

struct line { int k,b; } a[N + 2];
struct point { ll x,y; } b[Q + 2];

struct frac {
	ll x,y;
	frac(ll a,ll b):x(a),y(b) {}
};

bool operator<(const frac& a,const frac& b) { return a.x*b.y<b.x*a.y; }
bool operator==(const frac& a,const frac& b) { return a.x==b.x&&a.y==b.y; }
bool operator!=(const frac& a,const frac& b) { return a.x!=b.x||a.y!=b.y; }

bool operator<(const line& x,const line& y) { return x.k!=y.k?x.k>y.k:x.b<y.b; }
bool operator<(const point& a,const point& b) { return a.x!=b.x?a.x<b.x:a.y<b.y; }
frac operator*(const line& x,const line& y) { return frac(y.b-x.b,x.k-y.k); }

inline ll gen() { return g=g*48271%P; }

void _main() {
	scanf("%d",&n);
	rep(i,1,n) {
		scanf("%d%d",&a[i].k,&a[i].b);
		a[i].k=-a[i].k;
	}
	scanf("%d%lld%lld%lld",&q,&g,&ra,&rb);
	rep(i,1,q) {
		const int G1 = gen();
		const int G2 = gen();
		const int G3 = gen();
		b[i]=point{G1%(2*ra+1)-ra,((ll)G2*P+G3)%(2*rb+1)-rb};
	}
	sort(a+1,a+n+1);
	sort(b+1,b+q+1);
	heap<pair<frac,int>> hp;
	const auto add=[&](int x) {
		if(1<=x&&x<n&&a[x].k>a[x+1].k)
			hp.emplace(a[x]*a[x+1],x);
	};
	rep(i,1,n-1)
		add(i);
	rep(i,1,q) {
		const auto [x,y]=b[i];
		while(!hp.empty()&&hp.top().first<frac(x,1)) {
			auto [p,u]=hp.top();
			hp.pop();
			if(a[u]*a[u+1]!=p) continue;
			swap(a[u],a[u+1]);
			add(u-1);
			add(u+1);
		}
		int l=1,r=n,mid;
		while(l<=r) {
			mid=(l+r)>>1;
			if(a[mid].k*x+a[mid].b>=y) r=mid-1;
			else l=mid+1;
		}
		ans+=n-r;
	}
	printf("%lld",ans);
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