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
#define FILE_IO_NAME ""

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

const int N = 26, M = N * N;

int n;

vector<int> e[N + 2],g[N + 2];

bool bz[N + 2];

int dfc,dfn[N + 2],low[N + 2];
int scc[N + 2],scnt;
int stk[N + 2],tp;
bool in_stk[N + 2];

set<int> to[N + 2];

int deg[N + 2],dep[N + 2],sum;

void dfs(int u) {
	in_stk[u]=true;
	dfn[u]=low[u]=++dfc;
	stk[++tp]=u;
	for(auto v : e[u])
		if(!dfn[v]) {
			dfs(v);
			low[u]=min(low[u],low[v]);
		} else if(in_stk[v])
			low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]) {
		++scnt;
		while(stk[tp]!=u) {
			in_stk[stk[tp]]=false;
			scc[stk[tp]]=scnt;
			--tp;
		}
		--tp;
		in_stk[u]=false;
		scc[u]=scnt;
	}
}

int calc(int u) {
	int res=0;
	for(auto v : to[u])
		res+=!bz[v];
	return res;
}

int choose(const vector<int> &vex) {
	int sum=0;
	vector<int> val;
	for(auto i : vex) {
		int tot=calc(i);
		sum+=tot;
		val.push_back(tot);
	}
	int cho=randint(1,sum);
	sum=0;
	for(int i=0; i<val.size(); ++i)
		if(cho<=(sum+=val[i]))
			return vex[i];
	throw "no";
	return -1;
}

int walk(int u) {
	if(u==-1) return 0;
	int f=0;
	if(!bz[u]) {
		bz[u]=true;
		f=1;
		++sum;
		if(sum==scnt) return f;
	}
	if(g[u].empty()) return f;
	return walk(choose(g[u]))|f;
}

void get(int u) {
	if(to[u].size()) return ;
	to[u].insert(u);
	for(auto v : g[u]) {
		get(v);
		for(auto i : to[v])
			to[u].insert(i);
	}
}

void _main() {
	scanf("%d",&n);
	fo(i,1,n) {
		char s,t;
		scanf(" %c%c",&s,&t);
		int u=s-'A'+1,v=t-'A'+1;
		e[u].push_back(v);
		bz[u]=bz[v]=true;
	}
	fo(i,1,N)
		if(!dfn[i]&&bz[i])
			dfs(i);
	fo(i,1,N)
		for(auto j : e[i])
			if(scc[i]!=scc[j])
				g[scc[i]].push_back(scc[j]);
	fo(i,1,scnt) {
		sort(all(g[i]));
		g[i].erase(unique(all(g[i])),g[i].end());
		for(auto j : g[i])
			++deg[j];
	}
	vector<int> start,p;
	fo(i,1,scnt) {
		if(deg[i]==0)
			start.push_back(i);
		get(i);
	}
	int ans=scnt;
	while(runtime()<1.9) {
		sum=0;
		int cur=0;
		memset(bz,0,sizeof(bz));
		while(sum<scnt) cur+=walk(choose(start));
		ans=min(ans,cur);
	}
	printf("%d",ans);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}