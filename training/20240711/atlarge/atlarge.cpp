#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5, logN = 20;
int n,k,ans;
int dep[N + 2],anc[logN][N + 2];
int dfc,dfn[N + 2],low[N + 2];
bool vis[N + 2];
vector<int> e[N + 2];
void dfs(int u,int p) {
	dep[u]=dep[p]+1;
	dfn[u]=++dfc;
	anc[0][u]=p;
	for(int i=1; i<logN; ++i)
		anc[i][u]=anc[i-1][anc[i-1][u]];
	for(auto v : e[u])
		if(v!=p)
			dfs(v,u);
	low[u]=dfc;
}
int par(int u,int s) {
	for(int i=0; i<logN; ++i)
		if((s>>i)&1)
			u=anc[i][u];
	return u;
}
int main() {
	freopen("atlarge.in","r",stdin);
	freopen("atlarge.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(k,k);
	vector<int> leaf;
	for(int i=1; i<=n; ++i)
		if(e[i].size()==1)
			leaf.push_back(i);
	sort(leaf.begin(),leaf.end(),[](int x,int y) { return dep[x]<dep[y]; });
	for(auto u : leaf) {
		if(vis[dfn[u]]) continue;
		int v=par(u,dep[u]-dep[u]/2-1);
		for(int i=dfn[v]; i<=low[v]; ++i)
			vis[i]=true;
		++ans;
	}
	printf("%d",ans);
	return 0;
}