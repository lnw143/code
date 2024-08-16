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
#define debug(format,args...) void()
#define error(message,args...) (debug(message,##args),exit(1))

namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf;
	inline char gc() {
		static char buf[BUF],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2)?-1:*p1++;
	}
	inline void pc(char c) {
		*p++=c;
		if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	}
	inline void flush() {
		fwrite(pbuf,1,p-pbuf,stdout);
		p=pbuf;
	}
	template<typename T> inline void read(T &x) {
		x=0;
		char c=gc();
		T f=1;
		for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c^48);
		x*=f;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> inline void write(T x) {
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	inline void write(char c) { pc(c); }
	template<typename T,typename ...Args> void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using IO::read;
using IO::write;
using IO::flush;

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
void Yes(bool f=true) { if(f) write('Y','e','s','\n'); else write('N','o','\n'); }

const vector<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

#define MULTITEST
// #define FILE_IO_NAME ""

void _main();
void _init();
char* last_address();

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
	freopen(FILE_IO_NAME".in","r",stdin);
	// freopen(FILE_IO_NAME".out","w",stdout);
#endif
	_init();
	int T=1;
	debug("Memory:%.8lfMib\n",double(last_address()-&address_head)/pow(2,20));
#if defined(MULTITEST)
	read(T);
#endif
	while(T--) _main();
	return 0;
}

const int N = 2e5;

int n,m,p[N + 2],q[N + 2];

vector<int> e[N + 2];

namespace treecut {
	int sz[N + 2],wson[N + 2],dep[N + 2],fa[N + 2],dfc,dfn[N + 2],low[N + 2],top[N + 2],pos[N + 2];
	void dfs(int u,int p) {
		sz[u]=1;
		fa[u]=p,dep[u]=dep[p]+1;
		wson[u]=dfn[u]=low[u]=top[u]=0;
		for(auto v : e[u])
			if(v!=p) {
				dfs(v,u);
				sz[u]+=sz[v];
				if(sz[v]>sz[wson[u]]) wson[u]=v;
			}
	}
	int dfs2(int u,int _top) {
		top[u]=_top;
		dfn[u]=++dfc;
		pos[dfn[u]]=u;
		if(!wson[u]) return low[u]=dfn[u];
		low[u]=dfs2(wson[u],_top);
		for(auto v : e[u])
			if(v!=fa[u]&&v!=wson[u])
				dfs2(v,v);
		return low[u];
	}
	int lca(int x,int y) {
		while(top[x]!=top[y]) {
			if(dep[top[x]]>dep[top[y]]) swap(x,y);
			y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
	void clear() {
		dfc=0;
		dep[1]=sz[0]=0;
	}
}

struct node1 {
	int x,y;
	node1():x(-1e9),y(1e9) {}
	node1(int x,int y):x(x),y(y) {}
};
node1 operator+(const node1 &x,const node1& y) {
	return {max(x.x,y.x),min(x.y,y.y)};
}
struct node2 {
	int x,y,z;
	node2():x(0),y(0),z(0) {}
	node2(int x,int y,int z):x(x),y(y),z(z) {}
};
node2 operator+(const node2 &x,const node2& y) {
	using namespace treecut;
	vector<pair<int,int>> v{{-dep[x.x],x.x},{-dep[x.y],x.y},{-dep[y.x],y.x},{-dep[y.y],y.y}};
	sort(all(v));
	while(v.size()>1&&dfn[v[1].scd]<=dfn[v[0].scd]&&dfn[v[0].scd]<=dfn[v[1].scd]+sz[v[1].scd]-1) v.erase(v.begin()+1);
	return {v[0].scd,v.size()>1?v[1].scd:0,x.z>0&&(!y.z||dep[x.z]<dep[y.z])?x.z:y.z};
}

template<class node,node val(int x)> struct segtree {
	#define mid (l+r>>1)
	#define ls (u<<1)
	#define rs (ls|1)
	#define li ls,l,mid
	#define ri rs,mid+1,r
	node s[N << 2];
	void build(int u,int l,int r) {
		if(l==r) {
			s[u]=val(l);
			return ;
		}
		build(li);
		build(ri);
		s[u]=s[ls]+s[rs];
	}
	void modify(int u,int l,int r,int x,const node& y) {
		if(l==r) {
			s[u]=y;
			return ;
		}
		if(x<=mid) modify(li,x,y);
		else modify(ri,x,y);
		s[u]=s[ls]+s[rs];
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return node();
		if(x<=l&&r<=y) return s[u];
		return query(li,x,y)+query(ri,x,y);
	}
	#undef mid
	#undef ls
	#undef rs
	#undef li
	#undef ri
};

node1 val1(int x) {
	return {p[treecut::pos[x]],p[treecut::pos[x]]};
}

node2 val2(int x) {
	return {q[x],0,q[x]};
}

segtree<node1,val1> f;
segtree<node2,val2> g;

node1 pathq(int u,int v) {
	using namespace treecut;
	node1 res;
	while(top[u]!=top[v]) {
		if(dep[top[u]]>dep[top[v]]) swap(u,v);
		res=res+f.query(1,1,n,dfn[top[v]],dfn[v]);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res=res+f.query(1,1,n,dfn[u],dfn[v]);
	return res;
}

bool check(int u,int v,int l,int r) {
	using namespace treecut;
	int anc=lca(u,v);
	if(dep[u]+dep[v]-2*dep[anc]!=r-l) return false;
	node1 res=pathq(u,v);
	return l<=res.y&&res.x<=r;
}

void _main() {
	read(n);
	fo(i,1,n) read(p[i]),q[p[i]]=i;
	fo(i,1,n-1) {
		int x,y;
		read(x,y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	treecut::dfs(1,1);
	treecut::dfs2(1,1);
	f.build(1,1,n);
	g.build(1,1,n);
	read(m);
	fo(i,1,m) {
		int op,x,y;
		read(op,x,y);
		if(op==1) {
			if(x==y) continue;
			int u=p[x],v=p[y];
			using treecut::dfn;
			f.modify(1,1,n,dfn[x],{v,v});
			f.modify(1,1,n,dfn[y],{u,u});
			g.modify(1,1,n,u,{y,0,y});
			g.modify(1,1,n,v,{x,0,x});
			swap(p[x],p[y]);
		} else {
			auto [u,v,w]=g.query(1,1,n,x,y);
			Yes(u&&v&&check(u,v,x,y)||check(u,w,x,y));
		}
	}
	fo(i,1,n) e[i].clear();
	treecut::clear();
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}