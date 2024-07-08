#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,m;
vector<int> e[N + 2];
ll a[N + 2],f[N + 2];
void dfs(int u,int p) {
	f[u]=0;
	for(auto v : e[u])
		if(v!=p) {
			dfs(v,u);
			f[u]+=f[v];
		}
	f[u]=max(f[u]-a[u],0ll);
}
int main() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	scanf("%d",&m);
	if(n*m<=1e7) {
		dfs(1,1);
		printf(f[1]?"No\n":"Yes\n");
		for(int i=1; i<=m; ++i) {
			int x,w;
			scanf("%d%d",&x,&w);
			a[x]+=w;
			dfs(1,1);
			printf(f[1]?"No\n":"Yes\n");
		}
	} else if(e[1].size()==n-1) {
		ll sum=0;
		for(int i=2; i<=n; ++i) sum+=max(0ll,-a[i]);
		printf(a[1]>=sum?"Yes\n":"No\n");
		for(int i=1; i<=m; ++i) {
			int x,w;
			scanf("%d%d",&x,&w);
			sum-=max(0ll,-a[x]);
			a[x]+=w;
			sum+=max(0ll,-a[x]);
			printf(a[1]>=sum?"Yes\n":"No\n");
		}
	}
	return 0;
}