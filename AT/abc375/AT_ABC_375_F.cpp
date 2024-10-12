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

const int N = 300, M = N * N, Q = 2e5;

int n,m,q,u[M + 2],v[M + 2],w[M + 2];

ll f[N + 2][N + 2],ans[Q + 2];

struct OP {
	int type,x,y;
};
vector<OP> op;

bool bz[M + 2];

void floyd(int k) {
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}

void _main() {
	memset(f,0x3f,sizeof(f));
	scanf("%d%d%d",&n,&m,&q);
	fo(i,1,m) {
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
	}
	fo(i,1,q) {
		int t;
		scanf("%d",&t);
		if(t==1) {
			int x;
			scanf("%d",&x);
			bz[x]=true;
			op.push_back({1,x,0});
		} else {
			int x,y;
			scanf("%d%d",&x,&y);
			op.push_back({2,x,y});			
		}
	}
	fo(i,1,m) if(!bz[i]) {
		f[u[i]][v[i]]=min(f[u[i]][v[i]],(ll)w[i]);
		f[v[i]][u[i]]=min(f[v[i]][u[i]],(ll)w[i]);
	}
	fo(i,1,n) floyd(i);
	reverse(all(op));
	q=0;
	for(auto [t,x,y] : op) {
		if(t==1) {
			f[u[x]][v[x]]=min(f[u[x]][v[x]],(ll)w[x]);
			f[v[x]][u[x]]=min(f[v[x]][u[x]],(ll)w[x]);
			floyd(u[x]);
			floyd(v[x]);
		} else {
			ans[++q]=f[x][y];
		}
	}
	fd(i,q,1) printf("%lld\n",ans[i]<f[0][0]?ans[i]:-1);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}