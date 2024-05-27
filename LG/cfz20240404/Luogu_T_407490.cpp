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
#define endl '\n'

using namespace std;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;

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

const int
	N = 1e5,
	logN = 20,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;

int n,m,s,t,x[N + 2],y[N + 2];
vector<int> e[N + 2],leaf;
map<pair<int,int>,int> ans;
int dep[N + 2],anc[N + 2][logN];
void dfs(int u,int fa) {
	anc[u][0]=fa;
	for(int i=1; i<logN; ++i)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(auto v : e[u])
		if(v!=fa) {
			dep[v]=dep[u]+1;
			dfs(v,u);
		}
}
int lca(int u,int v) {
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=logN-1; i>=0; --i)
		if(dep[anc[v][i]]>=dep[u])
			v=anc[v][i];
	if(u==v) return u;
	for(int i=logN-1; i>=0; --i)
		if(anc[u][i]!=anc[v][i])
			u=anc[u][i],
			v=anc[v][i];
	return anc[u][0];
}
void solve() {
	cin>>n;
	for(int i=1; i<n; ++i) {
		cin>>x[i]>>y[i];
		e[x[i]].ebk(y[i]);
		e[y[i]].ebk(x[i]);
	}
	cin>>m;
	m=(ll)m*n%P;
	dfs(1,1);
	for(int i=1; i<=n; ++i)
		if(e[i].size()==1)
			leaf.ebk(i);
	s=leaf[0],t=leaf[1];
	int l=lca(s,t);
	if(dep[s]+dep[t]-2*dep[l]+1==n) {
		for(int i=1; i<n; ++i) {
			if(x[i]==s||y[i]==s) cout<<m*(P+1ll)/2%P<<' ';
			else cout<<P<<' ';
		}
		return ;
	}
}

#define MULTITEST 0
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int T=1;
#if MULTITEST
	cin>>T;
#endif
	while(T--) solve();
	return 0;
}