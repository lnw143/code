#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N(5), P(998244353);
int n,m,a[N + 2],cent,minn,ans;
vector<int> e[N + 2];
int cnt(int u,int fa) {
	int maxn=0,sz=a[u];
	for(auto v : e[u])
		if(v!=fa) {
			int s=cnt(v,u);
			maxn=max(maxn,s);
			sz+=s;
		}
	maxn=max(maxn,m-sz);
	if(maxn<minn||minn==maxn&&u<cent)
		cent=u,minn=maxn;
	return sz;
}
void dfs(int u,int r) {
	if(u>n) {
		if(!r) {
			cent=0;
			minn=m+1;
			cnt(1,-1);
			ans=(ans+cent)%P;
		}
		return ;
	}
	for(int i=0; i<=r; ++i)
		a[u]=i,
		dfs(u+1,r-i);
}
int main() {
	freopen("milkyway.in","r",stdin);
	freopen("milkyway.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,m);
	printf("%d",ans);
	return 0;
}