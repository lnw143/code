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

constexpr int
	N = 3,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

int n=3,a[N + 2][N + 2],c[N + 2][N + 2];

bool line(int x1,int y1,int x2,int y2,int x3,int y3) {
	return c[x1][y1]&&c[x1][y1]==c[x2][y2]&&c[x2][y2]==c[x3][y3];
}

bool checked() {
	rep(i,1,n) if(line(i,1,i,2,i,3)||line(1,i,2,i,3,i)) return true;
	return line(1,1,2,2,3,3)||line(3,1,2,2,1,3);
}

bool full() {
	rep(i,1,n) rep(j,1,n) if(!c[i][j]) return false;
	return true;
}

bool check(int u) {
	ll sum[3]={0,0,0};
	rep(i,1,n) rep(j,1,n) sum[c[i][j]]+=a[i][j];
	return sum[3^u]<sum[u];
}

bool dfs(int u) {
	if(checked()) return false;
	if(full()) return check(u);
	rep(i,1,n)
		rep(j,1,n)
			if(!c[i][j]) {
				c[i][j]=u;
				bool r=dfs(u^3);
				c[i][j]=0;
				if(!r) return true;
			}
	return false;
}

void _main() {
	rep(i,1,n)
		rep(j,1,n)
			cin>>a[i][j];
	cout<<(dfs(1)?"Takahashi":"Aoki");
}

void _init() {

}

int main() {
#if defined(FILE_IO_NAME) && ! defined(ONLINE_JUDGE)
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