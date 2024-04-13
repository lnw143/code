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
	N = 2e5,
	M = 22,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

int n,cnt,t[N + 2],b[N + 2],f[1 << M];
ll a[N + 2],p[N + 2],s[N + 2],m;

void _main() {
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	ll m_=m;
	for(ll i=2; i*i<=m_; ++i) {
		if(m_%i==0) {
			p[++cnt]=i;
			s[cnt]=1;
			while(m_%i==0) m_/=i,++t[cnt],s[cnt]*=i;
		}
	}
	if(m_>1) {
		p[++cnt]=m_;
		s[cnt]=m_;
		t[cnt]=1;
	}
	assert(cnt<M);
	ll k=1<<cnt;
	rep(i,1,n)
		if(m%a[i]==0) {
			ll sta=0;
			rep(j,1,cnt) sta|=(a[i]%s[j]==0)<<(j-1);
			per(j,0,k-1) {
				f[j|sta]+=f[j];
				if(f[j|sta]>=P) f[j|sta]-=P;
			}
			++f[sta]%=P;
			if(f[sta]>=P) f[sta]-=P;
		}
	cout<<f[k-1];
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