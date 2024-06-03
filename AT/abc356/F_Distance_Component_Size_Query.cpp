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

void _init() {

}

const int Q = 2e5, N = Q, logN = 20;

int n,q,t[N + 2];
ll k,x[N + 2];
vector<ll> v;
set<int> st;

int id(ll x) {
	return lower_bound(v.begin(),v.end(),x)-v.begin();
}

struct segtree {
	int t[N << 2];
#define ls (u<<1)
#define rs (ls|1)
#define mid (l+r>>1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void modify(int u,int l,int r,int x,int y) {
		if(r<x||x<l) return ;
		if(l==r) {
			t[u]=y;
			return ;
		}
		if(x<=mid) modify(li,x,y);
		else modify(ri,x,y);
		t[u]=t[ls]+t[rs];
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return t[u];
		return query(li,x,y)+query(ri,x,y);
	}
#undef ls
#undef rs
#undef mid
#undef li
#undef ri
} f,g;

int pre(int x) {
	return st.empty()||*st.begin()>=x?-1:*(--st.lower_bound(x));
}

int nxt(int x) {
	return st.empty()||*st.rbegin()<=x?-1:*st.upper_bound(x);
}

bool check(int l,int r) {
	return f.query(1,0,n-1,l,r)>g.query(1,0,n-1,l,r);
}

void _main() {
	scanf("%d%lld",&q,&k);
	fo(i,1,q) {
		scanf("%d%lld",&t[i],&x[i]);
		v.ebk(x[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	n=v.size();
	fo(i,1,q) {
		const int p=id(x[i]);
		if(t[i]==1) {
			const int l=pre(p),r=nxt(p);
			if(st.count(p)) {
				f.modify(1,0,n-1,p,0);
				st.erase(p);
				if(l!=-1&&x[i]-v[l]<=k) g.modify(1,0,n-1,l,(r!=-1&&v[r]-v[l]<=k));
				g.modify(1,0,n-1,p,0);
			} else {
				f.modify(1,0,n-1,p,1);
				st.insert(p);
				g.modify(1,0,n-1,p,(r!=-1&&v[r]-x[i]<=k));
				if(l!=-1) g.modify(1,0,n-1,l,(x[i]-v[l]<=k));
			}
		} else {
			auto findR = [&]() -> int {
				int l=p,r=n-1;
				while(l<=r) {
					int mid=(l+r)/2;
					if(check(p,mid)) r=mid-1;
					else l=mid+1;
				}
				return r+1;
			};
			auto findL = [&]() -> int {
				int l=1,r=p;
				while(l<=r) {
					int mid=(l+r)/2;
					if(check(mid-1,p-1)) l=mid+1;
					else r=mid-1;
				}
				return l-1;
			};
			printf("%d\n",f.query(1,0,n-1,findL(),findR()));
		}
	}
}

char* last_address() {
	static char address_tail;
	return &address_tail;
}