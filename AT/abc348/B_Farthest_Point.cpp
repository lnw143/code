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
#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define endl '\n'

using namespace std;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;

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

// #define MULTITEST
// #define FILENAME "a"

const int
	N = 1e2,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// (int)1e9 + 7
;

int n,x[N + 2],y[N + 2];

int sqr(int x) {
	return x*x;
}
void _main() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>x[i]>>y[i];
	for(int i=1; i<=n; ++i) {
		int mx=0,v=0;
		for(int j=1; j<=n; ++j)
			if(sqr(x[i]-x[j])+sqr(y[i]-y[j])>mx) {
				mx=sqr(x[i]-x[j])+sqr(y[i]-y[j]);
				v=j;
			}
		cout<<v<<endl;
	}
}

int main() {
#if defined(FILENAME) && !defined(CPH)
	freopen(FILENAME".in","r",stdin);
	freopen(FILENAME".out","w",stdout);
#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int T=1;
#if defined(MULTITEST)
	cin>>T;
#endif
	while(T--) _main();
	return 0;
}