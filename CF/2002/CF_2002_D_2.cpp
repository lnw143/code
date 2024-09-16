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

const int N = 3e5;

int n,q,fa[N + 2],p[N + 2],dfn[N + 2],low[N + 2],dfc;
vector<int> e[N + 2];

namespace segtree {
	const int S = N << 2;
	struct node {
		int s,t;
	} s[S + 2];
	node operator+(const node& x,const node& y) {
		if((x.s|y.s)==-1) return {-1,-1};
		if(fa[y.s]==x.t||(e[x.t].empty()&&y.s!=1&&dfn[fa[y.s]]<=dfn[x.t]&&dfn[x.t]<=low[fa[y.s]])) return {x.s,y.t};
		return {-1,-1};
	}
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			s[u]={p[l],p[l]};
			return ;
		}
		build(li);
		build(ri);
		s[u]=s[ls]+s[rs];
	}
	void modf(int u,int l,int r,int x,int k) {
		if(l==r) {
			s[u]={k,k};
			return ;
		}
		if(x<=mid) modf(li,x,k);
		else modf(ri,x,k);
		s[u]=s[ls]+s[rs];
	}
}

void dfs(int u) {
	dfn[u]=++dfc;
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
}

void _main() {
	scanf("%d%d",&n,&q);
	fo(i,2,n) scanf("%d",&fa[i]),e[fa[i]].push_back(i);
	fo(i,1,n) scanf("%d",&p[i]);
	dfc=0;
	dfs(1);
	segtree::build(1,1,n);
	fo(i,1,q) {
		int x,y;
		scanf("%d%d",&x,&y);
		segtree::modf(1,1,n,x,p[y]);
		segtree::modf(1,1,n,y,p[x]);
		swap(p[x],p[y]);
		YES(segtree::s[1].s==1);
	}
	fo(i,1,n) e[i].clear();
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}