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
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))

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

const int N = 1e5, M = 2e5, K = 1e5;

int n,m,k,x[M + 2],y[M + 2],ans[K + 2];

namespace pdsu {
	vector<pair<int,int>> s,t;
	int fa[N * 2 + 2],sz[N * 2 + 2];
	int find(int u) {
		return fa[u]==u?u:find(fa[u]);
	}
	void init() {
		fo(i,1,n*2) fa[i]=i,sz[i]=1;
	}
	void merge(int u,int v) {
		u=find(u),v=find(v);
		if(u==v) return ;
		if(sz[u]<sz[v]) swap(u,v);
		s.ebk(v,fa[v]);
		fa[v]=u;
		t.ebk(u,sz[u]);
		sz[u]+=sz[v];
	}
	void undo() {
		fa[s.back().fst]=s.back().scd;
		s.pop_back();
		sz[t.back().fst]=t.back().scd;
		t.pop_back();
	}
	bool check(int u,int v) {
		return find(u)==find(v);
	}
}

namespace segtree {
	vector<int> s[K << 2];
#define mid (l+r>>1)
	void modify(int u,int l,int r,int x,int y,int f) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			s[u].push_back(f);
			return ;
		}
		modify(u<<1,l,mid,x,y,f);
		modify(u<<1|1,mid+1,r,x,y,f);
	}
	void solve(int u,int l,int r,bool cur) {
		const int lvl=pdsu::s.size();
		if(!cur) for(auto i : s[u]) {
			if(pdsu::check(x[i],y[i])) {
				cur|=1;
				break;
			} else {
				pdsu::merge(x[i],y[i]+n);
				pdsu::merge(x[i]+n,y[i]);
			}
		}
		if(l==r)
			ans[l]=cur;
		else {
			solve(u<<1,l,mid,cur);
			solve(u<<1|1,mid+1,r,cur);
		}
		while(pdsu::s.size()>lvl) pdsu::undo();
	}
}

void _main() {
	scanf("%d%d%d",&n,&m,&k);
	pdsu::init();
	fo(i,1,m) {
		int l,r;
		scanf("%d%d%d%d",&x[i],&y[i],&l,&r);
		segtree::modify(1,1,k,l+1,r,i);
	}
	segtree::solve(1,1,k,0);
	fo(i,1,k)
		printf(ans[i]?"No\n":"Yes\n");
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}