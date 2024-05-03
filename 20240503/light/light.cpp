#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
using ll = long long;
constexpr int N = 5e6;
constexpr ll inf = 1ll << 60;
int T,n,k,p[N + 2],q[N + 2];
ll f[N + 2];
char s[N + 5];
int main() {
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%s",&n,&k,s+1);
		if(k==0) {
			printf("%lld\n",(n+1ll)*n/2);
			continue;
		}
		for(int i=1,h=1,t=0; i<=n; ++i) {
			if(s[i]=='1') q[++t]=i;
			while(h<=t&&q[h]+k<i) ++h;
			if(h<=t) p[i]=q[h];
			else p[i]=-1;
		}
		q[1]=0;
		for(int i=1,h=1,t=1; i<=n; ++i) {
			if(p[i]==-1) f[i]=f[i-1]+i;
			else {
				while(q[h]<p[i]-k-1) ++h;
				f[i]=f[q[h]]+p[i];
			}
			while(h<=t&&f[q[t]]>=f[i]) --t;
			q[++t]=i;
		}
		printf("%lld\n",f[n]);
	}
	return 0;
}