#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cctype>
using namespace std;
const int N = 20, M = N * N, inf = 1 << 30;
const vector<pair<int,int>> way{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n,m,cost[N + 2][N + 2],bene[N + 2][N + 2],sum;
int a[N + 2][N + 2],b[N + 2][N + 2];
namespace netflow {
	const int K = M * 2 + 100;
	int tot,dep[K],cur[K];
	inline int newnode() {
		return ++tot;
	}
	int S=newnode(),T=newnode();
	struct edge {
		int v,w,id;
	};
	vector<edge> e[K];
	void insert(int u,int v,int w) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back({v,w,vid});
		e[v].push_back({u,0,uid});
	}
	bool bfs() {
		memset(dep,-1,sizeof(dep));
		queue<int> Q;
		dep[S]=0;
		Q.push(S);
		while(Q.size()) {
			int u=Q.front();
			Q.pop();
			cur[u]=0;
			for(auto [v,w,id] : e[u])
				if(dep[v]==-1&&w) {
					dep[v]=dep[u]+1;
					Q.push(v);
				}
		}
		return ~dep[T];
	}
	int dfs(int u,int f) {
		if(u==T) return f;
		int rem=f;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,id]=e[u][i];
			if(dep[v]!=dep[u]+1||!w) continue;
			int r=dfs(v,min(w,rem));
			rem-=r;
			w-=r;
			e[v][id].w+=r;
			if(!rem) break;
		}
		return f-rem;
	}
}
int read() {
	static char c;
	scanf(" %c",&c);
	return isdigit(c)?c-'0':islower(c)?c-'a'+10:c-'A'+36;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			cost[i][j]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			sum+=bene[i][j]=read();
	using namespace netflow;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			a[i][j]=newnode(),
			b[i][j]=newnode();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if((i+j)%2) {
				insert(S,a[i][j],cost[i][j]);
				insert(a[i][j],b[i][j],bene[i][j]);
				for(auto [u,v] : way) {
					int x=u+i,y=v+j;
					if(x<1||x>n||y<1||y>m) continue;
					insert(a[i][j],a[x][y],inf);
					insert(b[i][j],b[x][y],inf);
				}
			} else {
				insert(a[i][j],b[i][j],bene[i][j]);
				insert(b[i][j],T,cost[i][j]);
			}
	while(bfs()) sum-=dfs(S,inf);
	printf("%d",sum);
	return 0;
}