#include<cstdio>
using namespace std;
using ll = long long;
const int N = 20;
int n,m,a[N + 2],s[N + 2];
char c;
ll fac[N + 2];
bool bz[N + 2];
int main() {
	scanf("%d%d",&n,&m);
	fac[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=fac[i-1]*i;
	for(int i=1; i<=m; ++i) {
		scanf("	%c",&c);
		if(c=='P') {
			ll x;
			scanf("%lld",&x);
			--x;
			for(int i=1; i<=n; ++i)
				a[i]=x/fac[n-i]%(n-i+1),bz[i]=false;
			for(int i=1; i<=n; ++i) {
				int s=a[i],p=-1;
				for(int j=1; j<=n; ++j)
					if(!bz[j]) {
						if(s==0) {
							p=j;
							break;
						}
						--s;
					}
				bz[p]=true;
				printf("%d ",p);
			}
			putchar('\n');
		} else {
			for(int i=1; i<=n; ++i)
				scanf("%d",&a[i]),s[i]=0;
			ll ans=1;
			for(int i=n; i>=1; --i) {
				for(int j=1; j<a[i]; ++j)
					ans+=s[j]*fac[n-i];
				++s[a[i]];
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}