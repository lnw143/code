// #pragma GCC optimize("O3,unroll-loops")

// #pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
// #pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

#include <cstdio>
#include <cmath>
#include <cstdint>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
#include <bitset>
#include <random>
#include <chrono>
#include <cassert>
#include <cstdlib>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define fo(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define fd(i,l,r) for(int i(l),i##END(r); i>=i##END; --i)
#define fu(i,l,r) for(int i(l),i##END(r); i<i##END; ++i)
#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define mkt make_tuple
#define fir first
#define sec second
#define all(v) v.begin(),v.end()
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))

using namespace std;
using ll = long long;
char address_head;
#define vec vector
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;
#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = double> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
double randpr(double l=0,double r=1) { return uniform_real_distribution<double>(l,r)(rnd); }
void Yes(bool f=true) { printf(f?"Yes\n":"No\n"); }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { printf(f?"yes\n":"no\n"); }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { printf(f?"YES\n":"NO\n"); }
void NO(bool f=true) { YES(!f); }
const vec<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

// #define MULTITEST
// #define FILE_IO_NAME ""

void _main();
void _init();
char* last_address();

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	_init();
	int T=1;
	debug("Memory:%.8lfMib\n",double(last_address()-&address_head)/pow(2,20));
#if defined(MULTITEST)
	scanf("%d",&T);
#endif
	while(T--) _main();
	return 0;
}

ll n;

vector<ll> fac;

ll rev(ll x) {
	ll y=0;
	for(; x; x/=10) y=y*10+x%10;
	return y;
}

bool cont0(ll x) {
	do
		if(x%10==0) return true;
	while(x/=10);
	return false;
}

bool check() {
	map<ll,int> mp;
	vector<ll> ans,ans2;
	for(auto i : fac)
		++mp[i];
	ll mid=-1;
	for(auto [i,j] : mp) {
		ll i_=rev(i);
		if(i==i_&&j%2==1) {
			if(mid!=-1) return false;
			mid=i;
		}
		if(i<=i_) {
			fo(k,1,i==i_?j/2:j)
				ans.pbk(i);
		}
	}
	if(mid!=-1) ans.pbk(mid);
	for(auto [i,j] : mp) {
		ll i_=rev(i);
		if(i>=i_) {
			fo(k,1,i==i_?j/2:j)
				ans2.pbk(i);
		}
	}
	fd(i,ans2.size()-1,0)
		ans.pbk(ans2[i]);
	string str="";
	str+=to_string(ans[0]);
	fo(i,1,ans.size()-1)
		str+='*',
		str+=to_string(ans[i]);
	if(str.size()<=1000) {
		cout<<str;
		return true;
	}
	return false;
}

bool dfs(ll x) {
	if(x<2) return check();
	const auto test = [&](ll y) -> bool {
		ll z=rev(y);
		if(!cont0(y)) {
			if(x/y%z==0) {
				fac.push_back(y);
				fac.push_back(z);
				if(dfs(x/y/z)) return true;
				fac.pop_back();
				fac.pop_back();
			}
			if(y==z) {
				fac.pbk(y);
				if(dfs(x/y)) return true;
				fac.pop_back();
			}
		}
		return false;
	};
	for(ll i=2; i*i<=x; ++i) 
		if(x%i==0) {
			if(test(i)) return true;
			if(i*i!=x) 	
				if(test(x/i)) return true;
		}
	return test(x);
}

void _main() {
	scanf("%lld",&n);
	if(n==1) {
		printf("1");
		return ;
	}
	if(!dfs(n)) printf("-1");
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}