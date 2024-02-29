#include<cstdio>
#include<bitset>
using namespace std;
const int N = 35;
int n,m,i,cnt,ans;
bitset<N + 2> a[N + 2],d;
int Gauss() {
	int cnt=0;
	for(int i=1; i<=n; ++i) {
		int y=0;
		for(int j=cnt+1; j<=n; ++j)
			if(a[j][i]) {
				y=j;
				break;
			}
		if(!y) continue;
		++cnt;
		if(cnt!=y) swap(a[y],a[cnt]);
		for(int j=1; j<=n; ++j)
			if(cnt!=j&&a[j][i])
				a[j]^=a[cnt];
	}
	return cnt;
}
void dfs(int x) {
	if(d.count()>ans) return ;
	if(x>n) {
		int sum=d.count();
		for(int i=1; i<=cnt; ++i)
			sum+=(a[i]&d).count()&1^a[i][0];
		ans=min(ans,sum);
		return ;
	}
	d[x]=0;
	dfs(x+1);
	d[x]=1;
	dfs(x+1);
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		static int x,y;
		scanf("%d%d",&x,&y);
		a[x][y]=a[y][x]=1;
	}
	for(i=1; i<=n; ++i)
		a[i][0]=a[i][i]=1;
	cnt=Gauss();
	if(cnt<n) {
		ans=1e9;
		dfs(cnt+1);
	} else
		for(int i=1; i<=n; ++i)
			ans+=a[i][0];
	printf("%d",ans);
	return 0;
}