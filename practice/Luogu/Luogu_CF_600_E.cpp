#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,c[N + 2],fa[N + 2],wson[N + 2],sz[N + 2],dfc,dfn[N + 2],low[N + 2],pos[N + 2];
vector<int> e[N + 2];
void dfs(int u) {
	sz[u]=1;
	dfn[u]=++dfc;
	pos[dfc]=u;
	for(auto v : e[u])
		if(v!=fa[u]) {
			fa[v]=u;
			dfs(v);
			sz[u]+=sz[v];
			if(sz[v]>sz[wson[u]]) wson[u]=v;
		}
	low[u]=dfc;
}
set<int> st[N + 2];
int cnt[N + 2],maxn;
long long ans[N + 2],sum[N + 2];
void put(int u,int v) {
	st[cnt[u]].erase(u);
	sum[cnt[u]]-=u;
	cnt[u]+=v;
	st[cnt[u]].insert(u);
	sum[cnt[u]]+=u;
	if(maxn<n&&!st[maxn+1].empty()) ++maxn;
	else if(st[maxn].empty()) --maxn;
}
void solve(int u,bool keep) {
	for(auto v : e[u])
		if(v!=fa[u]&&v!=wson[u])
			solve(v,false);
	if(wson[u]) solve(wson[u],true);
	put(c[u],1);
	for(auto v : e[u])
		if(v!=fa[u]&&v!=wson[u])	
			for(int i=dfn[v]; i<=low[v]; ++i)
				put(c[pos[i]],1);
	ans[u]=sum[maxn];
	if(!keep)
		for(int i=dfn[u]; i<=low[u]; ++i)
			put(c[pos[i]],-1);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&c[i]);
	for(int i=1; i<=n; ++i) {
		sum[0]+=i;
		st[0].insert(c[i]);
	}
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1);
	solve(1,true);
	for(int i=1; i<=n; ++i)
		printf("%lld ",ans[i]);
	return 0;
}