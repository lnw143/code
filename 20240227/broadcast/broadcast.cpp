#include<cstdio>
#include<set>
#include<queue>
#include<cctype>
#include<vector>
#include<algorithm>
#include<map>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(1e6), inf(1<<30);
int n,x[N + 2],d[N + 2],l[N + 2],r[N + 2];
int findl(int u) {
	int l=1,r=n,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(x[mid]>=u) r=mid-1;
		else l=mid+1;
	}
	return r+1;
}
int findr(int u) {
	int l=1,r=n,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(x[mid]<=u) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
namespace segtree_graph {
	const int S((N << 2)+ 2);
	vector<int> e[S];
	int tr[S],tot;
	#define mid ((l+r)>>1)
	#define ls (x<<1)
	#define rs (ls|1)
	#define li ls,l,mid
	#define ri rs,mid+1,r
	void insert(int x,int y) {
		e[x].push_back(y);
	}
	void maketree(int x,int l,int r) {
		if(l==r) {
			tr[x]=l;
			return ;
		}
		tr[x]=++tot;
		maketree(li);
		maketree(ri);
		insert(tr[x],tr[ls]);
		insert(tr[x],tr[rs]);
		return ;
	}
	void link(int x,int l,int r,int L,int R,int u) {
		if(r<L||R<l) return ;
		if(L<=l&&r<=R) {
			insert(u,tr[x]);
			return ;
		}
		link(li,L,R,u);
		link(ri,L,R,u);
	}
	#undef mid
	#undef ls
	#undef rs
	#undef li
	#undef ri
};
namespace SCC {
	using namespace segtree_graph;
	int stk[S],tp,dfn[S],low[S],dfc,scc[S],cnt,deg[S];
	bool in_stk[S],nos[S];
	vector<int> es[S];
	void tarjan(int u) {
		if(dfn[u]) return ;
		low[u]=dfn[u]=++dfc;
		in_stk[u]=true;
		stk[++tp]=u;
		for(int v : e[u])
			if(!dfn[v])	{
				tarjan(v);
				low[u]=min(low[u],low[v]);
			} else if(in_stk[v])
				low[u]=min(low[u],dfn[v]);
		if(low[u]==dfn[u]) {
			++cnt;
			while(stk[tp]!=u)
				nos[cnt]|=stk[tp]<=n,
				in_stk[stk[tp]]=false,
				scc[stk[tp--]]=cnt;
			nos[cnt]|=u<=n;
			in_stk[u]=false;
			scc[u]=cnt;
			--tp;
		}
	}
	int Ans1() {
		rep(i,1,tot)
			for(auto j : e[i])
				if(scc[j]!=scc[i]&&scc[i]&&scc[j])
					es[scc[i]].push_back(scc[j]),++deg[scc[j]];
		queue<int> q;
		rep(i,1,cnt)
			if(deg[i]==0)
				q.push(i);
		int ans=0;
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			if(nos[u]) ++ans;
			else {
				for(int v : es[u])
					if(--deg[v]==0)
						q.push(v);
			}
		}
		return ans;
	}
	int Ans2() {
		set<int> st;
		for(int i=1; i<=n; ++i)
			st.insert(scc[i]);
		return st.size();
	}
}
inline char gc() {
	const int BUF = 1<<20;
	static char ch[BUF], *l, *r;
	return (l == r && (r = (l = ch) + fread(ch, 1, BUF, stdin), l == r)) ? EOF : *l++;
}
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
int main() {
    freopen("broadcast.in","r",stdin);
    freopen("broadcast.out","w",stdout);
    read(n);
    rep(i,1,n)
        read(x[i]),read(d[i]);
	segtree_graph::tot=n;
	segtree_graph::maketree(1,1,n);
	rep(i,1,n)
		segtree_graph::link(1,1,n,findl(x[i]-d[i]),findr(x[i]+d[i]),i);
	rep(i,1,n)
		SCC::tarjan(i);
    printf("%d\n%d",SCC::Ans1(),SCC::Ans2());
    return 0;
}