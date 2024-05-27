#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int N = 2e5, Q = 5e5, A = 26;
int n,q;
char s[N + 2];
vector<int> d[N + 2];
namespace acam {
	int tot,tr[N + 2][A + 2],fail[N + 2];
	vector<int> insert(const char *s) {
		int u=0;
		vector<int> p;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
			u=tr[u][s[i]-'a'];
			p.push_back(u);
		}
		return p;
	}
	void build() {
		static int que[N + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				que[++t]=tr[0][i];
		while(h<t) {
			int u=que[++h];
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i];
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
}
namespace tree {
	const int logN = 20;
	using namespace acam;
	int dfc,dfn[N + 2],low[N + 2];
	vector<int> e[N + 2];
	void dfs(int u) {
		dfn[u]=++dfc;
		for(auto v : e[u])
			dfs(v);
		low[u]=dfc;
	}
	void init() {
		for(int i=1; i<=tot; ++i)
			e[fail[i]].push_back(i);
		dfs(0);
	}
}
namespace segtree {
	int tot,tr[N << 5],ls[N << 5],rs[N << 5],rt[N + 2];
	int build(int l,int r) {
		int u=++tot;
		if(l==r) return u;
		int mid=(l+r)/2;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x,int y) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		int mid=(l+r)/2;
		if(l==r) {
			tr[v]=tr[u]+y;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,y);
		else rs[v]=modify(rs[v],mid+1,r,x,y);
		tr[v]=tr[ls[v]]+tr[rs[v]];
		return v;
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return tr[u];
		int mid=(l+r)/2;
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
}
int main() {
	scanf("%d%d",&n,&q);
	using namespace acam;
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		d[i]=insert(s);
	}
	build();
	using namespace tree;
	using namespace segtree;
	init();
	rt[0]=build(1,dfc);
	for(int i=1; i<=n; ++i) {
		int root=rt[i-1];
		for(auto j : d[i])
			root=modify(root,1,dfc,dfn[j],1);
		rt[i]=root;
	}
	for(int i=1; i<=q; ++i) {
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		int u=d[k].back();
		printf("%d\n",query(rt[r],1,dfc,dfn[u],low[u])-query(rt[l-1],1,dfc,dfn[u],low[u]));
	}
	return 0;
}