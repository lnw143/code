#line 1 "templates.cpp"

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

#define MULTITEST
// #define FILE_IO_NAME ""

#line 1 "main.cpp"

const int
	N = 2e5,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 1e9 + 7
;

ll fac[N + 2],inv[N + 2],ifac[N + 2];

ll C(ll n,ll m) {
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

void _main() {
	int n,m,k;
	cin>>n>>m>>k;
	vec<int> p(m),s(k);
	for(auto &i : p)
		cin>>i;
	for(auto &i : s)
		cin>>i;
	if(p[0]!=1||s.back()!=n||p.back()!=s[0]) return cout<<0<<endl,void();
	ll ans=C(n-1,s[0]-1);
	for(int i=1; i<p.size(); ++i) 
		ans=ans*fac[p[i]-p[i-1]-1]%P*C(p[i]-2,p[i]-p[i-1]-1)%P;
	for(int i=1; i<s.size(); ++i)
		ans=ans*fac[s[i]-s[i-1]-1]%P*C(n-s[i-1]-1,s[i]-s[i-1]-1)%P;
	cout<<ans<<endl;
}

void _init() {
	fac[0]=fac[1]=inv[1]=ifac[1]=ifac[0]=1;
	for(int i=2; i<=N; ++i) {
		fac[i]=fac[i-1]*i%P;
		inv[i]=(P-P/i)*inv[P%i]%P;
		ifac[i]=ifac[i-1]*inv[i]%P;
	}
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