// #pragma GCC optimize("O3,unroll-loops")

// #pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
// #pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

#include <cstdio>
#include <cmath>
#include <cstdint>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
#include <bitset>
#include <random>
#include <chrono>
#include <cassert>
#include <cstdlib>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define fo(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define fd(i,l,r) for(int i(l),i##END(r); i>=i##END; --i)
#define fu(i,l,r) for(int i(l),i##END(r); i<i##END; ++i)
#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define mkt make_tuple
#define fst first
#define scd second
#define all(v) v.begin(),v.end()
#ifdef ONLINE_JUDGE
#define debug(format,args...) void()
#define error(message,args...) void()
#else
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))
#endif

using namespace std;
using ll = long long;
char address_head;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;
#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = double> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
double randpr(double l=0,double r=1) { return uniform_real_distribution<double>(l,r)(rnd); }
void Yes(bool f=true) { printf(f?"Yes\n":"No\n"); }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { printf(f?"yes\n":"no\n"); }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { printf(f?"YES\n":"NO\n"); }
void NO(bool f=true) { YES(!f); }
const vector<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

// #define MULTITEST
// #define FILE_IO_NAME ""

void _main();
void _init();
char* last_address();

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	_init();
	int T=1;
	debug("Memory:%.8lfMib\n",double(last_address()-&address_head)/pow(2,20));
#if defined(MULTITEST)
	scanf("%d",&T);
#endif
	while(T--) _main();
	return 0;
}

const int M = 1e5, P = 998244353;

ll n;
int k,m;

ll qpow(ll a,ll k) {
	ll x=1;
	for(; k; k>>=1,a=a*a%P) if(k&1) x=x*a%P;
	return x;
}

namespace comb {
	ll fac[M * 2 + 2],ifac[M * 2 + 2];
	void init() {
		fac[0]=1;
		fo(i,1,M*2) fac[i]=fac[i-1]*i%P;
		ifac[M*2]=qpow(fac[M*2],P-2);
		fd(i,M*2-1,0) ifac[i]=ifac[i+1]*(i+1)%P;
	}
	ll C(int n,int m) {
		return fac[n]*ifac[m]%P*ifac[n-m]%P;
	}
}

using comb::C;

namespace linear_sieve {
	vector<int> p;
	bool bz[M * 2 + 2];
	void init() {
		p.push_back(1);
		for(int i=2; ; ++i) {
			if(!bz[i]) {
				p.push_back(i);
				if(i>=m) break;
			}
			for(auto j : p) {
				if(i*j>m) break;
				bz[i*j]=true;
				if(j%i==0) break;
			}
		}
	}
}

using linear_sieve::p;

namespace min_25 {
	ll g[M * 2 + 2],h[M * 2 + 2];
	int pos(ll x) {
		return x<=m?x:m+n/x;
	}
	void init() {
		for(ll i=1; i<=n; i=n/(n/i)+1) {
			ll x=n/i;
			g[pos(x)]=ll(upper_bound(p.begin(),p.end(),x)-p.begin()-1)*k%P;
			h[pos(x)]=(g[pos(x)]-(x>=3?k:0))%P;
		}
	}
	ll S(ll x,int y,ll (*G)(ll),ll (*F)(int,int)) {
		if(x<=p[y]) return 0;
		ll res=G(x)-G(p[y]);
		for(int i=y+1; i<p.size()&&p[i]<=x/p[i]; ++i) {
			int t=1;
			for(ll s=p[i]; s<=n; s*=p[i],++t)
				(res+=F(p[i],t)*(S(x/s,i,G,F)+(t!=1))%P)%=P;
		}
		return res;
	}
}

void _main() {
	scanf("%lld%d",&n,&k);
	while((ll)m*m<n) ++m;
	linear_sieve::init();
	min_25::init();
	ll sumg=min_25::S(n,0,
		[](ll n) { return min_25::g[min_25::pos(n)]; },
		[](int p,int t) { return C(t+k-1,k-1); }
	);
	printf("%lld",sumg);
}

void _init() {
	comb::init();
}

char* last_address() {
	static char address_tail;
	return &address_tail;
}