#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,p[N + 2],q[N + 2],h[N + 2];
vector<int> pos[N + 2];
bool vis[N + 2];
int dfs(int u,int p[]) {
	return vis[u]?0:(vis[u]=true,dfs(p[u],p)+1);
}
void put(int u,int v,int l) {
	while(l--) {
		h[q[v]]=p[u];
		u=p[u],v=q[v];
	}
}
int main() {
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&q[i]);
	memset(vis,0,sizeof(vis));
	for(int i=1; i<=n; ++i)
		if(!vis[i])
			pos[dfs(i,p)].push_back(i);
	memset(vis,0,sizeof(vis));
	for(int i=1; i<=n; ++i)
		if(!vis[i]) {
			int l=dfs(i,q);
			if(pos[l].empty()) return printf("NO\n"),0;
			int j=pos[l].back();
			pos[l].pop_back();
			put(j,i,l);
		}
	printf("YES\n");
	for(int i=1; i<=n; ++i)
		printf("%d ",h[i]);
	return 0;
}