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
	N = 0,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// (int)1e9 + 7
;

void _main() {
	int n,x,m=0,ans=-1;
	cin>>n>>x;
	vec<int> a(n);
	++x;
	for(auto & i : a)
		cin>>i,m^=i;
	for(int i=30; i>=0; --i) {
		const int k = 1 << i;
		if((m&k)&&(x&k)) continue;
		else if((m&k)&&!(x&k)) break;
		else {
			int f=0;
			vec<int> b;
			for(const auto & i : a) {
				if(f) b.back()^=i;
				else b.pbk(i);
				if(i&k) f^=1;
			}
			if(!(m&k)&&(x&k))
				ans=max(ans,(int)b.size());
			else {
				assert(!(m&k)&&!(x&k));
				a=b;
			}
		}
	}
	cout<<ans<<endl;
	return ;
}

int main() {
#if defined(FILE_IO_NAME) && !defined(CPH)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
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