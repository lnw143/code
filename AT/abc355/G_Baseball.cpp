// #pragma GCC optimize("O3,unroll-loops")

#pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
#pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")

#include <cstdio>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>

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
using db = double;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

// mt19937 rnd(random_device{}());
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
ll randll(ll l,ll r) { return uniform_int_distribution<ll>(l,r)(rnd); }
db randpr(db l=0,db r=1) { return uniform_real_distribution<db>(l,r)(rnd); }

const int N = 5e4, M = 225;

int n,k,p[N + 2],a[N + 2];

db f[N + 2],s[N + 2];

ll Ans=1ll<<60;

void calc() {
	fo(i,1,k)
		a[i]=upper_bound(s+1,s+n+1,randpr(0,s[n]))-s;
	sort(a+1,a+k+1);
	ll ans=0;
	for(int i=1,j=1; i<=n; ++i) {
		while(j<k&&abs(a[j]-i)>abs(a[j+1]-i)) ++j;
		ans+=(ll)p[i]*abs(a[j]-i);
	}
	Ans=min(Ans,ans);
	return ;
}

int main() {
	scanf("%d%d",&n,&k);
	fo(i,1,n)
		scanf("%d",&p[i]),f[i]=p[i];
	fo(i,1,n) fo(j,max(1,i-M),min(i+M,n))
		if(i!=j)
			f[i]+=p[j]/abs(i-j);
	fo(i,1,n) s[i]=s[i-1]+f[i];
	// while(runtime()<n/1e4) calc();
	while(runtime()<4.9) calc();
	printf("%lld",Ans);
	return 0;
}