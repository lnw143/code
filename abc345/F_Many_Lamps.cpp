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
mt19937 rnd(random_device{}());

const int
	N = 2e5,
	M = 2e5,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int n,m,k,u[M + 2],v[M + 2],c[N + 2],t[M + 2];
#define val(e) ((c[u[e]]?-1:1)+(c[v[e]]?-1:1))
void solve() {
	scanf("%d%d%d",&n,&m,&k);
	if(k&1) {
		printf("No");
		return ;
	}
	priority_queue<pair<int,int>> pq;
	for(int i=1; i<=m; ++i) {
		scanf("%d%d",&u[i],&v[i]);
		pq.emplace(i,2);
	}
	while(!pq.empty()&&k) {
		auto [e,w]=pq.top();
		if(w<=0||k<w) continue;
		pq.pop();
		if(val(e)!=w) {
			pq.emplace(e,val(e));
			continue;
		}
		k-=w;
		c[u[e]]^=1;
		c[v[e]]^=1;
		t[e]^=1;
		pq.emplace(e,val(e));
	}
	if(k==0) {
		printf("Yes\n");
		int sum=0;
		for(int i=1; i<=m; ++i)
			sum+=t[i];
		printf("%d\n",sum);
		for(int i=1; i<=m; ++i)
			if(t[i])
				printf("%d ",i);
	} else printf("No");
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