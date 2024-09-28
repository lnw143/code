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
#ifdef ONLINE_JUDGE
#define debug(format,args...) void()
#define error(message,args...) void()
#else
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))
#endif

using namespace std;
using ll = long long;
char address_head;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;
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
const vector<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

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

const int N = 1e5;

int n,m,vmax,a[N + 2];

ll seed;

int Rand() {
	int ret=seed;
	seed=(seed*7+13)%1000000007;
	return ret;
}

struct node {
	int l,r;
	mutable ll v;
};

bool operator<(const node& x,const node& y) {
	return x.l<y.l;
}

set<node> odt;

set<node>::iterator split(int x) {
	auto it=odt.lower_bound({x,0,0});
	if(it!=odt.end()&&it->l==x) return it;
	auto [l,r,v]=*--it;
	odt.erase(it);
	odt.insert({l,x-1,v});
	return odt.insert({x,r,v}).first;
}

void assign(int l,int r,int x) {
	auto itr=split(r+1),itl=split(l);
	odt.erase(itl,itr);
	odt.insert({l,r,x});
}

void add(int l,int r,int x) {
	auto itr=split(r+1),itl=split(l);
	for(auto i=itl; i!=itr; ++i)
		i->v+=x;
}

ll kth(int l,int r,int x) {
	auto itr=split(r+1),itl=split(l);
	vector<pair<ll,int>> t;
	for(auto i=itl; i!=itr; ++i)
		t.emplace_back(i->v,i->r-i->l+1);
	sort(all(t));
	for(auto [i,j] : t)
		if(x<=j)
			return i;
		else
			x-=j;
}

ll qpow(ll a,ll n,ll p) {
	a%=p;
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

ll sum(int l,int r,int x,int y) {
	auto itr=split(r+1),itl=split(l);
	ll res=0;
	for(auto i=itl; i!=itr; ++i)
		(res+=(i->r-i->l+1)*qpow(i->v,x,y)%y)%=y;
	return res;
}

void _main() {
	scanf("%d%d%lld%d",&n,&m,&seed,&vmax);
	fo(i,1,n) a[i]=Rand()%vmax+1;
	fo(i,1,n) odt.insert({i,i,a[i]});
	fo(i,1,m) {
		int op=Rand()%4+1;
		int l=Rand()%n+1;
		int r=Rand()%n+1;
		if(l>r) swap(l,r);
		if(op==1) {
			int x=Rand()%vmax+1;
			add(l,r,x);
		} else if(op==2) {
			int x=Rand()%vmax+1;
			assign(l,r,x);
		} else if(op==3) {
			int x=Rand()%(r-l+1)+1;
			printf("%lld\n",kth(l,r,x));
		} else if(op==4) {
			int x=Rand()%vmax+1;
			int y=Rand()%vmax+1;
			printf("%lld\n",sum(l,r,x,y));
		}
	}
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}