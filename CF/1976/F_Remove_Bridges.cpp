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

const int N = 3e5, logN = 20;

int n;

vector<int> e[N + 2],leaf;

int dep[N + 2],anc[logN][N + 2];

bool vis[N + 2];

void dfs(int u,int p) {
	anc[0][u]=p;
	fo(i,1,logN-1) anc[i][u]=anc[i-1][anc[i-1][u]];
	for(auto v : e[u])
		if(v!=p) {
			dep[v]=dep[u]+1;
			dfs(v,u);
		}
	if(e[u].size()==1&&u!=1) leaf.push_back(u);
}

int calc(int u) {
	if(vis[u]) return 0;
	int res=0,tmp=dep[u];
	fd(i,logN-1,0)
		if(!vis[anc[i][u]])
			u=anc[i][u],res|=1<<i;
	return u==1?tmp:res+1;
}

void _main() {
	scanf("%d",&n);
	fo(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[1]=0;
	dfs(1,1);
	priority_queue<pair<int,int>> hp;
	for(auto u : leaf) hp.emplace(dep[u],u);
	int k=0,ans=n-1;
	while(hp.size()) {
		auto [depn,u]=hp.top();
		hp.pop();
		int dep_=calc(u);
		if(vis[u]||depn!=dep_) {
			if(!vis[u]) hp.emplace(dep_,u);
			continue;
		}
		ans-=depn;
		++k;
		if(k%2==1) printf("%d ",ans);
		for(; !vis[u]; u=anc[0][u]) vis[u]=true;
	}
	fo(i,(k+1)/2+1,n-1) printf("0 ");
	putchar('\n');
	fo(i,1,n) e[i].clear(),vis[i]=false;
	leaf.clear();
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}