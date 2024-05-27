#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e5 + 2;
int n,i,t[N],x[N],ls[N],pr[N],a[N],ans;
bool bz[N];
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",&t[i],&x[i]);
		if(t[i]==1) {
			pr[i]=ls[x[i]];
			ls[x[i]]=i;
		}
	}
	for(i=n; i>=1; --i)
		if(t[i]==2) {
			while(ls[x[i]]>i) ls[x[i]]=pr[ls[x[i]]];
			if(!ls[x[i]]) {
				printf("-1");
				return 0;
			}
			bz[ls[x[i]]]=true;
			++a[ls[x[i]]],--a[i+1];
			ls[x[i]]=pr[ls[x[i]]];
		}
	for(i=1; i<=n; ++i)
		ans=max(ans,a[i]+=a[i-1]);
	printf("%d\n",ans);
	for(i=1; i<=n; ++i)
		if(t[i]==1)
			printf("%d ",bz[i]);
	return 0;
}