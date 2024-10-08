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

int n,m,p,s[N + 2],fa[N + 2],anc[N + 2];
int pa[N * 2 + 2],son[N * 2 + 2][2],sz[N * 2 + 2];
bool bz[N * 2 + 2];
ll f[N * 2 + 2],w[N * 2 + 2];
int g[N * 2 + 2];

struct edge {
	int u,v,w;
} eg[N + 2];

int find(int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}

void merge(int u,int v) {
	fa[find(u)]=find(v);
}

void dfs(int u) {
	if(!son[u][0]) {
		f[u]=0;
		g[u]=u;
	} else {
		int x=son[u][0],y=son[u][1];
		dfs(x),dfs(y);
		if(f[x]+w[u]*sz[y]<f[y]+w[u]*sz[x]) {
			f[u]=f[x]+w[u]*sz[y];
			g[u]=g[x];
		} else {
			f[u]=f[y]+w[u]*sz[x];
			g[u]=g[y];
		}
		sz[u]=sz[x]+sz[y];
	}
}

void _main() {
	scanf("%d%d%d",&n,&m,&p);
	fo(i,1,p) scanf("%d",&s[i]);
	fo(i,1,m) scanf("%d%d%d",&eg[i].u,&eg[i].v,&eg[i].w);
	sort(eg+1,eg+m+1,[](auto x,auto y) { return x.w<y.w; });
	fo(i,1,n) fa[i]=anc[i]=i;
	int c=n;
	fo(i,1,m) {
		auto [u,v,weight]=eg[i];
		if(find(u)!=find(v)) {
			int x=anc[find(u)],y=anc[find(v)];
			pa[x]=pa[y]=++c;
			son[c][0]=x;
			son[c][1]=y;
			w[c]=weight;
			merge(u,v);
			anc[find(u)]=c;
		}
	}
	fo(i,1,p) sz[s[i]]=1;
	pa[c]=0;
	dfs(c);
	heap<pair<ll,int>> hp;
	ll ans=f[c];
	for(int i=g[c]; pa[i]&&!bz[pa[i]]; i=pa[i]) {
		int v=son[pa[i]][son[pa[i]][0]==i];
		hp.emplace(f[v]-sz[v]*w[pa[i]],v);
		bz[pa[i]]=true;
	}
	printf("%lld ",ans);
	fo(i,2,n) {
		auto [val,u]=hp.top();
		hp.pop();
		ans+=val;
		for(int i=g[u]; pa[i]&&!bz[pa[i]]; i=pa[i]) {
			int v=son[pa[i]][son[pa[i]][0]==i];
			hp.emplace(f[v]-sz[v]*w[pa[i]],v);
			bz[pa[i]]=true;
		}
		printf("%lld ",ans);
	}
	fo(i,1,c) son[i][0]=son[i][1]=bz[i]=sz[i]=0;
	putchar('\n');
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}