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

const int N = 1000;

int n,m,q,fa[N * 2 + 2],sz[N * 2 + 2],c[N + 2];

bool bz[N * 2 + 2];

int find(int u) {
	return u==fa[u]?u:fa[u]=find(fa[u]);
}

void merge(int u,int v) {
	u=find(u),v=find(v);
	if(u==v) return ;
	if(sz[u]<sz[v]) swap(u,v);
	fa[v]=u;
	sz[u]+=sz[v];
}

int ask(int x,int y) {
	printf("? %d %d\n",x,y);
	fflush(stdout);
	int res;
	assert(scanf("%d",&res)==1);
	return res;
	// return c[x]!=c[y];
}

heap<pair<int,int>> hp;

pair<int,int> get() {
	if(hp.empty()) return mkp(-1,-1);
	auto x=hp.top();
	hp.pop();
	while(hp.size()&&(fa[x.second]!=x.second||sz[x.second]!=x.first)) x=hp.top(),hp.pop();
	if(fa[x.second]!=x.second||sz[x.second]!=x.first) return mkp(-1,-1);
	return x;
}

void _main() {
	scanf("%d%d%d",&n,&m,&q);
	// { // data
	// 	set<int> st;
	// 	while(st.size()<m) st.emplace(randint(1,n));
	// 	for(auto i : st) c[i]=1;
	// }
	fo(i,1,n*2) fa[i]=i,sz[i]=1;
	fo(i,1,n) hp.emplace(sz[i],i);
	for(int i=0; i<q; ) {
		auto [szu,u]=get();
		auto [szv,v]=get();
		if(u==-1||v==-1) break;
		if(find(u)==find(v)) {
			hp.emplace(u,sz[u]);
			continue;
		}
		u=(u-1)%n+1;
		v=(v-1)%n+1;
		++i;
		if(ask(u,v)) merge(u,v+n),merge(u+n,v);
		else merge(u,v),merge(u+n,v+n);
		hp.emplace(sz[find(u)],find(u));
		// debug("%d %d %d %d\n",u,v,sz[u],i);
	}
	putchar('!');
	fo(i,1,n*2) sz[i]=0;
	fo(i,1,n) ++sz[find(i)];
	fo(i,1,n)
		if(sz[find(i)]<=m)
			printf(" %d",i);
	putchar('\n');
	fflush(stdout);
	// fo(i,1,n) assert(c[i]==(sz[find(i)]<=m));
}

void _init() {
}

char* last_address() {
	static char address_tail;
	return &address_tail;
}