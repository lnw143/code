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
#define clock() chrono::system_clock::now()
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

const int N = 3e5, M = N * 2;

int n,q,a[N + 2],b[N + 2];

bool ans[N + 2];

vector<int> num;

namespace fenwick {
	ll s[N + 2];
	int mp[M + 2];
	void add(int x,int v) {
		for(int i=x; i<=n; i+=i&-i) s[i]+=v;
	}
	void init() {
		for(int i=1; i<=num.size(); ++i) mp[i]=randint(0,1e9);
		memset(s,0,sizeof(s));
		for(int i=1; i<=n; ++i) {
			a[i]=b[i];
			s[i]+=mp[a[i]];
			if(i+(i&-i)<=n) s[i+(i&-i)]+=s[i];
		}
	}
	void change(int x,int v) {
		add(x,mp[v]-mp[a[x]]);
		a[x]=v;
	}
	ll sum(int x) {
		ll r=0;
		for(int i=x; i; i&=i-1) r+=s[i];
		return r;
	}
	ll sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
}

struct query {
	int op,x,y,z;
} qr[N + 2];

void _main() {
	scanf("%d%d",&n,&q);
	fo(i,1,n) scanf("%d",&a[i]),num.push_back(a[i]);
	fo(i,1,q) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x,v;
			scanf("%d%d",&x,&v);
			qr[i]={op,x,v,0};
			num.push_back(v);
		} else {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			qr[i]={op,l,r,k};
		}
	}
	sort(all(num));
	num.erase(unique(all(num)),num.end());
	fo(i,1,n) b[i]=a[i]=lower_bound(all(num),a[i])-num.begin()+1;
	fo(i,1,q) if(qr[i].op==1) qr[i].y=lower_bound(all(num),qr[i].y)-num.begin()+1;
	fo(i,1,50) {
		fenwick::init();
		fo(i,1,q)
			if(qr[i].op==1)
				fenwick::change(qr[i].x,qr[i].y);
			else if(fenwick::sum(qr[i].x,qr[i].y)%qr[i].z!=0)
				ans[i]=true;
	}
	fo(i,1,q)
		if(qr[i].op==2)
			NO(ans[i]);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}