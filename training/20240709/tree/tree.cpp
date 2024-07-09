#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5;
int n,m,fa[N + 2],g[N + 2];
struct edge {
	int v,w;
};
vector<edge> e[N + 2];
void dfs(int u,int p) {
	fa[u]=p;
	for(auto [v,w] : e[u])
		if(v!=p) {
			g[v]=w;
			dfs(v,u);
		}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs(1,1);
	for(int i=1; i<=n; ++i) {
		int 
	}
	return 0;
}