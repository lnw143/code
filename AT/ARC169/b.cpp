#include<cstdio>
using namespace std;
const int N = 2.5e5 + 2;
using ll = long long;
int n,i,j,a[N],nx[N];
ll s,sum,f[N],ans;
int main() {
	scanf("%d%lld",&n,&s);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	sum=a[1],j=1;
	for(i=1; i<=n; ++i) {
		while(j<=n&&sum<=s)
			sum+=a[++j];
		nx[i]=j;
		sum-=a[i];
	}
	for(i=n; i>=1; --i) {
		f[i]=n-i+1+f[nx[i]];
		ans+=f[i];
	}
	printf("%lld",ans);
	return 0;
}