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
int n,a[N + 2],t[N + 2],x[N + 2],sum[2];
ll ans[N + 2];
bool bz[2][N + 2];
void solve() {
	scanf("%d%d%d",&sum[0],&sum[1],&n);
	for(int i=1; i<=n; ++i)
		scanf("%d%d%d",&t[i],&a[i],&x[i]);
	ans[0]=(ll)sum[0]*sum[1];
	for(int i=n; i>=1; --i) {
		--t[i];
		if(bz[t[i]][a[i]]) continue;
		bz[t[i]][a[i]]=true;
		ans[x[i]]+=sum[!t[i]];
		ans[0]-=sum[!t[i]];
		--sum[t[i]];
	}
	int tot=0;
	for(int i=0; i<=N; ++i)
		if(ans[i]) ++tot;
	printf("%d\n",tot);
	for(int i=0; i<=N; ++i)
		if(ans[i])
			printf("%d %lld\n",i,ans[i]);
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