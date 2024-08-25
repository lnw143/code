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

const int N = 500, P = 998244353;

int n,m,minn[N + 2][N + 2];

ll c[N + 2][N + 2],f[N + 2][N + 2][N + 2],s[N + 2][N + 2];

bool check(int l,int r,int x) {
	return minn[x][l]>r;
}

void _main() {
	scanf("%d%d",&n,&m);
	memset(minn,0x3f,sizeof(minn));
	fo(i,1,m) {
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		if(l==r) return printf("0"),void();
		minn[x][l]=min(minn[x][l],r);
	}
	fo(i,1,n)
		fd(j,i-1,1)
			minn[i][j]=min(minn[i][j],minn[i][j+1]);
	fo(i,1,n) c[i][0]=c[i][i]=1;
	fo(i,1,n)
		fo(j,1,i-1)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
	fo(i,1,n) s[i][i]=1;
	fo(i,2,n)
		fo(j,1,n-i+1) {
			fo(k,j,j+i-1) {
				if(!check(j,j+i-1,k)) continue;
				ll &prod=f[j][j+i-1][k];
				prod=1;
				if(j<k) (prod*=s[j][k-1])%=P;
				if(k<j+i-1) (prod*=s[k+1][j+i-1])%=P;
				ll l=k-j,r=j+i-1-k;
				(prod*=c[l+r][l])%=P;
			}
			fo(k,j,j+i-1) (s[j][j+i-1]+=f[j][j+i-1][k])%=P;
		}
	printf("%lld\n",s[1][n]);
}

void _init() {

}

char* last_address() {
	static char address_tail;
	return &address_tail;
}