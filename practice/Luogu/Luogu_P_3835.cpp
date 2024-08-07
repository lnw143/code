#include <cstdio>
#include <chrono>
#include <random>
using namespace std;
const int N = 5e5, inf = 0x7fffffff;
int n;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
namespace ptreap {
	const int S = N << 6;
	int tot,rt[N + 2],ls[S + 2],rs[S + 2],val[S + 2],sz[S + 2];
	unsigned int pri[S + 2];
	int newnode(int x) {
		int u=++tot;
		ls[u]=rs[u]=0;
		val[u]=x;
		sz[u]=1;
		pri[u]=rnd();
		return u;
	}
	int copy(int u) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		val[v]=val[u];
		sz[v]=sz[u];
		pri[v]=pri[u];
		return v;
	}
	void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) {
			int w=copy(u);
			rs[w]=merge(rs[w],v);
			pushup(w);
			return w;
		} else {
			int w=copy(v);
			ls[w]=merge(u,ls[w]);
			pushup(w);
			return w;
		}
	}
	void spval(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		u=copy(u);
		if(val[u]<=k) x=u,spval(rs[u],rs[u],y,k);
		else y=u,spval(ls[u],x,ls[u],k);
		pushup(u);
	}
	void sprnk(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		u=copy(u);
		if(k<=sz[ls[u]]) y=u,sprnk(ls[u],x,ls[u],k);
		else x=u,sprnk(rs[u],rs[u],y,k-sz[ls[u]]-1);
		pushup(u);
	}
	int first(int u) {
		while(ls[u]) u=ls[u];
		return u;
	}
	int last(int u) {
		while(rs[u]) u=rs[u];
		return u;
	}
	int ins(int u,int v) {
		int x,y;
		spval(u,x,y,v);
		return merge(merge(x,newnode(v)),y);
	}
	int del(int u,int v) {
		int x,y,z;
		spval(u,x,z,v);
		spval(x,x,y,v-1);
		return merge(merge(x,merge(ls[y],rs[y])),z);
	}
	int get_rnk(int u,int v) {
		int x,y;
		spval(u,x,y,v-1);
		return sz[x]+1;
	}
	int find_val(int u,int k) {
		int x,y;
		sprnk(u,x,y,k);
		return val[last(x)];
	}
	int find_pre(int u,int v) {
		int x,y;
		spval(u,x,y,v-1);
		if(!x) return -inf;
		return val[last(x)];
	}
	int find_nxt(int u,int v) {
		int x,y;
		spval(u,x,y,v);
		if(!y) return inf;
		return val[first(y)];
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		int id,op,x;
		scanf("%d%d%d",&id,&op,&x);
		using namespace ptreap;
		if(op==1) rt[i]=ins(rt[id],x);
		else if(op==2) rt[i]=del(rt[id],x);
		else {
			rt[i]=rt[id];
			if(op==3) printf("%d\n",get_rnk(rt[i],x));
			else if(op==4) printf("%d\n",find_val(rt[i],x));
			else if(op==5) printf("%d\n",find_pre(rt[i],x));
			else printf("%d\n",find_nxt(rt[i],x));
		}
	}
	return 0;
}