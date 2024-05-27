#include<cstdio>
#include<vector>
#include<algorithm>
#include<functional>
#include<utility>
using namespace std;
using pII = pair<int,int>;
const int N = 1e4, M = N << 2, S = M << 2;
int n,m,x[N + 2],y[N + 2],b[M + 2];
pII a[M + 2];
namespace graph {
	vector<int> e[M + S + 2];
	int tot,len[M + S + 2],dfn[M + S + 2],low[M + S + 2],dfc,scc[M + S + 2],sc,stk[M + S + 2],tp;
	bool in_stk[M + S + 2];
	void insert(int x,int y) {
		e[x].push_back(y);
	}
	namespace segtree {
		int tr[S + 2];
		#define mid ((l+r)>>1)
		#define ls (x<<1)
		#define rs (ls|1)
		#define li ls,l,mid
		#define ri rs,mid+1,r
		void maketree(int x,int l,int r) {
			tr[x]=++tot;
			if(l==r) return insert(tr[x],a[l].second),void();
			maketree(li);
			maketree(ri);
			insert(tr[x],tr[ls]);
			insert(tr[x],tr[rs]);
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
	}
	void init() {
		tot=m;
		segtree::maketree(1,1,m);
		for(int i=1; i<=tot; ++i)
			len[i]=e[i].size();
	}
	void tarjan(int u) {
		if(dfn[u]) return ;
		low[u]=dfn[u]=++dfc;
		stk[++tp]=u;
		in_stk[u]=true;
		for(auto v : e[u])
			if(!dfn[v]) {
				tarjan(v);
				low[u]=min(low[u],low[v]);
			} else if(in_stk[v])
				low[u]=min(low[u],dfn[v]);
		if(low[u]==dfn[u]) {
			++sc;
			while(stk[tp]!=u) {
				scc[stk[tp]]=sc;
				in_stk[stk[tp]]=false;
				--tp;
			}
			scc[u]=sc;
			in_stk[u]=false;
			--tp;
		}
	}
	bool check(int lim) {
		for(int i=1; i<=tot; ++i)
			e[i].erase(e[i].begin()+len[i],e[i].end());
		for(int i=1; i<=m; ++i) {
			int l=upper_bound(b+1,b+m+1,b[i]-lim)-b,
				r=lower_bound(b+1,b+m+1,b[i]+lim)-b-1,
				u=a[i].second<=n?a[i].second+n:a[i].second-n;
			segtree::link(1,1,m,l,i-1,u);
			segtree::link(1,1,m,i+1,r,u);
		}
		for(int i=1; i<=tot; ++i)
			dfn[i]=low[i]=scc[i]=in_stk[i]=0;
		sc=dfc=0;
		for(int i=1; i<=tot; ++i)
			if(!dfn[i])	
				tarjan(i);
		for(int i=1; i<=n; ++i)
			if(scc[i]==scc[i+n])
				return false;
		return true;
	}
}
int solve() {
	int l=0,r=1e9,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(graph::check(mid)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
int main() {
	scanf("%d",&n);
	m=n*2;
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&x[i],&y[i]),
		a[i*2-1]=pII(x[i],i+n),
		a[i*2]=pII(y[i],i);
	sort(a+1,a+m+1);
	for(int i=1; i<=m; ++i)
		b[i]=a[i].first;
	graph::init();
	printf("%d",solve());
	return 0;
}