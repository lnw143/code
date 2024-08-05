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
#define fst first
#define scd second
#define all(v) v.begin(),v.end()
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))

using namespace std;
using ll = long long;
char address_head;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;
#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = double> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
double randpr(double l=0,double r=1) { return uniform_real_distribution<double>(l,r)(rnd); }
void Yes(bool f=true) { printf(f?"Yes\n":"No\n"); }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { printf(f?"yes\n":"no\n"); }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { printf(f?"YES\n":"NO\n"); }
void NO(bool f=true) { YES(!f); }
const vector<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

#define MULTITEST
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

template<ll Base,ll P> struct shash {
	vector<ll> h,bs;
	ll query(int l,int r) {
		ll res=h[r];
		if(l>0) res-=h[l-1]*bs[r-l+1]%P;
		return (res%P+P)%P;
	}
	shash(string s) {
		h.resize(s.size());
		bs.resize(s.size());
		h[0]=s[0];
		bs[0]=1;
		fo(i,1,h.size()-1)
			h[i]=(h[i-1]*Base+s[i])%P,
			bs[i]=bs[i-1]*Base%P;
	}
};

void _main() {
	string s,x,y;
	cin>>s>>x>>y;
	ll tx=0,ty=0;
	for(auto c : x) if(c=='1') ++tx;
	for(auto c : y) if(c=='1') ++ty;
	ll sx=x.size()-tx,sy=y.size()-ty;
	if(sx==sy) return Yes();
	if(tx==ty) return No();
	if((sy-sx)*(int)s.size()%(tx-ty)!=0||(sy-sx)*(int)s.size()/(tx-ty)<0) return No();
	int tlen=(sy-sx)*(int)s.size()/(tx-ty);
	if(tlen>s.size()) return Yes();
	string t=s.substr(0,tlen);
	shash<131, 998244353> sf(s),tf(t);
	shash<13331, (ll)1e9+7> sg(s),tg(t);
	int i=0,j=0,p=0,q=0;
	const auto gs = [&](char c) {
		return int(c=='0'?s.size():t.size());
	};
	while(i<x.size()&&j<y.size()) {
		int len=min(gs(x[i])-p,gs(y[j])-q);
		if((x[i]=='0'?sf:tf).query(p,p+len-1)!=(y[j]=='0'?sf:tf).query(q,q+len-1)||
		(x[i]=='0'?sg:tg).query(p,p+len-1)!=(y[j]=='0'?sg:tg).query(q,q+len-1))
			return No();
		p+=len;
		if(p==gs(x[i])) ++i,p=0;
		q+=len;
		if(q==gs(y[j])) ++j,q=0;
	}
	Yes();
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}