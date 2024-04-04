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
#define ebk emplace_back
#define pbk push_back
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
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;

#define MULTITEST 1

int n,k,sum;
vector<int> e[N + 2];
int dfs(int u,int fa,const int lim) {
	int sz=1;
	for(auto v : e[u])
		if(v!=fa)
			sz+=dfs(v,u,lim);
	if(sz>=lim) {
		++sum;
		return 0;
	}
	return sz;
}
bool check(int x) {
	sum=0;
	dfs(1,-1,x);
	return sum>k;
}
void solve() {
	cin>>n>>k;
	for(int i=1; i<n; ++i) {
		int x,y;
		cin>>x>>y;
		e[x].ebk(y);
		e[y].ebk(x);
	}
	int l=1,r=n/(k+1),mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<l-1<<endl;
	for(int i=1; i<=n; ++i)
		e[i].clear();
}

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