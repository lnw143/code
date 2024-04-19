#pragma GCC optimize("O3,unroll-loops")

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
constexpr db eps = 1e-12;

template<typename T> using vec = vector<T>;
template<typename T> using heap = priority_queue<T,vec<T>,greater<T>>;
template<typename T> using big_heap = priority_queue<T>;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
db randpr(db l=0,db r=1) { return uniform_real_distribution<db>(l,r)(rnd); }

void Yes(bool f=true) { cout<<(f?"Yes":"No")<<endl; }
void No(bool f=true) { Yes(!f); }
void yes(bool f=true) { cout<<(f?"yes":"no")<<endl; }
void no(bool f=true) { yes(!f); }
void YES(bool f=true) { cout<<(f?"YES":"NO")<<endl; }
void NO(bool f=true) { YES(!f); }

template<typename Tp1,typename Tp2> bool umx(Tp1 &x,Tp2 y) { return y>x?x=y,true:false; }
template<typename Tp1,typename Tp2> bool umn(Tp1 &x,Tp2 y) { return y<x?x=y,true:false; }

ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

template<int P> struct ModInt {
  public:
	using mint = ModInt<P>;
	using mintp = mint&;

	operator const int&() { return x; }

	mint operator+(const int& t) const { return x+t>=P?x+t-P:x+t; }
	mint operator-(const int& t) const { return x<t?x-t+P:x-t; }
	mintp operator+=(const int& t) { return ((x+=t)>=P)&&(x-=P),(*this); }
	mintp operator-=(const int& t) { return ((x-=t)<0)&&(x+=P),(*this); }

	mint operator++(int) { return (++x>=P)?x=0,P-1:x-1;}
	mint operator--(int) { return (--x<0)?x=P-1,0:x+1;}
	mintp operator++() { return (++x>=P)?x=0,(*this):(*this);}
	mintp operator--() { return (--x<0)?x=P-1,(*this):(*this);}

	mint operator*(const int& t) const { return (ll)x*t%P; }
	mintp operator*=(const int& t) { return x=(ll)x*t%P,(*this); }

	int v() { return x; }

	ModInt():x(0) {}
	template<typename Tp> ModInt(Tp y) {
		if(y<0) x=y%P+P;
		else if(y<P) x=y;
		else x=y%P;
	}
  private:
	int x;
};

constexpr int
	N = 2e5,
	logN = 20,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

using mint = ModInt<P>::mint;

// #define MULTITEST
// #define FILE_IO_NAME ""

int n,a[N + 2],fa[logN][N * 2 + 2],ans[N * 2 + 2];
bool bz[N + 2];
vec<int> e[N * 2 + 2];

int find(int x,int u) { return fa[x][u]==u?u:fa[x][u]=find(x,fa[x][u]); }
void unite(int x,int u,int v) {
	if(x<0||find(x,u)==find(x,v)) return ;
	fa[x][find(x,u)]=find(x,v);
	int len=1<<x-1;
	unite(x-1,u,v);
	unite(x-1,u+len,v+len);
}

void _main() {
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep_(i,0,logN) rep(j,1,n*2) fa[i][j]=j;
	rep(i,1,n) unite(0,i,2*n-i+1);
	rep(i,1,n) {
		int l=i-a[i],r=i+a[i],k=a[i]*2+1;
		r=2*n-r+1;
		per(j,0,logN-1)
			if(k&(1<<j)) {
				unite(j,l,r);
				l+=1<<j;
				r+=1<<j;
			}
	}
	rep(i,1,n)
		if(1<i-a[i]&&i+a[i]<n) {
			int u=find(0,i-a[i]-1),v=find(0,i+a[i]+1);
			if(u==v) return No(),void();
			e[u].ebk(v);
			e[v].ebk(u);
		}
	Yes();
	rep(i,1,n) {
		int u=find(0,i);
		for(auto v : e[u])
			bz[ans[v]]=true;
		ans[u]=1;
		while(bz[ans[u]]) ++ans[u];
		for(auto v : e[u])
			bz[ans[v]]=false;
		cout<<ans[u]<<' ';
	}
}

void _init() {

}

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
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