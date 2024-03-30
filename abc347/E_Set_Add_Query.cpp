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
int n,q,p[N + 2];
ll ans[N + 2],s[N + 2];
void solve() {
	cin>>n>>q;
	int sz=0;
	for(int i=1; i<=q; ++i) {
		int x;
		cin>>x;
		if(p[x]) {
			--sz;
			s[i]=s[i-1]+sz;
			ans[x]+=s[i-1]-s[p[x]-1];
			p[x]=0;
		} else {
			++sz;
			s[i]=s[i-1]+sz;
			p[x]=i;
		}
	}
	for(int i=1; i<=n; ++i)
		if(p[i]) cout<<s[q]-s[p[i]-1]+ans[i]<<" ";
		else cout<<ans[i]<<" ";
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