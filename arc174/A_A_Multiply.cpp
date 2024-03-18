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
	N = 3e5,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int n,c,a[N + 2];
ll ans,s[N + 2];

void solve() {
	scanf("%d%d",&n,&c);
	--c;
	ll mn=0,mx=0;
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
		if(c>0) ans=max(ans,c*(s[i]-mn));
		else ans=max(ans,c*(s[i]-mx));
		mn=min(mn,s[i]);
		mx=max(mx,s[i]);
	}
	printf("%lld",s[n]+ans);
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