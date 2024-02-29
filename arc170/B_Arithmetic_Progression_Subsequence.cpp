#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5;
int n,i,j,a[N + 2],p[N + 2];
long long ans;
struct Temp {
	int x[12];
} u[N + 2],v[N + 2];
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		p[i]=n+1;
		scanf("%d",&a[i]);
		u[i]=u[i-1];
		u[i].x[a[i]]=i;
	}
	p[n+1]=n+1;
	for(i=n; i>=1; --i) {
		v[i]=v[i+1];
		v[i].x[a[i]]=i;
	}
	for(i=2; i<n; ++i)
		for(j=max(1,2*a[i]-10); j<=10&&j<2*a[i]; ++j)
			if(u[i-1].x[j]&&v[i+1].x[2*a[i]-j])
				p[u[i-1].x[j]]=min(p[u[i-1].x[j]],v[i+1].x[2*a[i]-j]);
	for(i=n; i>=1; --i) {
		p[i]=min(p[i+1],p[i]);
		ans+=n-p[i]+1;
	}
	printf("%lld",ans);
	return 0;
}