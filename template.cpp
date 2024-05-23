// #pragma GCC optimize("O3,unroll-loops")

// #pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
// #pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

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

#define fo(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define fd(i,l,r) for(int i(l),i##END(r); i>=i##END; --i)
#define fu(i,l,r) for(int i(l),i##END(r); i<i##END; ++i)

#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define mkt make_tuple
#define debug(format,args...) fprintf(stderr,format,##args)
#define error(message,args...) (debug(message,##args),exit(1))

using namespace std;

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using db = double;
using ldb = long double;

char address_head;
template<typename T> constexpr T inf = 0;
template<> constexpr int inf<int> = 0x3f3f3f3f;
template<> constexpr ll inf<ll> = 1ll << 60;

#ifdef __SIZEOF_INT128__
using i128 = __int128;
using ui128 = unsigned __int128;
template<> constexpr i128 inf<i128> = i128(1) << 120;
#endif

constexpr db eps = 1e-12;

#define vec vector
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
db randpr(db l=0,db r=1) { return uniform_real_distribution<db>(l,r)(rnd); }

template<typename Tp1,typename Tp2> bool umx(Tp1 &x,Tp2 y) { return y>x?x=y,true:false; }
template<typename Tp1,typename Tp2> bool umn(Tp1 &x,Tp2 y) { return y<x?x=y,true:false; }

void Yes(bool f=true) { printf(f?"Yes\n":"No\n"); }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { printf(f?"yes\n":"no\n"); }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { printf(f?"YES\n":"NO\n"); }
void NO(bool f=true) { YES(!f); }
template<typename ...Args> string formatStr(const char* __format,Args ...args) {
	static char buf[1<<16];
	sprintf(buf,__format,args...);
	return buf;
}
ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}
ll mul(ll a,ll b,ll p) {
	a%=p,b%=p;
	ll x=0;
	for(; b; b>>=1,a=(a<<1)%p) if(b&1) x=(x+a)%p;
	return x;
}
ll qPow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=mul(a,a,p)) if(n&1) x=mul(x,a,p);
	return x;
}

const vec<pair<int,int>> way4{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, way4_{{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, way8{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

// #define MOD 998244353 // 1000000007

#ifdef MOD
const int P = MOD;
struct ModInt {
  public:
	operator int() const { return x; }

	ModInt operator+(ModInt t) const { return x+t; }
	ModInt operator-(ModInt t) const { return x-t; }
	ModInt operator*(ModInt t) const { return (ll)x*t; }
	ModInt operator/(ModInt t) const { return (ll)x*t.inv(); }

	ModInt operator++(int) { int p=x++; return x%=P,p; }
	ModInt operator--(int) { int p=x--; return x%=P,p; }
	ModInt& operator++() { return ++x%=P,(*this);}
	ModInt& operator--() { return --x%=P,(*this);}
	
	ModInt& operator+=(ModInt t) { return (*this)=(*this)+t; }
	ModInt& operator-=(ModInt t) { return (*this)=(*this)-t; }
	ModInt& operator*=(ModInt t) { return (*this)=(*this)*t; }
	ModInt& operator/=(ModInt t) { return (*this)=(*this)/t; }
	
	bool operator==(ModInt t) { return safe_mod()==t.safe_mod(); }
	bool operator!=(ModInt t) { return safe_mod()!=t.safe_mod(); }

	int safe_mod() const { return (x%P+P)%P; }

	ModInt inv() const { return qpow(x,P-2,P); }

	ModInt():x(0) {}
	template<typename Tp> ModInt(Tp y): x(y%P) {}
  private:
	int x;
};
using mint = ModInt;
#endif

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

void _main() {

}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}