#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e3 + 2, M = 8 + 2;
int n,m=8,i,j,x[N][M],sumx[N],ans[N];
double diff[M],sumy[N],avg[M];
template<typename T>T abs(T x) {
	return x<0?-x:x;
}
bool cmp(int x,int y) {
	if(sumy[x]!=sumy[y]) return sumy[x]>sumy[y];
	if(sumx[x]!=sumx[y]) return sumx[x]>sumx[y];
	return x<y;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j) {
			scanf("%d",&x[i][j]);
			sumx[i]+=x[i][j];
			avg[j]+=x[i][j];
		}
	for(i=1; i<=m; ++i) {
		avg[i]/=n;
		for(j=1; j<=n; ++j)
			diff[i]+=abs(x[j][i]-avg[i]);
	}
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j)
			if(diff[j]!=0)
				sumy[i]+=(j<=3?1:0.8)*(x[i][j]-avg[j])*n/diff[j];
	for(i=1; i<=n; ++i)
		ans[i]=i;
	stable_sort(ans+1,ans+n+1,cmp);
	for(i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}