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
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using db = double;
using ldb = long double;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

const int
	N = 2e5,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
ll n,a,b;

void solve() {
	cin>>n>>a>>b;
	const ll p=a+b;
	vector<pair<ll,ll>> t;
	for(int i=1; i<=n; ++i) {
		ll d;
		cin>>d;
		d=(d-1)%p;
		t.emplace_back(a-d,p-d-1);
		t.emplace_back(a+p-d,1e18);
	}
	t.emplace_back(-1e18,-1);
	sort(t.begin(),t.end());
	for(int i=1; i<t.size(); ++i)
		if(t[i-1].second+1<t[i].first)
			return cout<<"Yes",void();
	cout<<"No";
}

int main() {
#if MULTITEST
	int T;
	scanf("%d",&T);
	while(T--) solve();
#else
	solve();
#endif
	return 0;
}