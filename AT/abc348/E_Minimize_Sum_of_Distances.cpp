#include<cstdio>
#include<cmath>
#include<cstdint>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
#include<bitset>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdlib>
#include<complex>
#include<deque>
#include<functional>
#include<iostream>
#include<limits>
#include<numeric>
#include<iomanip>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define endl '\n'

using namespace std;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
ll randint(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
db randpr(db l=0,db r=1) {
	return uniform_real_distribution<db>(l,r)(rnd);
}

// #define MULTITEST
// #define FILENAME "a"

const int
	N = 1e5,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// (int)1e9 + 7
;

int n,c[N + 2];
ll sz[N + 2],f[N + 2];
vector<int> e[N + 2];
void dfs(int u,int fa) {
	sz[u]=c[u];
	for(auto v : e[u])
		if(v!=fa) {
			dfs(v,u);
			sz[u]+=sz[v];
			f[u]+=sz[v]+f[v];
		}
}
void dp(int u,int fa) {
	for(auto v : e[u])
		if(v!=fa) {
			f[v]=f[u]+sz[1]-sz[v]*2;
			dp(v,u);
		}
}
void _main() {
	cin>>n;
	for(int i=1; i<n; ++i) {
		int u,v;
		cin>>u>>v;
		e[u].ebk(v);
		e[v].ebk(u);
	}
	for(int i=1; i<=n; ++i)
		cin>>c[i];
	dfs(1,1);
	dp(1,1);
	cout<<*min_element(f+1,f+n+1);
}

int main() {
#if defined(FILENAME) && !defined(CPH)
	freopen(FILENAME".in","r",stdin);
	freopen(FILENAME".out","w",stdout);
#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int T=1;
#if defined(MULTITEST)
	cin>>T;
#endif
	while(T--) _main();
	return 0;
}