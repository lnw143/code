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
#include<iomanip>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
ll randint(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
db randpr(db l=0,db r=1) {
	return uniform_real_distribution<db>(l,r)(rnd);
}

const int
	N = 5e2,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
int n,d,a[N + 2][N + 2],f[N + 2][N + 2];
bool work(int k) {
	int ans=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) {
			int s=a[i][j]/d;
			if((s+i+j+k)%2!=0) {
				if(a[i][j]<0) --s;
				else ++s;
			}
			f[i][j]=s*d;
			ans+=abs(a[i][j]-f[i][j]);
		}
	if(ans*2<=d*n*n) {
		for(int i=1; i<=n; ++i,cout<<endl)
			for(int j=1; j<=n; ++j) 
				cout<<f[i][j]<<' ';
		return true;
	}
	return false;
}
void solve() {
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	cin>>n>>d;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			cin>>a[i][j];
	if(!work(0)) assert(work(1));
}

int main() {
	int T=1;
#if MULTITEST
	cin>>T;
#endif
	while(T--) solve();
	return 0;
}