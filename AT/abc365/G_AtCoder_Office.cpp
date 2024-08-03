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

const int N = 2e5, M = 2e5;

int n,m,q,t[M + 2],p[M + 2];

vector<int> e[N + 2],s[N + 2];

map<pair<int,int>,int> mp;

void _main() {
	scanf("%d%d",&n,&m);
	fo(i,1,m) {
		scanf("%d%d",&t[i],&p[i]);
		e[p[i]].pbk(i);
	}
	fo(i,1,n) {
		s[i].resize(e[i].size());
		fo(j,1,s[i].size()-1)
			s[i][j]=s[i][j-1]+(j&1?t[e[i][j]]-t[e[i][j-1]]:0);
	}
	scanf("%d",&q);
	fo(i,1,q) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(mp.count(mkp(x,y))) {
			printf("%d\n",mp[mkp(x,y)]);
			continue;
		}
		if(e[x].size()>e[y].size()) swap(x,y);
		int ans=0;
		for(int i=1; i<e[x].size(); i+=2) {
			int l=upper_bound(all(e[y]),e[x][i-1])-e[y].begin(),
			r=lower_bound(all(e[y]),e[x][i])-e[y].begin()-1;
			if(l<e[y].size()&&l%2==1) ans+=t[e[y][l]]-t[e[x][i-1]];
			if(r>=0&&r<e[y].size()&&r%2==0) ans+=t[e[x][i]]-t[e[y][r]];
			if(l<e[y].size()&&r<e[y].size()&&r>=0) ans+=s[y][r]-s[y][l];
		}
		if(x>y) swap(x,y);
		mp[mkp(x,y)]=ans;
		printf("%d\n",ans);
	}
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}