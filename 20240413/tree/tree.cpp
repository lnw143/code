#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 5e5;
int n,c[N + 2];
vector<int> e[N + 2],ans;
void dfs(int u,int p,int s) {
	if(s!=c[u]) s^=1,ans.emplace_back(u);
	for(auto v : e[u])
		if(v!=p)
			dfs(v,u,s);
}
int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&c[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,1,0);
	sort(ans.begin(),ans.end());
	for(auto i : ans)
		printf("%d ",i);
	return 0;
}