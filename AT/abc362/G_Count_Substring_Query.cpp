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

const int N = 5e5, A = 26;

int n,p[N + 2];
string s;
vector<int> e[N + 2];
int dfc,dfn[N + 2],low[N + 2];

namespace fenwick {
	int s[N + 5];
	void add(int u,int x) {
		for(; u<=dfc; u+=u&-u) s[u]+=x;
	}
	int sum(int u) {
		int r=0;
		for(; u; u&=u-1) r+=s[u];
		return r;
	}
	int sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
}

namespace acam {
	int tot,tr[N + 2][A + 2],fail[N + 2];
	int insert(const string &s) {
		int u=0;
		for(auto c : s) {
			if(!tr[u][c-'a']) tr[u][c-'a']=++tot;
			u=tr[u][c-'a'];
		}
		return u;
	}
	void build() {
		queue<int> Q;
		fo(i,0,A-1)
			if(tr[0][i])
				Q.push(tr[0][i]);
		while(!Q.empty()) {
			int u=Q.front();
			Q.pop();
			e[fail[u]].push_back(u);
			fo(i,0,A-1)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],Q.push(tr[u][i]);
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
}

void dfs(int u) {
	dfn[u]=++dfc;
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
}

void _main() {
	cin>>s>>n;
	fo(i,1,n) {
		string t;
		cin>>t;
		p[i]=acam::insert(t);
	}
	acam::build();
	dfs(0);
	int u=0;
	for(auto c : s) {
		u=acam::tr[u][c-'a'];
		fenwick::add(dfn[u],1);
	}
	fo(i,1,n)
		printf("%d\n",fenwick::sum(dfn[p[i]],low[p[i]]));
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}