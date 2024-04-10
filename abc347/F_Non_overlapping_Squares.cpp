#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

#define rep(i,l,r) for(int i(l),i##End(r); i<=i##End; ++i)
#define rep_(i,l,r) for(int i(l),i##End(r); i<i##End; ++i)
#define per(i,l,r) for(int i(r),i##End(l); i>=i##End; --i)
#define per_(i,l,r) for(int i(r),i##End(l); i>i##End; --i)

#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define endl '\n'

using namespace std;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;

template<typename T> constexpr T inf = 0;
template<> constexpr int inf<int> = 1e9;
template<> constexpr ll inf<ll> = 1e18;
template<> constexpr db inf<db> = 1e18;
template<> constexpr ldb inf<ldb> = 1e18;

template<typename T> using vec = vector<T>;
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;

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
// #define FILE_IO_NAME ""

const int
	N = 1e3,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

int n,m,a[N + 2][N + 2];
ll s[N + 2][N + 2],b[N + 2][N + 2],lu[N + 2][N + 2],ru[N + 2][N + 2],ld[N + 2][N + 2],rd[N + 2][N + 2],ans;
void _main() {
	cin>>n>>m;
	rep(i,1,n)
		rep(j,1,n)
			cin>>a[i][j],s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	rep(i,1,n-m+1) rep(j,1,n-m+1) b[i][j]=s[i+m-1][j+m-1]+s[i-1][j-1]-s[i-1][j+m-1]-s[i+m-1][j-1];
	rep(i,m,n) rep(j,m,n) lu[i][j]=max({lu[i-1][j],lu[i][j-1],b[i-m+1][j-m+1]});
	rep(i,m,n) per(j,1,n-m+1) ru[i][j]=max({ru[i-1][j],ru[i][j+1],b[i-m+1][j]});
	per(i,1,n-m+1) rep(j,m,n) ld[i][j]=max({ld[i+1][j],ld[i][j-1],b[i][j-m+1]});
	per(i,1,n-m+1) per(j,1,n-m+1) rd[i][j]=max({rd[i+1][j],rd[i][j+1],b[i][j]});
	rep(i,m,n-m)
		rep(j,m,n-m)
			ans=max({ans,
			lu[i][j]+ld[i+1][j]+rd[1][j+1],
			lu[i][n]+ld[i+1][j]+rd[i+1][j+1],
			lu[n][j]+ru[i][j+1]+rd[i+1][j+1],
			lu[i][j]+ru[i][j+1]+rd[i+1][1],
			lu[n][j]+b[i+1][j+1]+rd[1][j+m+1],
			lu[i][n]+b[i+1][j+1]+rd[i+m+1][1]
			});
	cout<<ans;
}

void _init() {

}

int main() {
#if defined(FILE_IO_NAME) && !defined(CPH)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	_init();
	int T=1;
#if defined(MULTITEST)
	cin>>T;
#endif
	while(T--) _main();
	return 0;
}