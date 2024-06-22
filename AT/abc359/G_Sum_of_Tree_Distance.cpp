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
mt19937 rnd(random_device{}());
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

const int N = 2e5, logN = 20;

int n,a[N + 2],anc[logN][N + 2],dep[N + 2];
int dfc,dfn[N + 2];
ll ans;
vector<int> e[N + 2],s[N + 2];

void dfs(int u) {
	dfn[u]=++dfc;
	dep[u]=dep[anc[0][u]]+1;
	fu(i,1,logN) anc[i][u]=anc[i-1][anc[i-1][u]];
	for(auto v : e[u])
		if(v!=anc[0][u]) {
			anc[0][v]=u;
			dfs(v);
		}
}

int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	fd(i,logN-1,0)
		if(dep[anc[i][u]]>=dep[v])
			u=anc[i][u];
	if(u==v) return u;
	fd(i,logN-1,0)
		if(anc[i][u]!=anc[i][v])
			u=anc[i][u],
			v=anc[i][v];
	return anc[0][u];
}

namespace virtree {
	int sz[N + 2];
	vector<int> w[N + 2];
	ll dfs(int u) {
		ll sum=sz[u]*dep[u];
		for(auto v : w[u]) {
			ll res=dfs(v);
			ans+=(sum-(ll)sz[u]*dep[u])*sz[v]+(res-(ll)sz[v]*dep[u])*sz[u];
			sum+=res;
			sz[u]+=sz[v];
		}
		return sum;
	}
	void solve(vector<int> node) {
		if(node.empty()) return ;
		int n=node.size();
		for(auto u : node) sz[u]=1;
		sort(all(node),[](int x,int y) { return dfn[x]<dfn[y]; });
		fo(i,0,n-2) node.push_back(lca(node[i],node[i+1]));
		node.push_back(1);
		sort(all(node),[](int x,int y) { return dfn[x]<dfn[y]; });
		node.erase(unique(all(node)),node.end());
		n=node.size();
		fo(i,1,n-1) w[lca(node[i-1],node[i])].push_back(node[i]);
		dfs(1);
		for(auto i : node) w[i].clear(),sz[i]=0;
	}
}

void _main() {
	scanf("%d",&n);
	fo(i,1,n-1) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	fo(i,1,n) {
		scanf("%d",&a[i]);
		s[a[i]].pbk(i);
	}
	anc[0][1]=1;
	dfs(1);
	fo(i,1,n)
		virtree::solve(s[i]);
	printf("%lld\n",ans);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}