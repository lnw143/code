#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
const int N = 400, K = 20, S = 1 << K;
int n,cnt,k,l[N + 5],r[N + 5],dep[N + 5];
bool f[N + 2][S + 2];
vector<int> e[N + 5];
vector<pair<int,int>> v[N + 5];
void dfs(int u,int p) {
	if(dep[u]==k) {
		l[u]=r[u]=++cnt;
		v[cnt].push_back({k-1,cnt});
		return ;
	}
	l[u]=n+1,r[u]=0;
	for(auto v : e[u])
		if(v!=p) {
			dep[v]=dep[u]+1;
			dfs(v,u);
			l[u]=min(l[u],l[v]);
			r[u]=max(r[u],r[v]);
		}
	if(u>1&&l[u]<=r[u]) v[r[u]].push_back({dep[u]-1,l[u]});
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(k>K) {
		printf("DA\n");
		return 0;
	}
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	f[0][0]=true;
	for(int i=1; i<=cnt; ++i)
		for(auto [s,p] : v[i])
			for(int j=0; j<(1<<k); ++j)
				if(j&(1<<s))
					f[i][j]|=f[p-1][j^(1<<s)];
	bool ans=false;
	for(int i=0; i<(1<<k); ++i) ans|=f[cnt][i];
	printf(ans?"DA\n":"NE\n");
	return 0;
}