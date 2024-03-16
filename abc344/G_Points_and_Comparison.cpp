#pragma GCC optimize("Ofast,inline,unroll-loops,fast-math,no-stack-protector")
#pragma GCC target("sse,sse2,avx,avx2,bmi,bmi2,lzcnt,popcnt,avx512vl,avx512f,tune=native")
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
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using db = double;
using ldb = long double;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

const int
	N = 5e3,
	Q = 1e7,
	P = (1ll << 31) - 1
;
const db eps = 1e-12;

#define MULTITEST 0
int n,q,k[N + 2],b[N + 2],t[Q + 2],e[N + 2],p[N + 2],A;
ll x[Q + 2],y[Q + 2],B,ans,g;
using Tp = tuple<db,int,int>;
vector<Tp> v;
ll gen() {
	return (g*=48271)%=P;
}
int find_ans(ll x,ll y) {
	int l=1,r=n,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(k[e[mid]]*x+b[e[mid]]<=y) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
void solve() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&k[i],&b[i]),b[i]=-b[i],e[i]=i;
	scanf("%d%lld%d%lld",&q,&g,&A,&B);
	for(int i=1; i<=q; ++i) {
		x[i]=gen()%(2*A+1)-A;
		y[i]=gen();
		y[i]=(y[i]*P+gen())%(2*B+1)-B;
		y[i]=-y[i];
		t[i]=i;
	}
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if(k[i]!=k[j])
				v.push_back(make_tuple(db(b[j]-b[i])/(k[i]-k[j]),i,j));
	sort(v.begin(),v.end());
	sort(t+1,t+q+1,[](int u,int v) { return x[u]<x[v]; });
	sort(e+1,e+n+1,[=](int u,int v) { return k[u]<k[v]||k[u]==k[v]&&b[u]<b[v]; });
	for(int p=0,i=1; i<=q; ++i) {
		const int u=t[i];
		const ll X=x[u],Y=y[u];
		vector<Tp> r;
		while(p<v.size()) {
			auto [o,p,q]=v[p];
			if(o<X-eps) r.push_back(v[p++]);
			else break;
		}
		
		ans+=find_ans(X,Y);
	}
	printf("%lld",ans);
}

int main() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#if MULTITEST
	int T;
	scanf("%d",&T);
	while(T--) solve();
#else
	solve();
#endif
	return 0;
}