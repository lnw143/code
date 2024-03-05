#include<cstdio>
#include<random>
using namespace std;
const int N(1e5);
int n,m;
mt19937 rnd(random_device{}());
namespace treap {
	int rt,tot,ls[N + 2],rs[N + 2],tag[N + 2],pri[N + 2],val[N + 2],siz[N + 2];
	int newnode(int v) {
		++tot;
		return val[tot]=v,pri[tot]=rnd(),siz[tot]=1,tot;
	}
	void pushdown(int u) {
		if(tag[u]) tag[ls[u]]^=1,tag[rs[u]]^=1,swap(ls[u],rs[u]),tag[u]=0;
	}
	void pushup(int u) {
		siz[u]=siz[ls[u]]+siz[rs[u]]+1;
	}
	void split(int u,int v,int &x,int &y) {
		if(!u) return x=y=0,void();
		pushdown(u);
		if(v<=siz[ls[u]]) y=u,split(ls[u],v,x,ls[u]);
		else x=u,split(rs[u],v-siz[ls[u]]-1,rs[u],y);
		pushup(u);
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		pushdown(u);
		pushdown(v);
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		else return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void reverse(int l,int r) {
		int x,y,z;
		split(rt,r,x,z);
		split(x,l-1,x,y);
		tag[y]^=1;
		rt=merge(merge(x,y),z);
	}
	void print(int u) {
		if(!u) return ;
		pushdown(u);
		print(ls[u]);
		printf("%d ",val[u]);
		print(rs[u]);
	}
}
int main() {
	using namespace treap;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		rt=merge(rt,newnode(i));
	for(int i=1; i<=m; ++i) {
		int l,r;
		scanf("%d%d",&l,&r);
		reverse(l,r);
	}
	print(rt);
	return 0;
}