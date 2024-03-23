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
	N = 1e5,
	logN = 62,
	M = 26,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
ll k;
int n,m,nx[M],anc[M][N + 2][logN];
ll w[M][N + 2][logN];
char s[N + 2],t[N + 2];
bool check(ll x) {
	int u=0;
	ll ret=0;
	for(int i=1; i<=m; ++i) {
		int h=t[i]-'a';
		ll r=x;
		for(int j=logN-1; j>=0; --j)
			if(x&(1ll<<j)) {
				ret+=w[h][u][j];
				if(ret>=k) return false;
				u=anc[h][u][j];
			}
	}
	return true;
}
ll binary_search() {
	ll l=0,r=1e18,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
void solve() {
	scanf("%lld%s%s",&k,s+1,t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for(int i=1; i<=n; ++i)
		if(!nx[s[i]-'a'])
			nx[s[i]-'a']=i;
	for(int i=1; i<=m; ++i)
		if(!nx[t[i]-'a']) return printf("0"),void();
	for(int i=n; i>=0; --i) {
		for(int j=0; j<M; ++j) if(nx[j])
			anc[j][i][0]=nx[j],
			w[j][i][0]=(nx[j]<=i);
		if(i>0) nx[s[i]-'a']=i;
	}
	for(int i=0; i<M; ++i) if(nx[i])
		for(int l=1; l<logN; ++l)
			for(int j=0; j<=n; ++j) {
				anc[i][j][l]=anc[i][anc[i][j][l-1]][l-1];
				w[i][j][l]=w[i][j][l-1]+w[i][anc[i][j][l-1]][l-1];
			}
	printf("%lld",binary_search());
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