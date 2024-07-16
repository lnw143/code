#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5;
int n,depx;
vector<int> e[N + 2];
int siz[N + 2],wson[N + 2],dep[N + 2],dfc,dfn[N + 2],low[N + 2],pos[N + 2],top[N + 2];
int query_dis(int u) {
	printf("d %d\n",u);
	fflush(stdout);
	int d;
	scanf("%d",&d);
	return d;
}
int query_nxt(int u) {
	printf("s %d\n",u);
	fflush(stdout);
	int v;
	scanf("%d",&v);
	return v;
}
void dfs(int u,int p) {
	siz[u]=1;
	dep[u]=dep[p]+1;
	for(auto v : e[u])
		if(v!=p) {
			dfs(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[wson[u]]) wson[u]=v;
		}
}
int dfs2(int u,int p,int Top) {
	top[u]=Top;
	pos[dfn[u]=++dfc]=u;
	if(wson[u]) low[u]=dfs2(wson[u],u,Top);
	else low[u]=dfn[u];
	for(auto v : e[u])
		if(v!=p&&v!=wson[u])
			dfs2(v,u,v);
	return low[u];
}
void solve(int u) {
	u=query_nxt(u);
	int bot=pos[low[u]],dis=query_dis(bot),depl=(depx+dep[bot]-dis)/2,lca=pos[low[u]-(dep[bot]-depl)];
	if(depl==depx) {
		printf("! %d\n",lca);
		fflush(stdout);
		return ;
	}
	solve(lca);
	return ;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	dfs2(1,1,1);
	depx=query_dis(1)+1;
	if(depx==1) {
		printf("! 1\n");
		fflush(stdout);
		return 0;
	}
	solve(1);
	return 0;
}