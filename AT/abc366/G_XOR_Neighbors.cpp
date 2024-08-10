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
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
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

const int N = 60;

int n,m;
bitset<N + 2> a[N + 2],all;

ll ans[N + 2];

bool solve() {
	fo(i,1,n) ans[i]=0;
	fo(i,1,n) {
		int tot=0;
		fo(j,1,n) 
			if(a[i][j]&&ans[j]==0) ++tot;
		fo(j,1,n)
			if(a[i][j]&&ans[j]==0) {
				if(tot>1) {
					ans[j]=randll(1,(1ll<<60)-1);
					--tot;
					continue;
				}
				for(int k=1; k<=n; ++k)
					if(j!=k&&a[i][k])
						ans[j]^=ans[k];
				break;
			}
	}
	fo(i,1,n) if(!all[i]) ans[i]=randll(1,(1ll<<60)-1);
	fo(i,1,n)
		if(!ans[i])
			return false;
	return true;
}

void _main() {
	scanf("%d%d",&n,&m);
	fo(i,1,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y]=a[y][x]=1;
	}
	fo(i,1,n) {
		fo(j,i,n)
			if(a[j][i])
				swap(a[i],a[j]);
		if(!a[i][i]) continue;
		fo(j,1,n)
			if(i!=j&&a[j][i])
				a[j]^=a[i];
	}
	fo(i,1,n)
		if(a[i].count()==1)
			return No();
	fo(i,1,n) all|=a[i];
	while(runtime()<1.9&&!solve());
	fo(i,1,n) if(!ans[i]) return No();
	Yes();
	fo(i,1,n) printf("%lld ",ans[i]);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}