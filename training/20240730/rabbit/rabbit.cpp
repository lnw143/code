#include <cstdio>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
using namespace std;
const int N = 2.5e6;
int n,m,a[N + 2],b[N + 2],at,bt;
int c[N + 2],d[N + 2];
long long ans;
namespace treap {
	const int S = N + 10;
	int tot,rt,ls[S],rs[S],val[S],tag[S],sz[S];
	unsigned int pri[S];
	mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
	inline int newnode(int x) {
		int u=++tot;
		pri[u]=rnd();
		val[u]=x;
		sz[u]=1;
		tag[u]=ls[u]=rs[u]=0;
		return u;
	}
	inline void pushdown(int u) {
		if(!tag[u]) return ;
		if(ls[u]) tag[ls[u]]+=tag[u],val[ls[u]]+=tag[u];
		if(rs[u]) tag[rs[u]]+=tag[u],val[rs[u]]+=tag[u];
		tag[u]=0;
	}
	inline void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		pushdown(u),pushdown(v);
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		else return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	template<typename ...Args> int merge(int u,int v,Args ...args) {
		return merge(merge(u,v),args...);
	}
	void spval(int u,int &x,int &y,int v) {
		if(!u) return x=y=0,void();
		pushdown(u);
		if(val[u]<=v) x=u,spval(rs[u],rs[u],y,v);
		else y=u,spval(ls[u],x,ls[u],v);
		pushup(u);
	}
	void sprnk(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		pushdown(u);
		if(sz[ls[u]]<k) x=u,sprnk(rs[u],rs[u],y,k-sz[ls[u]]-1);
		else y=u,sprnk(ls[u],x,ls[u],k);
		pushup(u);
	}
	void insert(int v) {
		int x,y;
		spval(rt,x,y,v);
		rt=merge(merge(x,newnode(v)),y);
	}
	int Min(int u) {
		while(ls[u]) pushdown(u),u=ls[u];
		return val[u];
	}
	int Max(int u) {
		while(rs[u]) pushdown(u),u=rs[u];
		return val[u];
	}
	int solve(int s) {
		int x,y;
		spval(rt,x,y,0);
		s=min(s,sz[y]);
		rt=y;
		if(!s) return 0;
		sprnk(rt,x,y,sz[rt]-s);
		--tag[y],--val[y];
		int l=Max(x),r=Min(y);
		if(l>r) {
			int u,v,p,q;
			spval(x,u,v,r);
			spval(y,p,q,l);
			rt=merge(u,p,v,q);
		} else
			rt=merge(x,y);
		return s;
	}
}
int main() {
	scanf("%d%d%d%d%d%d",&n,&m,&a[1],&at,&b[1],&bt);
	for(int i=2; i<=n; ++i) a[i]=(a[i-1]*58ll+at)%(m+1);
	for(int i=2; i<=m; ++i) b[i]=(b[i-1]*58ll+bt)%(n+1);
	for(int i=1; i<=n; ++i) treap::insert(a[i]);
	for(int i=1; i<=m; ++i) ans+=treap::solve(b[i]);
	printf("%lld",ans);
	return 0;
}