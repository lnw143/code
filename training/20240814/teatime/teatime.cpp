#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 2e6;
int n,a[N + 2],v[N + 2],cnt;
bool bz[N + 2];
long long ans,s[N + 2];
int main() {
	freopen("teatime.in","r",stdin);
	freopen("teatime.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<n; ++i) scanf("%d",&a[i]);
	for(int i=1; i*2<n; ++i) {
		if(bz[i]) continue;
		cnt=0;
		int u=i;
		do {
			bz[u]=bz[n-u]=true;
			v[++cnt]=a[u]-a[n-u];
			u=u*2%n;
		} while(u!=i);
		for(int i=1; i<=cnt; ++i) s[i]=s[i-1]+v[i];
		nth_element(s+1,s+(cnt+1)/2,s+cnt+1);
		for(int i=1; i<=cnt; ++i) ans+=abs(s[(cnt+1)/2]-s[i]);
	}
	printf("%lld",ans);
	return 0;
}