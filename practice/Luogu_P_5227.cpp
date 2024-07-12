#include <cstdio>
#include <chrono>
#include <random>
using namespace std;
const int N = 1e5, M = 2e5, C = 4;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n,m,k,q[C + 2];
unsigned int w[M + 2];
struct edge {
	int v,id;
};
vector<edge> e[N + 2];
bool vis[N + 2],vie[M + 2];
void dfs(int u,int p) {
	vis[u]=true;
	for(auto [v,id] : e[u]) {
		if(vis[v]) {
			if(!vie[id]) {
				w[id]=rnd();
				vie[id]=true;
			}
		} else {
			vie[id]=true;
			dfs(v,id);
		}
		if(id!=p) w[p]^=w[id];
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back({v,i});
		e[v].push_back({u,i});
	}
	dfs(1,0);
	scanf("%d",&k);
	for(int i=1; i<=k; ++i) {
		int c;
		scanf("%d",&c);
		for(int j=0; j<c; ++j)
			scanf("%d",&q[j]);
		bool f=false;
		for(int j=1; j<(1<<c); ++j) {
			unsigned int s=0;
			for(int p=0; p<c; ++p)
				if((j>>p)&1)
					s^=w[q[p]];
			if(s==0) {
				f=true;
				break;
			}
		}
		printf(f?"Disconnected\n":"Connected\n");
	}
	return 0;
}