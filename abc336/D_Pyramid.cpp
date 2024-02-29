#include<atcoder/all>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace atcoder;
using namespace std;
const int N = 2e5;
int n,a[N + 2],b[N + 2],c[N + 2],i,ans;
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	b[1]=1;
	for(i=2; i<=n; ++i)
		b[i]=a[i]>b[i-1]?b[i-1]+1:a[i];
	c[n]=1;
	for(i=n-1; i>=1; --i)
		c[i]=a[i]>c[i+1]?c[i+1]+1:a[i];
	for(i=1; i<=n; ++i)
		ans=max(ans,min(b[i],c[i]));
	printf("%d",ans);
	return 0;
}