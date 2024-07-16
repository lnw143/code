#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e6;
int n,dep[N + 2],hson[N + 2],ans[N + 2];
vector<int> e[N + 2],f[N + 2];
void dfs(int u,int p) {
	for(auto v : e[u])
		if(v!=p) {
			dfs(v,u);
			if(dep[v]>dep[hson[u]]) hson[u]=v;
		}
	dep[u]=dep[hson[u]]+1;
}
void dp(int u,int p) {
	if(hson[u]) {
		dp(hson[u],u);
		swap(f[u],f[hson[u]]);
		ans[u]=ans[hson[u]];
		f[u].push_back(1);
		if(f[u][ans[u]]==1) ans[u]=dep[u];
		for(auto v : e[u])
			if(v!=hson[u]&&v!=p) {
				dp(v,u);
				for(int i=1; i<=dep[v]; ++i) {
					int j=i+dep[u]-1-dep[v];
					f[u][j]+=f[v][i];
					if(f[u][j]>f[u][ans[u]]||(f[u][j]==f[u][ans[u]]&&j>ans[u])) ans[u]=j;
				}
			}
	} else {
		f[u].resize(2);
		f[u][1]=1;
		ans[u]=1;
	}
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
	dp(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",dep[i]-ans[i]);
	return 0;
}