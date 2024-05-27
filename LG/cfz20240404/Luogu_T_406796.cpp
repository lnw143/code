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
#define endl '\n'

using namespace std;

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
	N = 2e5,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
int n,a[N + 2],b[N + 2];
void solve() {
	cin>>n;
	int sum=0;
	b[n]=0;
	for(int i=0; i<n; ++i) {
		cin>>a[i];
		b[n-i-1]=a[i]==sum;
		sum^=a[i];
	}
	cin>>a[n];
	if(a[n]==sum) {
		for(int i=0; i<=n; ++i)
			if(b[i]) b[i]=0;
			else {
				b[i]=1;
				break;
			}
	}
	bool p=false;
	for(int i=n; i>=0; --i)
		if(p|=b[i])
			cout<<b[i];
	if(!p) cout<<0;
	cout<<endl;
}

#define MULTITEST 1
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int T=1;
#if MULTITEST
	cin>>T;
#endif
	while(T--) solve();
	return 0;
}