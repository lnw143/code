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
ll randint(ll a,ll b) {
	return uniform_int_distribution<ll>(a,b)(rnd);
}
db randpr() {
	return uniform_real_distribution<db>(0,1)(rnd);
}

const int
	N = 5,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
const ll inf = 1ll << 60;
using mint = static_modint<P>;

#define MULTITEST 1
int a[N + 2],p[N + 2];
ll s,t;
ll calc(ll x) {
	if(p[4]>=p[5]) return p[5]*x;
	ll c=-3*s+t+2*x;
	assert(c*p[4]+(x-c)*p[5]==(t-3*s)*p[4]+(3*s-t)*p[5]+x*(2*p[4]-p[5]));
	return (t-3*s)*p[4]+(3*s-t)*p[5]+x*(2*p[4]-p[5]);
}
ll Div(ll a,ll b) { // ceil
	return a/b+!!(a%b);
}
ll solve(ll l,ll r) {
	return min(calc(l),calc(r));
}
void solve() {
	s=t=0;
	for(int i=1; i<=N; ++i) {
		scanf("%d",&a[i]);
		if(i!=3) t+=(ll)i*a[i],s+=a[i];
	}
	for(int i=1; i<=N; ++i)
		scanf("%d",&p[i]);
	if(t>=s*3) {
		printf("0\n");
		return ;
	}
	printf("%lld\n",solve(Div(3*s-t,2),3*s-t));
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