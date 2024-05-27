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
#define per(i,r,l) for(int i(r),i##End(l); i>=i##End; --i)
#define per_(i,r,l) for(int i(r),i##End(l); i>i##End; --i)

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
	N = 1e5,
	M = 26,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

ll n;
string s,t;
vec<int> pos[M + 2];

bool check(ll len) {
	ll sum=1;
	int now=0;
	for(int i=0; i<t.size(); ++i) {
		const auto &p = pos[t[i]-'a'];
		if(p.size()==0) return false;
		int rst=p.end()-lower_bound(p.begin(),p.end(),now);
		if(len>rst) {
			ll rem=len-rst-1;
			sum+=1+rem/p.size();
			now=p[rem%p.size()]+1;
		} else if(len==rst) {
			++sum;
			now=0;
		} else 
			now=p[p.size()-rst+len-1]+1;
		if(sum>n+(now?0:1)) return false;
	}
	return sum<=n+(now?0:1);
}

void _main() {
	cin>>n>>s>>t;
	for(int i=0; i<s.size(); ++i)
		pos[s[i]-'a'].ebk(i);
	ll l=1,r=inf<ll>,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<l-1;
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