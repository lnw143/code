#include <cstdio>
#include <vector>
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c&15);
	return x;
}
using namespace std;
const int N = 2e5;
int n,q,a[N + 2],id[N + 2];
namespace tree {
	int ls[N + 2],rs[N + 2],l[N + 2],r[N + 2],tot;
	void dfs(int u) {
		if(ls[u]) {
			dfs(ls[u]);
			l[u]=l[ls[u]];
			++tot;
		} else l[u]=++tot;
		id[u]=tot;
		if(rs[u]) {
			dfs(rs[u]);
			r[u]=r[rs[u]];
		} else r[u]=tot;
	}
	void init() {
		for(int i=1; i<=n; ++i)
			ls[i]=read(),rs[i]=read();
		tree::dfs(1);
	}
}
namespace psegtree {
	const int S = N << 6;
	int tot,s[S + 2],ls[S + 2],rs[S + 2],rt[N + 2];
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		if(l<r) ls[u]=build(l,mid),rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int v,int l,int r,int x) {
		int u=++tot;
		ls[u]=ls[v],rs[u]=rs[v],s[u]=s[v];
		if(l==r) {
			++s[u];
			return u;
		}
		if(x<=mid) ls[u]=modify(ls[u],l,mid,x);
		else rs[u]=modify(rs[u],mid+1,r,x);
		s[u]=s[ls[u]]+s[rs[u]];
		return u;
	}
	int query(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return s[u];
		if(y<=mid) return query(ls[u],l,mid,x,y);
		if(mid<x) return query(rs[u],mid+1,r,x,y);
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
#undef mid
	void init() {
		static vector<int> t[N + 2];
		for(int i=1; i<=n; ++i) t[tree::l[i]].push_back(tree::r[i]);
		rt[n+1]=build(1,n);
		for(int i=n; i>=1; --i) {
			rt[i]=rt[i+1];
			for(auto j : t[i])
				rt[i]=modify(rt[i],1,n,j);
		}
	}
	int sum(int l,int r) {
		if(l>r) return 0;
		return query(rt[l],1,n,l,r);
	}
}
namespace segtree {
	const int S = N << 2;
	struct node {
		int l,r,s;
	} s[S + 2];
	node operator+(const node& x,const node& y) {
		if(!x.r) return y;
		if(!y.l) return x;
		return {x.l,y.r,x.s+y.s+psegtree::sum(x.r,y.l-1)};
	}
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			if(l==1||a[l-1]<=a[l]) s[u]={0,0,0};
			else s[u]={l,l,0};
			return ;
		}
		build(li);
		build(ri);
		s[u]=s[ls]+s[rs];
	}
	void modify(int u,int l,int r,int x,int k) {
		if(l==r) {
			if(k) s[u]={x,x,0};
			else s[u]={0,0,0};
			return ;
		}
		if(x<=mid) modify(li,x,k);
		else modify(ri,x,k);
		s[u]=s[ls]+s[rs];
	}
	node query(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return s[u];
		if(y<=mid) return query(li,x,y);
		if(mid<x) return query(ri,x,y);
		return query(li,x,y)+query(ri,x,y);
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
}
int main() {
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	n=read(),q=read();
	read();
	tree::init();
	for(int i=1; i<=n; ++i)
		a[id[i]]=read();
	psegtree::init();
	segtree::build(1,1,n);
	for(int i=1; i<=q; ++i) {
		if(read()==1) {
			int x=id[read()],y=read();
			if(1<x) segtree::modify(1,1,n,x,a[x-1]>y);
			if(x<n) segtree::modify(1,1,n,x+1,y>a[x+1]);
			a[x]=y;
		} else {
			int x=read();
			int l=tree::l[x],r=tree::r[x];
			auto [L,R,ans]=segtree::query(1,1,n,l,r);
			if(!L) printf("%d\n",psegtree::sum(l,r));
			else printf("%d\n",ans+psegtree::sum(l,L-1)+psegtree::sum(R,r));
		}
	}
	return 0;
}