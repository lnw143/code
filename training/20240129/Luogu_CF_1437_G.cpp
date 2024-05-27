#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
const int N = 3e5, S = 3e5, A = 26;
int n,m,i,p[N + 2],a[N + 2];
char s[S + 2];
namespace CutTree {
	int em,e[S + 2],ls[S + 2],nx[S + 2];
	int sz[S + 2],wson[S + 2],dfn[S + 2],dfc,rnk[S + 2],top[S + 2],fa[S + 2];
	void insert(int x,int y) {
		e[++em]=y;
		nx[em]=ls[x];
		ls[x]=em;
	}
}
namespace ACAM {
	int tr[S + 2][A + 2],fail[S + 2],w[S + 2],tot;
	bool bz[S + 2];
	multiset<int> st[S + 2];
}
namespace SegmentTree {
	int tr[(S << 2) + 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void mktree(int x,int l,int r) {
		if(l==r) {
			tr[x]=ACAM::bz[CutTree::rnk[l]]-1;
			return ;
		}
		int mid=(l+r)/2;
		mktree(li);
		mktree(ri);
		tr[x]=max(tr[ls],tr[rs]);
		return ;
	}
	void ask(int x,int l,int r,int L,int R,int &MAX) {
		if(tr[x]<=MAX||r<L||R<l) return ;
		if(L<=l&&r<=R) {
			MAX=max(MAX,tr[x]);
			return ;
		}
		int mid=(l+r)/2;
		ask(li,L,R,MAX);
		ask(ri,L,R,MAX);
	}
	void change(int x,int l,int r,int f,int g) {
		if(r<f||f<l) return ;
		if(l==r) {
			tr[x]=g;
			return ;
		}
		int mid=(l+r)/2;
		if(f<=mid) change(li,f,g);
		else change(ri,f,g);
		tr[x]=max(tr[ls],tr[rs]);
		return ;
	}
#undef ls
#undef rs
#undef li
#undef ri
}
namespace CutTree {
	void dfs(int x) {
		sz[x]=1;
		for(int i=ls[x]; i; i=nx[i]) {
			fa[e[i]]=x;
			dfs(e[i]);
			sz[x]+=sz[e[i]];
			if(sz[e[i]]>sz[wson[x]])
				wson[x]=e[i];
		}
	}
	void dfs2(int x,int tp) {
		dfn[x]=++dfc;
		rnk[dfc]=x;
		top[x]=tp;
		if(wson[x]) dfs2(wson[x],tp);
		for(int i=ls[x]; i; i=nx[i])
			if(e[i]!=wson[x])
				dfs2(e[i],e[i]);
	}
	void query(int x,int &MAX) {
		while(~x) {
			SegmentTree::ask(1,1,CutTree::dfc,dfn[top[x]],dfn[x],MAX);
			x=fa[top[x]];
		}
		return ;
	}
}
namespace ACAM {
	int insert(const char* s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
			u=tr[u][s[i]-'a'];
		}
		bz[u]=1;
		return u;
	}
	void build() {
		queue<int> q;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				q.push(tr[0][i]);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			CutTree::insert(fail[u],u);
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
}
int query(const char* s) {
	int ret=-1,u=0;
	for(int i=0; s[i]; ++i) {
		u=ACAM::tr[u][s[i]-'a'];
		CutTree::query(u,ret);
	}
	return ret;
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i) {
		scanf("%s",s);
		p[i]=ACAM::insert(s);
		ACAM::st[p[i]].insert(0);
		a[i]=0;
	}
	ACAM::build();
	CutTree::dfs(0);
	CutTree::dfs2(0,0);
	CutTree::fa[0]=-1;
	SegmentTree::mktree(1,1,CutTree::dfc);
	for(i=1; i<=m; ++i) {
		static int op;
		scanf("%d",&op);
		if(op==1) {
			static int x,y;
			scanf("%d%d",&x,&y);
			multiset<int> &st=ACAM::st[p[x]];
			int premax=*st.rbegin();
			st.erase(st.find(a[x]));
			a[x]=y;
			st.insert(a[x]);
			if(premax!=*st.rbegin()) SegmentTree::change(1,1,CutTree::dfc,CutTree::dfn[p[x]],*st.rbegin());
		} else {
			scanf("%s",s);
			printf("%d\n",query(s));
		}
	}
	return 0;
}