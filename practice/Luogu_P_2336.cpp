#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
using vI = vector<int>;
const int N(5e4), M(1e5);
int n,m,q[M + 2];
vI p[N + 2];
namespace acam {
	const int S(2e5), logS(20);
	map<int,int> ch[S + 2];
	vector<int> e[S + 2];
	int tot,fail[S + 2],dep[S + 2],anc[S + 2][logS],dfn[S + 2],low[S + 2],dfc;
	namespace fenwick {
		int tr[S + 2];
		void add(int x,int f) {
			while(x<=dfc) {
				tr[x]+=f;
				x+=x&(-x);
			}
		}
		void add(int l,int r,int f) {
			add(l,f);
			add(r+1,-f);
		}
		int query(int x) {
			int r=0;
			while(x) {
				r+=tr[x];
				x&=x-1;
			}
			return r;
		}
		int query(int l,int r) {
			return query(r)-query(l-1);
		}
	}
	int getFail(int u,int c) {
		if(ch[u].count(c)) return ch[u][c];
		if(!u) return 0;
		return ch[u][c]=getFail(fail[u],c);
	}
	vI insert(vI x) {
		int u=0;
		vI p{0};
		for(auto i : x) {
			if(!ch[u].count(i))
				ch[u][i]=++tot;
			p.push_back(u=ch[u][i]);
		}
		return p;
	}
	void dfs(int u) {
		dfn[u]=++dfc;
		for(auto v : e[u])
			dfs(v);
		low[u]=dfc;
	}
	void build() {
		queue<int> q;
		for(auto [w,v] : ch[0])
			q.push(v);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			e[fail[u]].push_back(u);
			anc[u][0]=fail[u];
			dep[u]=dep[fail[u]]+1;
			for(int i=1; i<logS; ++i)
				anc[u][i]=anc[anc[u][i-1]][i-1];
			for(auto [w,v] : ch[u]) {
				fail[v]=getFail(fail[u],w);
				q.push(v);
			}
		}
		dfs(0);
	}
	int lca(int u,int v) {
		if(dep[u]<dep[v]) swap(u,v);
		for(int i=logS-1; i>=0; --i)
			if(dep[anc[u][i]]>=dep[v])
				u=anc[u][i];
		if(u==v) return u;
		for(int i=logS-1; i>=0; --i)
			if(anc[u][i]!=anc[v][i])
				u=anc[u][i],v=anc[v][i];
		return anc[u][0];
	}
}
vI read() {
	vI a;
	int k;
	scanf("%d",&k);
	a.resize(k);
	for(int &i : a)
		scanf("%d",&i);
	return a;
}
void mark(vI p) {
	using namespace acam;
	sort(p.begin(),p.end(),[](int x,int y){ return dfn[x]<dfn[y]; });
	for(auto u : p)
		fenwick::add(dfn[u],1);
	for(int i=0; i<p.size()-1; ++i)
		fenwick::add(dfn[lca(p[i],p[i+1])],-1);
}
int ask(vI p) {
	using namespace acam;
	sort(p.begin(),p.end(),[](int x,int y){ return dfn[x]<dfn[y]; });
	int ans=0;
	for(auto u : p)
		ans+=fenwick::query(dfn[u]);
	for(int i=0; i<p.size()-1; ++i)
		ans-=fenwick::query(dfn[lca(p[i],p[i+1])]);
	return ans;
}
int main() {
	using namespace acam;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) {
		vI a=read(),b=read();
		a.push_back(1e4+1);
		a.insert(a.end(),b.begin(),b.end());
		p[i]=insert(a);
	}
	for(int i=1; i<=m; ++i)
		q[i]=insert(read()).back();
	build();
	for(int i=1; i<=n; ++i)
		mark(p[i]);
	for(int i=1; i<=m; ++i)
		printf("%d\n",fenwick::query(dfn[q[i]],low[q[i]]));
	for(int i=1; i<=dfc; ++i)
		fenwick::tr[i]=0;
	for(int i=1; i<=m; ++i)
		fenwick::add(dfn[q[i]],low[q[i]],1);
	for(int i=1; i<=n; ++i)
		printf("%d ",ask(p[i]));
	return 0;
}