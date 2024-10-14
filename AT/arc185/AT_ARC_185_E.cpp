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

#define fo(i,l,r) for(ll i(l),i##END(r); i<=i##END; ++i)
#define fd(i,l,r) for(ll i(l),i##END(r); i>=i##END; --i)
#define fu(i,l,r) for(ll i(l),i##END(r); i<i##END; ++i)
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

const int N = 5e5, M = 1e5, P = 998244353;

int n,a[N + 2];

ll d[M + 2],ans[N + 2];

namespace linear_sieve {
	ll phi[M + 2];
	vector<int> prm;
	bool bz[M + 2];
	void init() {
		phi[1]=1;
		for(int i=2; i<=M; ++i) {
			if(!bz[i]) {
				prm.push_back(i);
				phi[i]=i-1;
			}
			for(auto j : prm) {
				if(i*j>M) break;
				bz[i*j]=true;
				if(i%j==0) {
					phi[i*j]=phi[i]*j;
					break;
				}
				phi[i*j]=phi[i]*(j-1);
			}
		}
	}
}

using linear_sieve::phi;

void _main() {
	linear_sieve::init();
	scanf("%d",&n);
	fo(i,1,n) scanf("%d",&a[i]);
	ll p2=1;
	fo(i,1,n) {
		ans[i]=ans[i-1]*2%P;
		for(int j=1; j*j<=a[i]; ++j)
			if(a[i]%j==0) {
				(ans[i]+=phi[j]*d[j])%=P;
				if(j*j!=a[i]) (ans[i]+=phi[a[i]/j]*d[a[i]/j])%=P;
			}
		for(int j=1; j*j<=a[i]; ++j)
			if(a[i]%j==0) {
				(d[j]+=p2)%=P;
				if(j*j!=a[i]) (d[a[i]/j]+=p2)%=P;
			}
		(p2*=2)%=P;
	}
	fo(i,1,n) printf("%lld\n",ans[i]);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}