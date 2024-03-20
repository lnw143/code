#include<cstdio>
#include<random>
#include<vector>
#include<utility>
#include<cassert>
#include<cstring>
const int N = 1e3;
using namespace std;
int n,m,ans,dis[N + 2][N + 2],deg[N + 2];
vector<int> node;
int main() {
	scanf("%d%d",&n,&m);
	memset(dis,0x3f,sizeof(dis));
	for(int i=1; i<=m; ++i)	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		dis[u][v]=min(dis[u][v],w);
		dis[v][u]=min(dis[v][u],w);
		++deg[u];
		++deg[v];
	}
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1; i<=n; ++i)
		if(deg[i]&1)
			node.push_back(i);
	assert(node.size()%2==0);
	
	return 0;
}