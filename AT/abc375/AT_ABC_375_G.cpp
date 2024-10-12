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

const int N = 2e5;
const ll inf = 1ll << 60;

int n,m;

ll dis[N + 2],disn[N + 2];

vector<pair<int,int>> e[N + 2];
vector<int> g[N + 2];

map<pair<int,int>,int> mp;
bool ans[N + 2];

void dij(int s,ll* dis) {
	fo(i,1,n) dis[i]=inf;
	dis[s]=0;
	heap<pair<ll,int>> hp;
	hp.emplace(0,s);
	for(int i=1; i<n&&hp.size(); ) {
		auto [d,u]=hp.top();
		hp.pop();
		if(d!=dis[u]) continue;
		++i;
		for(auto [v,w] : e[u])
			if(d+w<dis[v]) {
				dis[v]=d+w;
				hp.emplace(dis[v],v);
			}
	}
}

int low[N + 2],dfn[N + 2],dfc;

void dfs(int u,int p) {
	dfn[u]=low[u]=++dfc;
	for(auto v : g[u])
		if(!dfn[v]) {
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]) ans[mp[mkp(u,v)]]=true;
		} else if(v!=p)
			low[u]=min(low[u],dfn[v]);
}

void _main() {
	scanf("%d%d",&n,&m);
	fo(i,1,m) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		mp[mkp(u,v)]=mp[mkp(v,u)]=i;
		e[u].ebk(v,w);
		e[v].ebk(u,w);
	}
	dij(1,dis);
	dij(n,disn);
	fo(i,1,n)
		for(auto [v,w] : e[i])
			if(dis[i]+w+disn[v]==dis[n]) {
				g[i].pbk(v);
				g[v].pbk(i);
			}
	dfs(1,-1);
	fo(i,1,m) Yes(ans[i]);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}