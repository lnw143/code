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
	N = 20,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
const vector<pair<int,int>> w{
	{-1, 0},{1, 0},{0, -1},{0, 1},
	// {-1, 1},{1, 1},{1, -1},{-1, -1},
};

int n,a[N + 2][N + 2],f[N + 2][N + 2],g[N + 2][N + 2],h[N + 2][N + 2];

void solve() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)	
			cin>>a[i][j];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			for(auto [u,v] : w) {
				int x=i+u,y=j+v;
				if(x<1||x>n||y<1||y>n) continue;
				if(a[x][y]) {
					f[i][j]+=a[x][y];
					++g[i][j];
				}
			}
	for(int i=1; i<=n; ++i,putchar('\n'))
		for(int j=1; j<=n; ++j)
			cout<<(a[i][j]||g[i][j]==0?a[i][j]:f[i][j]/g[i][j])<<" ";
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