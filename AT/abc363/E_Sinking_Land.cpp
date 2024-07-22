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

const int N = 1e3, M = 1e5;

int n,m,k,a[N + 2][N + 2],ans[M + 2];
bool vis[N + 2][N + 2];

int dfs(int x,int y,int s) {
	if(x<1||n<x||y<1||m<y||a[x][y]>s||vis[x][y]) return 0;
	vis[x][y]=true;
	int res=1;
	for(auto [u,v] : way4)
		res+=dfs(x+u,y+v,s);
	return res;
}

void _main() {
	scanf("%d%d%d",&n,&m,&k);
	fo(i,1,n)
		fo(j,1,m)
			scanf("%d",&a[i][j]);
	vector<pair<int,int>> Q;
	fo(i,1,n)
		fo(j,1,m)
			Q.ebk(i,j);
	sort(all(Q),[](auto x,auto y) {
		return a[x.first][x.second]<a[y.first][y.second];
	});
	fo(i,1,n*m) {
		auto [x,y]=Q[i-1];
		for(auto [u,v] : way4) 
			if(x==1||x==n||y==1||y==m||vis[x+u][y+v]) {
				ans[a[x][y]]+=dfs(x,y,a[x][y]);
				break;
			}
	}
	int Ans=0;
	fo(i,1,k) {
		Ans+=ans[i];
		printf("%d\n",n*m-Ans);
	}
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}