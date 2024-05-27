#include<cstdio>
#include<utility>
#include<vector>
using namespace std;
template<typename T> using vec=vector<T>;
using ll = long long;
constexpr int N = 1e5;
int n,k,fa[N + 2],w[N + 2];
int dfc,dfn[N + 2],low[N + 2];
vec<int> e[N + 2];
vec<pair<int,int>> p[N + 2];
void dfs(int u) {
	dfn[u]=++dfc;
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
	p[low[u]].emplace_back(dfn[u],w[u]);
}
int main() {
	freopen("galo.in","r",stdin);
	freopen("galo.out","w",stdout);
	scanf("%d%d",&n,&k);
	k=min(n,k+1);
	vec<vec<ll>> f(n+1,vec<ll>(k+1,0));
	for(int i=2; i<=n; ++i)
		scanf("%d%d",&fa[i],&w[i]),e[fa[i]].emplace_back(i);
	dfs(1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=k; ++j) {
			f[i][j]=f[i-1][j];
			for(const auto &[u,v] : p[i])
				f[i][j]=max(f[i][j],f[u-1][j-1]+v);
		}
	printf("%lld",f[n][k]);
	return 0;
}