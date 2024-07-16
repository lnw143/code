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
#define fir first
#define sec second
#define all(v) v.begin(),v.end()
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))

using namespace std;
using ll = long long;
char address_head;
#define vec vector
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
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
const vec<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

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

int n[2],k,a[N + 2],b[N + 2],t[N + 2];

ll s[N + 2],f[2][N + 2];

void _main() {
	scanf("%d%d",&n[0],&n[1]);
	k=n[0]+n[1]+1;
	fo(i,1,k) scanf("%d",&a[i]);
	fo(i,1,k) scanf("%d",&b[i]);
	int c[2]={0,0},p[2]={k+1,k+1},q[2]={k+1,k+1};
	fo(i,1,k) {
		t[i]=a[i]<b[i];
		++c[t[i]];
		if(c[t[i]]==n[t[i]])
			p[t[i]]=i;
		else if(c[t[i]]==n[t[i]]+1)
			q[t[i]]=i;
		s[i]=s[i-1]+max(a[i],b[i]);
	}
	if(!n[0]) p[0]=q[0]=0;
	if(!n[1]) p[1]=q[1]=0;
	f[0][k+1]=f[1][k+1]=0;
	fd(i,k,1) f[0][i]=f[0][i+1]+a[i],f[1][i]=f[1][i+1]+b[i];
	fo(i,1,k) {
		int r[2]={p[0],p[1]};
		ll ans=0;
		if(i<=r[t[i]]) r[t[i]]=q[t[i]],ans=-max(a[i],b[i]);
		if(r[0]<r[1]) {
			if(!ans) ans=-b[i];
			ans+=s[r[0]]+f[1][r[0]+1];
		} else {
			if(!ans) ans=-a[i];
			ans+=s[r[1]]+f[0][r[1]+1];
		}
		printf("%lld ",ans);
	}
	putchar('\n');
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}