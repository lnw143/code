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
	N = 1,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int n,q,x[N + 2],y[N + 2],a[Q + 2],b[Q + 2],A,B;
mint g;
ll gen() {
	return (g*=48271).val();
}
void solve() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&x[i],&y[i]);
	scanf("%d%d%d",&q,&A,&B);
	for(int i=1; i<=q; ++i) {
		a[i]=gen()%(2*A+1)-A;
		b[i]=gen();
		b[i]=((ll)b[i]*P+gen())%(2*B+1)-B;
	}
	
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