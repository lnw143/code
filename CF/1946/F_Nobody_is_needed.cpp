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
	N = 1e6,
	M = 0,
	K = 0,
	Q = 1e6,
	S = 0,
	P = 998244353// 1e9 + 7
;

int n,q,a[N + 2],p[N + 2];
ll f[N + 2];

namespace fenwick {
	ll t[N + 2];
	void add(int x,int f) {
		while(x<=n) {
			t[x]+=f;
			x+=x&-x;
		}
	}
	ll query(int x) {
		ll r=0;
		while(x) {
			r+=t[x];
			x&=x-1;
		}
		return r;
	}
}

void _main() {
	cin>>n>>q;
	for(int i=1; i<=n; ++i)
		cin>>a[i],p[a[i]]=i,fenwick::t[i]=0;
	vector<tuple<int,int,int>> asks(q);
	vector<ll> ans(q);
	int l=0;
	for(auto& [u,v,w] : asks)
		cin>>u>>v,w=l++;
	sort(asks.begin(),asks.end());
	for(int i=n; i>=1; --i) {
		f[1]=1;
		for(int j=1; j*a[i]<=n; ++j)
			for(int k=2; k*j*a[i]<=n; ++k)
				if(i<=p[j*a[i]]&&p[j*a[i]]<=p[k*j*a[i]])
					f[k*j]+=f[j];
		for(int j=1; j*a[i]<=n; ++j) {
			fenwick::add(p[j*a[i]],f[j]);
			f[j]=0;
		}
		while(true) {
			const auto [u,v,w]=asks.back();
			if(u!=i) break;
			ans[w]=fenwick::query(v)-fenwick::query(i-1);
			asks.pop_back();
		}
	}
	for(const auto &i : ans)
		cout<<i<<' ';
	cout<<endl;
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