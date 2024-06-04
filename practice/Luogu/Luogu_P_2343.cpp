#include<cstdio>
using namespace std;
int m,q;
namespace splay {
	const int S = 1e5 + 1e4;
	int root,tot,fa[S + 2],sz[S + 2],cnt[S + 2],val[S + 2],ch[S + 2][2];
#define ls(u) ch[u][0]
#define rs(u) ch[u][1]
	void pushup(int u) { sz[u]=sz[ls(u)]+sz[rs(u)]+cnt[u]; }
	int newnode(int x) {
		int u=++tot;
		sz[u]=cnt[u]=1;
		val[u]=x;
		return u;
	}
	int get(int u) {
		return u==ch[fa[u]][1];
	}
	void rotate(int u) {
		int v=fa[u],p=fa[v],t=get(u);
		ch[v][t]=ch[u][!t];
		ch[u][!t]=v;
		fa[v]=u;
		if(ch[v][t]) fa[ch[v][t]]=v;
		fa[u]=p;
		if(p) ch[p][ch[p][1]==v]=u;
		pushup(v);
		pushup(u);
	}
	void splay(int u) {
		for(int v=fa[u]; v; rotate(u), v=fa[u])
			if(fa[v]) rotate(get(v)==get(u)?v:u);
		root=u;
	}
	void insert(int x) {
		if(!root) {
			root=newnode(x);
			return ;
		}
		int u=root;
		while(true) {
			if(val[u]==x) {
				++cnt[u];
				pushup(u);
				splay(u);
				return ;
			}
			int &v=ch[u][val[u]<x];
			if(!v) {
				v=newnode(x);
				fa[v]=u;
				pushup(u);
				splay(v);
				return ;
			}
			u=v;
		}
	}
	int kth(int k) {
		int u=root;
		while(true) {
			if(k<=sz[ls(u)]) u=ls(u);
			else {
				k-=sz[ls(u)];
				if(k<=cnt[u]) return val[u];
				k-=cnt[u];
				u=rs(u);
			}
		}
	}
}
int main() {
	scanf("%d%d",&m,&q);
	for(int i=1; i<=m; ++i) {
		int x;
		scanf("%d",&x);
		splay::insert(-x);
	}
	while(q--) {
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1) printf("%d\n",-splay::kth(x));
		else splay::insert(-x);
	}
	return 0;
}