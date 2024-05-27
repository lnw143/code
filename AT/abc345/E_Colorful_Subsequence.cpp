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
	K = 5e2,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int n,k,c[N + 2],v[N + 2];
ll f[2][N + 2][K + 2];
void solve() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&c[i],&v[i]);
	
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