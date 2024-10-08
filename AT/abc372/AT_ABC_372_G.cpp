// #pragma GCC optimize("O3,unroll-loops")

#pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
#pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

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

#define MULTITEST
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

const int N = 2e5;

const long double eps = 1e-12;

int n,m;

ll ans;

struct line {
	ll a,b,c;
	long double k,b_;
	db operator()(ll x) const {
		return (c-a*x)*1.0l/b;
	}
	line()=default;
	line(ll a,ll b,ll c):a(a),b(b),c(c),k(-a*1.0l/b),b_(c*1.0l/b) {}
} a[N + 2],b[N + 2];

long double operator*(const line& x,const line& y) {
	if(abs(x.k-y.k)<eps) return -1e20l;
	return (y.b-x.b)/(x.k-y.k);
}

bool operator<(const line& x,const line& y) {
	if(abs(x.k-y.k)<eps) return x.c*y.b>y.c*x.b;
	return x.a*y.b<y.a*x.b;
}

void solve(db L,db R,const line& x) {
	auto [k,b]=x;
	ll l=ceil(L),r=floor(R);
	for(ll i=l; i<=r; ) {
		ll v=ceil(x(i)),j=min(r+1,(ll)ceil((v-b-1)/k));
		ans+=v*(j-i);
		i=j;
	}
	ans-=r-l+1;
}

void _main() {
	scanf("%d",&n);
	fo(i,1,n) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		a[i]=line(u,v,w);
	}
	sort(a+1,a+n+1);
	m=0;
	fo(i,1,n) {
		while(m>=2&&b[m-1]*b[m]>b[m]*a[i]) --m;
		b[++m]=a[i];
	}
	int k=1;
	while(k<m&&b[k]*b[k+1]<=0) ++k;
	fo(i,k,m)
		b[i-k+1]=b[i];
	m-=k-1;
	while(m>=2&&b[m](b[m]*b[m-1])<=0) --m;
	ans=0;
	if(m==1)
		solve(1,-b[1].b/b[1].k-eps,b[1]);
	else {
		solve(1,b[1]*b[2]-eps,b[1]);
		fo(i,2,m-1) solve(b[i]*b[i-1],b[i]*b[i+1]-eps,b[i]);
		solve(b[m-1]*b[m],-b[m].b/b[m].k-eps,b[m]);
	}
	printf("%lld\n",ans);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}