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
int n,a[N + 2][2];
ll t[N + 2][2];
char s[N + 2];
void solve() {
	scanf("%d%s",&n,s+1);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i][s[i]=='0']);
		t[i][0]=t[i-1][0]+a[i][i&1];
		t[i][1]=t[i-1][1]+a[i][(i&1)^1];
	}
	ll ans=1e18;
	for(int i=1; i<n; ++i)
		for(auto j : {0,1})
			ans=min(ans,t[i][j]+a[i+1][(i^j)&1]+t[n][j^1]-t[i+1][j^1]);
	printf("%lld",ans);
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