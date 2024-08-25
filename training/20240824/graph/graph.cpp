#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
inline char gc() {
	static char *l,*r,buf[1<<16];
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c&15);
	return x;
}
char pbuf[1<<16],*pp=pbuf;
inline void pc(char c) {
	*pp++=c;
	if(pp-pbuf==1<<16) fwrite(pbuf,1,1<<16,stdout),pp=pbuf;
}
inline void write(long long x) {
	static char stk[1<<7];
	char *tp=stk;
	do *tp++=x%10; while(x/=10);
	while(tp!=stk) pc((*--tp)|48);
}
using namespace std;
using ll = long long;
const int N = 1e5, M = 3e5;
int n,m;
struct edge {
	int u,v;
} eg[M + 2];
ll ans[M + 2];
namespace pdsu {
	int fa[N + 2],sz[N + 2];
	ll cur;
	void init() {
		for(int i=1; i<=n; ++i) fa[i]=i,sz[i]=1;
	}
	int find(int u) {
		return fa[u]==u?u:find(fa[u]);
	}
	vector<pair<int,int>> fp,sp;
	vector<ll> cp;
	void merge(int u,int v) {
		u=find(u),v=find(v);
		if(u==v) return ;
		if(sz[u]<sz[v]) swap(u,v);
		fp.emplace_back(v,fa[v]);
		fa[v]=u;
		cp.emplace_back(cur);
		cur+=(ll)sz[u]*sz[v];
		sp.emplace_back(u,sz[u]);
		sz[u]+=sz[v];
	}
	int now() {
		return cp.size();
	}
	void undo(int limit) {
		while(now()>limit) {
			fa[fp.back().first]=fp.back().second;
			fp.pop_back();
			sz[sp.back().first]=sp.back().second;
			sp.pop_back();
			cur=cp.back();
			cp.pop_back();
		}
	}
}
namespace tarjan {
	int dfn[N + 2],low[N + 2],dfc;
	int stk[N + 2],tp;
	int scc[N + 2],scnt;
	bool in_stk[N + 2];
	vector<int> e[N + 2];
	void dfs(int u) {
		dfn[u]=low[u]=++dfc;
		in_stk[u]=true;
		stk[++tp]=u;
		for(auto v : e[u])
			if(!dfn[v]) {
				dfs(v);
				low[u]=min(low[u],low[v]);
			} else if(in_stk[v])
				low[u]=min(low[u],dfn[v]);
		if(dfn[u]==low[u]) {
			++scnt;
			while(true) {
				int v=stk[tp];
				--tp;
				scc[v]=scnt;
				in_stk[v]=false;
				if(v==u) break;
			}
		}
	}
	void solve(const vector<int> Node) {
		for(auto i : Node) {
			i=pdsu::find(i);
			if(!dfn[i])
				dfs(i);
		}
	}
	void addEdge(const vector<int>& E) {
		for(auto i : E) {
			auto [u,v]=eg[i];
			u=pdsu::find(u);
			v=pdsu::find(v);
			if(u==v) continue;
			e[u].push_back(v);
		}
	}
	void clean(const vector<int>& V) {
		for(auto i : V) {
			e[i].clear(),
			dfn[i]=low[i]=scc[i]=0;
		}
		scnt=dfc=0;
	}
}
void solve(const int l,const int r,const vector<int>& E) {
	if(l>r) return ;
	const int mid=(l+r)/2;
	vector<int> t,node,El,Er;
	for(auto i : E)
		if(i<=mid)
			t.push_back(i),
			node.push_back(pdsu::find(eg[i].u)),
			node.push_back(pdsu::find(eg[i].v));
		else
			Er.push_back(i);
	tarjan::addEdge(t);
	tarjan::solve(node);
	const int past = pdsu::now();
	for(auto i : t)
		if(tarjan::scc[pdsu::find(eg[i].u)]==tarjan::scc[pdsu::find(eg[i].v)]) {
			pdsu::merge(eg[i].u,eg[i].v);
			El.push_back(i);
		} else
			Er.push_back(i);
	tarjan::clean(node);
	ans[mid]=pdsu::cur;
	solve(mid+1,r,Er);
	pdsu::undo(past);
	solve(l,mid-1,El);
}
int main() {
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read(),m=read();
	for(int i=1; i<=m; ++i) eg[i].u=read(),eg[i].v=read();
	pdsu::init();
	vector<int> E;
	for(int i=1; i<=m; ++i) E.push_back(i);
	solve(1,m,E);
	for(int i=1; i<=m; ++i)	
		write(ans[i]),pc('\n');
	fwrite(pbuf,1,pp-pbuf,stdout);
	return 0;
}