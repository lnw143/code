#include<cstdio>
#include<vector>
using namespace std;
using ll = long long;
const int N = 2e6, P = 1e9 + 7, P2 = (P + 1) / 2;
int n,i,fa[N + 2],f[N + 2],ans;
vector<int> e[N + 2];
void dfs(int x) {
	f[x]=1;
	for(int v : e[x]) {
		dfs(v);
		f[x]=(f[x]+(ll)f[v]*P2%P)%P;
		ans=(ans+f[v])%P;
	}
}
int main() {
	freopen("deconstruct.in","r",stdin);
	freopen("deconstruct.out","w",stdout);
	scanf("%d",&n);
	for(i=2; i<=n; ++i) {
		scanf("%d",&fa[i]);
		e[fa[i]].push_back(i);
	}
	dfs(1);
	printf("%d",ans);
	return 0;
}