#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int N = 1e5, M = 1e2;
int T,n,m,q,x,y,k,ans;
vector<int> a;
vector<pair<int,int>> e[N + 2];
int solve(const vector<int>& a,int k) {
	static int cnt[M + 2];
	for(int i=0; i<m; ++i) cnt[i]=0;
	int sum=0,res=0;
	for(auto i : a) {
		++cnt[(sum+k)%m];
		sum=(sum+i)%m;
		res+=cnt[sum];
	}
	return res;
}
void dfs(int u,int fa) {
	if(u==y) ans=solve(a,k);
	for(auto [v,w] : e[u])
		if(v!=fa) {
			a.push_back(w);
			dfs(v,u);
			a.pop_back();
		}
}
int main() {
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1; i<n; ++i) {
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			e[u].emplace_back(v,w);
			e[v].emplace_back(u,w);
		}
		scanf("%d",&q);
		for(int i=1; i<=q; ++i) {
			scanf("%d%d%d",&x,&y,&k);
			dfs(x,x);
			printf("%d\n",ans);
		}
		for(int i=1; i<=n; ++i) e[i].clear();
	}
	return 0;
}