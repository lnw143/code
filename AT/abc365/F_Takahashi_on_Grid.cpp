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

const int N = 2e5, logN = 20, Q = 2e5;

int n,l[N + 2],r[N + 2],q,f[logN][N * 2 + 2];
ll g[logN][N * 2 + 2];
pair<int,int> s[Q + 2],t[Q + 2];

template<int max(int,int)>
struct ST {
	int st[logN][N + 2];
	void init(int n,int *a) {
		fo(i,1,n) st[0][i]=a[i];
		fo(j,1,logN-1)
			fo(i,1,n-(1<<j)+1)
				st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	}
	int query(int l,int r) {
		int k=__lg(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
};

int imax(int x,int y) { return max(x,y); }
int imin(int x,int y) { return min(x,y); }

ST<imax> L;
ST<imin> R;

int find_next(int x,int y) {
	int l=x,r=n;
	while(l<=r) {
		int mid=(l+r)/2;
		if(L.query(x,mid)<=y&&y<=R.query(x,mid)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}

void _main() {
	scanf("%d",&n);
	fo(i,1,n) scanf("%d%d",&l[i],&r[i]);
	L.init(n,l);
	R.init(n,r);
	fo(i,1,n) {
		int t=find_next(i,l[i])+1;
		g[0][i*2-1]=t-i;
		if(t>n)
			--g[0][i*2-1],
			f[0][i*2-1]=n*2+1;
		else {
			if(r[t]<l[i])
				g[0][i*2-1]+=l[i]-r[t],
				f[0][i*2-1]=t*2;
			else 
				g[0][i*2-1]+=l[t]-l[i],
				f[0][i*2-1]=t*2-1;
		}
		t=find_next(i,r[i])+1;
		g[0][i*2]=t-i;
		if(t>n)
			--g[0][i*2],
			f[0][i*2]=n*2+1;
		else {
			if(r[t]<r[i])
				g[0][i*2]+=r[i]-r[t],
				f[0][i*2]=t*2;
			else 
				g[0][i*2]+=l[t]-r[i],
				f[0][i*2]=t*2-1;
		}
	}
	f[0][2*n+1]=2*n+1;
	fo(i,1,logN-1) {
		f[i][2*n+1]=2*n+1;
		g[i][2*n+1]=0;
		fo(j,1,2*n)
			f[i][j]=f[i-1][f[i-1][j]],
			g[i][j]=g[i-1][j]+g[i-1][f[i-1][j]];
	}
	scanf("%d",&q);
	fo(i,1,q) {
		int sx,sy,tx,ty;
		scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
		if(mkp(sx,sy)>mkp(tx,ty)) swap(sx,tx),swap(sy,ty);
		int t=find_next(sx,sy);
		if(t>=tx) {
			printf("%d\n",tx-sx+abs(ty-sy));
			continue;
		}
		++t;
		int k;
		ll ans;
		if(r[t]<sy) {
			k=2*t;
			ans=t-sx+sy-r[t];
		} else {
			k=2*t-1;
			ans=t-sx+l[t]-sy;
		}
		fd(j,logN-1,0)
			if(f[j][k]<=2*tx) {
				ans+=g[j][k];
				k=f[j][k];
			}
		printf("%lld\n",ans+tx-(k+1)/2+abs(ty-(k&1?l[(k+1)/2]:r[(k+1)/2])));
	}
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}