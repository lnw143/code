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

int n,m,p,s[N + 2],fa[N + 2];
ll cur[N + 2];
bool bz[N + 2],t[N + 2];

struct edge {
	int u,v,w;
} eg[N + 2];

vector<pair<int,int>> e[N + 2];

int find(int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}

void merge(int u,int v) {
	fa[find(u)]=find(v);
}

ll calc(int u,int x) {
	if(cur[u]<x) return 0;
	bz[u]=true;
	ll res=t[u]?cur[u]-x:0;
	for(auto [v,w] : e[u])
		if(!bz[v])
			res+=calc(v,max(x,w));
	bz[u]=false;
	return res;
}

void dfs(int u,int x) {
	if(cur[u]<x) return ;
	cur[u]=x;
	bz[u]=true;
	for(auto [v,w] : e[u])
		if(!bz[v])
			dfs(v,max(x,w));
	bz[u]=false;
}

void _main() {
	scanf("%d%d%d",&n,&m,&p);
	fo(i,1,p) scanf("%d",&s[i]),t[s[i]]=true;
	fo(i,1,m) scanf("%d%d%d",&eg[i].u,&eg[i].v,&eg[i].w);
	sort(eg+1,eg+m+1,[](auto x,auto y) { return x.w<y.w; });
	fo(i,1,n) fa[i]=i;
	fo(i,1,m) {
		auto [u,v,w]=eg[i];
		if(find(u)!=find(v)) {
			merge(u,v);
			e[u].emplace_back(v,w);
			e[v].emplace_back(u,w);
		}
	}
	fo(i,1,n) cur[i]=1e9;
	fo(i,1,p) {
		ll maxn=-1;
		int maxv=-1;
		fo(i,1,n) {
			ll v=calc(i,0);
			if(v>maxn) maxn=v,maxv=i;
		}
		dfs(maxv,0);
		ll ans=0;
		fo(i,1,p) ans+=cur[s[i]];
		printf("%lld ",ans);
	}
	fo(i,p+1,n) printf("0 ");
	putchar('\n');
	fo(i,1,n) e[i].clear(),t[i]=false;
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}