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

vector<ll> v;

int n,q,t[Q + 2],l[N + 2],r[N + 2];
ll k,x[Q + 2];

namespace fenwick {
	int t[N + 2];
	void add(int x) {
		while(x<=n) {
			++t[x];
			x+=x&-x;
		}
	}
	int sum(int x) {
		int res=0;
		while(x) {
			res+=t[x];
			x&=x-1;
		}
		return res;
	}
	int sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
}

namespace dsu {
	int fa[logN][N + 2],l[logN][N + 2],r[logN][N + 2];
	void init() {
		fu(i,0,logN) fu(j,0,N) fa[i][j]=j,l[i][j]=r[i][j]=j;
	}
	int find(int k,int u) {
		return fa[k][u]==u?u:fa[k][u]=find(k,fa[k][u]);
	}
	void link(int k,int x,int y) {
		x=find(k,x),y=find(k,y);
		if(x==y) return ;
		fa[k][y]=x;
		l[k][x]=min(l[k][x],l[k][y]);
		r[k][x]=max(r[k][x],r[k][y]);
		if(k==0) return ;
		link(k-1,x,y);
		link(k-1,x+(1<<(k-1)),y+(1<<(k-1)));
	}
	void merge(int x,int y,int len) {
		fu(i,0,logN)
			if(len&(1<<i)) {
				link(i,x,y);
				x+=1<<i;
				y+=1<<i;
			}
	}
}

int findl(int x) {
	++x;
	int l=1,r=x-1;
	while(l<=r) {
		int mid=(l+r)/2;
		if(fenwick::sum(x-mid,x-1)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}

int findr(int x) {
	++x;
	int l=1,r=n-x;
	while(l<=r) {
		int mid=(l+r)/2;
		if(fenwick::sum(x+1,x+mid)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
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
	fu(i,0,n) {
		l[i]=lower_bound(v.begin(),v.end(),v[i]-k)-v.begin();
		r[i]=upper_bound(v.begin(),v.end(),v[i]+k)-v.begin()-1;
	}
	dsu::init();
	fo(i,1,q) {
		int p=lower_bound(v.begin(),v.end(),x[i])-v.begin();
		if(t[i]==1) {
			using namespace fenwick;
			add(p+1);
			int x=p-findl(p),y=p+findr(p);
			dsu::merge(x,x+1,y-x);
		}
		else {
			int u=dsu::find(0,p);
			printf("%d\n",fenwick::sum(dsu::l[0][u]+1,dsu::r[0][u]+1));
		}
	}
}

char* last_address() {
	static char address_tail;
	return &address_tail;
}