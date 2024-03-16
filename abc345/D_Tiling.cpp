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
	N = 7,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;
#define MULTITEST 0
int n,m,h,w,a[N + 2],b[N + 2],x[N + 2],y[N + 2];
bool dfs(int s,int u) {
	if(runtime()>1.9) return false;
	while(!(s&(1<<(u-1)))&&u<=n) ++u;
	if(u>n) return true;
	for(int t=0; t<2; ++t,swap(a[u],b[u]))
		for(int i=1; i<=h-a[u]+1; ++i)
			for(int j=1; j<=w-b[u]+1; ++j) {
				bool flag=true;
				for(int k=1; k<u; ++k)
					if((s&(1<<(k-1)))&&(!(x[k]+a[k]<=i||i+a[u]<=x[k]||y[k]+b[k]<=j||j+b[u]<=y[k]))) {
							flag=false;
							break;
						}
				if(flag) {
					x[u]=i;
					y[u]=j;
					if(dfs(s,u+1)) return true;
				}
			}
	return false;
}
void solve() {
	scanf("%d%d%d",&n,&h,&w);
	m=1<<n;
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=0; i<m; ++i) {
		ll sum=0;
		for(int j=0; j<n; ++j)
			if(i&(1<<j))
				sum+=a[j+1]*b[j+1];
		if(sum==h*w&&dfs(i,1)) {
			printf("Yes");
			return ;
		}
	}
	printf("No");
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