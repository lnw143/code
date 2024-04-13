#include<cstdio>
using namespace std;
const int N = 1e6, inf = 1 << 30;
int n,m,k,a[N + 2],b[N + 2],t[N * 2 + 2],p[N * 2 + 2],ans;
int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=1; i<=m; ++i)
		scanf("%d",&b[i]);
	for(int i=1; i<m; ++i)
		t[i]=b[i]-b[i+1];
	t[m]=inf;
	for(int i=1; i<n; ++i)
		t[m+i]=a[i]-a[i+1];
	k=n+m-1;
	for(int i=2; i<=k; ++i) {
		int j=p[i-1];
		while(j&&t[j+1]!=t[i]) j=p[j];
		if(t[j+1]==t[i]) ++j;
		p[i]=j;
		if(p[i]==m-1) ++ans;
	}
	printf("%d",ans);
	return 0;
}