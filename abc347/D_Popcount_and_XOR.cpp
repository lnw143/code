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
	N = 60,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int a,b;
ll c;
int popcnt(ll x) {
	if(!x) return 0;
	return popcnt(x&(x-1))+1;
}
ll pow2(int x) {
	return 1ll<<x;
}
void solve() {
	cin>>a>>b>>c;
	int k=popcnt(c),t=(a+b-k)/2;
	if((a+b-k)%2||a+b<k||a<t||b<t) return cout<<-1,void();
	int u=a-t,v=b-t;
	ll x=0,y=0;
	for(int i=0; i<N; ++i)
		if(c&pow2(i)) {
			if(u) {
				x|=pow2(i);
				--u;
			} else {
				assert(v>0);
				y|=pow2(i);
				--v;
			}
		} else if(t>0) {
			--t;
			x|=pow2(i);
			y|=pow2(i);
		}
	if(!(popcnt(x)==a&&popcnt(y)==b&&(x^y)==c)) cout<<-1;
	else cout<<x<<' '<<y;
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