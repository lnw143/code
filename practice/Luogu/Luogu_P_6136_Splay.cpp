#include <cstdio>
using namespace std;
const int N = 1e5, M = 1e6;
namespace splay {
	const int S = N + M;
	int root,tot,fa[S + 2],ch[S + 2][2],val[S + 2],cnt[S + 2],sz[S + 2];
#define ls(u) ch[u][0]
#define rs(u) ch[u][1]
	void pushup(int u) { sz[u]=sz[ls(u)]+sz[rs(u)]+cnt[u]; }
	int get(int u) { return ch[fa[u]][1]==u; }
	void rotate(int u) {
		int p=fa[u],g=fa[p],t=get(u);
		ch[p][t]=ch[u][!t];
		fa[ch[u][!t]]=p;
		ch[u][!t]=p;
		fa[p]=u;
		fa[u]=g;
		if(g) ch[g][rs(g)==p]=u;
		pushup(p);
		pushup(u);
	}
	void splay(int u) {
		for(int p=fa[u]; p; rotate(u),p=fa[u])
			if(fa[p]) rotate(get(p)==get(u)?p:u);
		root=u;
	}
	void clear(int u) {
		fa[u]=ls(u)=rs(u)=val[u]=cnt[u]=sz[u]=0;
	}
	int newnode(int x) {
		int u=++tot;
		cnt[u]=1;
		val[u]=x;
		sz[u]=1;
		ch[u][0]=ch[u][1]=0;
		return u;
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
				break;
			}
			int p=u;
			u=ch[u][val[u]<x];
			if(!u) {
				ch[p][val[p]<x]=u=newnode(x);
				fa[u]=p;
				splay(u);
				break;
			}
		}
	}
	int kth(int k) {
		int u=root;
		while(true) {
			if(k<=sz[ls(u)]) {
				u=ls(u);
				continue;
			}
			k-=sz[ls(u)];
			if(k<=cnt[u]) {
				splay(u);
				return val[u];
			}
			k-=cnt[u];
			u=rs(u);
		}
	}
	int rnk(int x) {
		int u=root,res=1;
		while(u) {
			if(x<val[u]) {
				u=ls(u);
				continue;
			}
			res+=sz[ls(u)];
			if(x==val[u]) {
				splay(u);
				return res;
			}
			res+=cnt[u];
			u=rs(u);
		}
		return res;
	}
	int __pre() {
		int u=ls(root);
		while(rs(u)) u=rs(u);
		splay(u);
		return u;
	}
	int __nxt() {
		int u=rs(root);
		while(ls(u)) u=ls(u);
		splay(u);
		return u;
	}
	void del(int x) {
		rnk(x);
		int u=root;
		if(cnt[u]>1) {
			--cnt[u];
			pushup(u);
			return ;
		}
		if(!ls(u)&&!rs(u)) {
			clear(u);
			root=0;
			return ;
		}
		if(ls(u)&&rs(u)) {
			int v=__pre();
			rs(v)=rs(u);
			fa[rs(u)]=v;
		} else {
			root=ls(u)?ls(u):rs(u);
			fa[root]=0;
		}
		clear(u);
	}
	int pre(int x) {
		insert(x);
		int res=val[__pre()];
		del(x);
		return res;
	}
	int nxt(int x) {
		insert(x);
		int res=val[__nxt()];
		del(x);
		return res;
	}
#undef ls
#undef rs
}
int n,m,a[N + 2],last,ans;
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		splay::insert(x);
	}
	for(int i=1; i<=m; ++i) {
		int opt,x;
		scanf("%d%d",&opt,&x);
		using namespace splay;
		x^=last;
		if(opt==1) insert(x);
		if(opt==2) del(x);
		if(opt==3) ans^=last=rnk(x);
		if(opt==4) ans^=last=kth(x);
		if(opt==5) ans^=last=pre(x);
		if(opt==6) ans^=last=nxt(x);
	}
	printf("%d",ans);
	return 0;
}