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

// #define MULTITEST
// #define FILE_IO_NAME ""

const int
	N = 2e5,
	M = N << 5,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

int n,m,v[N + 2],c[N + 2],a[N + 2];
ll ans[N + 2];
pair<int,int> t[N + 2];

namespace segtree {
	int tot,rt[N + 2],sz[M],ls[M],rs[M];
	ll tr[M];
	void pushup(int u) {
		tr[u]=tr[ls[u]]+tr[rs[u]];
		sz[u]=sz[ls[u]]+sz[rs[u]];
	}
	int build(int l,int r) {
		int u=++tot;
		if(l==r) return u;
		int mid=l+r>>1;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x,int y) {
		int v=++tot;
		ls[v]=ls[u];
		rs[v]=rs[u];
		if(l==r) {
			sz[v]=sz[u]+y;
			tr[v]=(ll)sz[v]*a[x];
			return v;
		}
		int mid=l+r>>1;
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,y);
		else rs[v]=modify(rs[v],mid+1,r,x,y);
		pushup(v);
		return v;
	}
	ll query(int u,int v,int l,int r,int k) {
		if(l==r) return (ll)a[l]*k;
		int mid=l+r>>1;
		if(k<=sz[ls[v]]-sz[ls[u]]) return query(ls[u],ls[v],l,mid,k);
		return tr[ls[v]]-tr[ls[u]]+query(rs[u],rs[v],mid+1,r,k-sz[ls[v]]+sz[ls[u]]);
	}
}

int id(int x) {
	return lower_bound(a+1,a+n+1,x,greater<int>())-a;
}

void solve(int x,int y,int u,int v) {
	if(x>y) return ;
	int mid=x+y>>1;
	int p=0;
	ans[mid]=-inf<ll>;
	rep(i,u,min(mid-m+1,v)) {
		using namespace segtree;
		ll cost=query(rt[i-1],rt[mid],1,n,m)-2*(c[mid]-c[i]);
		if(cost>ans[mid])  {
			ans[mid]=cost;
			p=i;
		}
	}
	solve(x,mid-1,u,p);
	solve(mid+1,y,p,v);
}

void _main() {
	cin>>n>>m;
	rep(i,1,n) cin>>v[i]>>c[i];
	rep(i,1,n) t[i]=mkp(c[i],v[i]);
	sort(t+1,t+n+1);
	rep(i,1,n) a[i]=v[i]=t[i].second,c[i]=t[i].first;
	sort(a+1,a+n+1,greater<int>());
	using namespace segtree;
	rt[0]=build(1,n);
	rep(i,1,n) rt[i]=modify(rt[i-1],1,n,id(v[i]),1);
	solve(m,n,1,n-m+1);
	ll Ans=-inf<ll>;
	rep(i,m,n) Ans=max(Ans,ans[i]);
	cout<<Ans;
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