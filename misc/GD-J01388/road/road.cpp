#include<cstdio>
using namespace std;
const int N = 1e5 + 2;
int n,d,i,v[N],a[N],p[N],cnt,minn=1e6;
long long s[N],dis,buy,now,cost;
int main() {
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%d%d",&n,&d);
	for(i=1; i<n; ++i) {
		scanf("%d",&v[i]);
		s[i+1]=s[i]+v[i];
	}
	for(i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		if(a[i]<minn) {
			p[++cnt]=i;
			minn=a[i];
		}
	}
	if(p[cnt]!=n) p[++cnt]=n;
	for(i=1; i<cnt; ++i) {
		dis=s[p[i+1]]-s[p[i]];
		if(now>=dis) {
			now-=dis;
			continue;
		}
		buy=(dis-now+d-1)/d;
		cost+=buy*a[p[i]];
		now+=buy*d-dis;
	}
	printf("%lld",cost);
	return 0;
}
