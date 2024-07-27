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

const int N = 2e5, Q = 2e5;

int n,q,l[N + 2],r[N + 2],v[N + 2],rt[Q + 2];
ll c[Q + 2],ans;

pair<int,int> t[Q + 2];

namespace segtree {
	int s[N << 2],t[N << 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			t[u]=1;
			return;
		}
		build(li);
		build(ri);
		t[u]=t[ls]+t[rs];
	}
	void modify(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			s[u]=1;
			t[u]=0;
			return ;
		}
		modify(li,x,y);
		modify(ri,x,y);
		t[u]=s[u]?0:t[ls]+t[rs];
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l||s[u]) return 0;
		if(x<=l&&r<=y) return t[u];
		return query(li,x,y)+query(ri,x,y);
	}
#undef ls
#undef rs
#undef li
#undef ri
#undef mid
}

namespace psegtree {
	int tot,ls[N << 6],rs[N << 6];
	ll s[N << 6],t[N << 6];
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		if(l==r) return u;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return u;
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		s[v]=s[u],t[v]=t[u];
		if(x<=l&&r<=y) {
			++t[v];
			s[v]+=r-l+1;
			return v;
		}
		ls[v]=modify(ls[v],l,mid,x,y);
		rs[v]=modify(rs[v],mid+1,r,x,y);
		s[v]=t[v]*(r-l+1)+s[ls[v]]+s[rs[v]];
		return v;
	}
	ll query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return s[u];
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y)+(min(r,y)-max(l,x)+1)*t[u];
	}
#undef mid
}

void _main() {
	scanf("%d%d",&n,&q);
	fo(i,1,q) scanf("%d%d%lld",&l[i],&r[i],&c[i]);
	fo(i,1,q) t[i]=mkp(l[i],r[i]);
	sort(t+1,t+q+1);
	fo(i,1,q-1)
		if(t[i].second<t[i+1].first) {
			printf("-1");
			return ;
		}
	fo(i,1,q) v[i]=i;
	sort(v+1,v+q+1,[](int x,int y){ return c[x]<c[y]; });
	segtree::build(1,1,n);
	rt[0]=psegtree::build(1,n);
	fo(i,1,q) {
		ans+=segtree::query(1,1,n,l[v[i]],r[v[i]])*c[v[i]];
		segtree::modify(1,1,n,l[v[i]],r[v[i]]);
		rt[i]=psegtree::modify(rt[i-1],1,n,l[v[i]],r[v[i]]);
	}
	fo(i,2,q) {
		if(psegtree::query(rt[i-1],1,n,l[v[i]],r[v[i]])!=0) {
			ans+=c[v[i]];
			continue;
		}
		int s=i+1,t=n;
		while(s<=t) {
			int mid=(s+t)/2;
			if(psegtree::query(rt[mid],1,n,l[v[i]],r[v[i]])!=r[v[i]]-l[v[i]]+1) t=mid-1;
			else s=mid+1;
		}
		ans+=c[v[t+1]];
	}
	printf("%lld",ans);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}