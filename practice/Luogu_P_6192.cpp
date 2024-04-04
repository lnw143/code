#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e2, M = 5e2, K = 10, S = 1 << K;
int n,m,k,w[N + 2],f[N + 2][S + 2];
vector<pair<int,int>> e[N + 2];
void dij(int s) {
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hp;
	for(int i=1; i<=n; ++i)
		hp.emplace(f[i][s],i);
	while(!hp.empty()) {
		const auto [d,u]=hp.top();
		hp.pop();
		if(f[u][s]!=d) continue;
		for(auto [v,w] : e[u])
			if(d+w<f[v][s]) {
				f[v][s]=d+w;
				hp.emplace(f[v][s],v);
			}
	}
	return ;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
	}
	for(int i=0; i<k; ++i) {
		int x;
		scanf("%d",&x);
		w[x]|=1<<i;
	}
	int s=1<<k;
	memset(f,0x3f,sizeof(f));
	for(int i=1; i<=n; ++i)
		f[i][w[i]]=0;
	for(int i=1; i<s; ++i) {
		for(int j=i; j; j=(j-1)&i)
			for(int k=1; k<=n; ++k)
				f[k][i]=min(f[k][i],f[k][j]+f[k][i^j]);
		dij(i);
	}
	int ans=1e9;
	for(int i=1; i<=n; ++i)
		ans=min(ans,f[i][s-1]);
	printf("%d",ans);
	return 0;
}