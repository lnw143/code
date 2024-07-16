#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5, K = 2e5, P = 1e9 + 7;
int n,m,k,a[N + 2],s[N + 2],p[K + 2];
int cnt[N + 2],d[N + 2],tot,ans;
void add(int x) {
	tot+=(m-1)/k;

}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		s[i]=(s[i-1]+a[i])%k;
	}
	for(int i=1; i<=n; ++i) {
		++cnt[s[i-1]];
		(ans+=cnt[s[i]])%=P;//-cnt[(s[i]+1ll*s[n]*m)%k]
	}
	memset(cnt,0,sizeof(*cnt)*k);
	if(s[n]==0) {
		for(int i=n-1; i>=1; --i) {
			(ans+=cnt[s[i]])%=P;
			++cnt[s[i]];
		}
		memset(cnt,0,sizeof(*cnt)*k);
		for(int i=0; i<n; ++i) ++cnt[s[i]];
		for(int i=1; i<=n; ++i) (ans+=cnt[s[i]]*(m-1ll)%P)%=P;
	} else {
		for(int i=1,sum=0; i<=k; ++i,(sum+=s[n])%=k) p[sum]=i;
		
	}
	printf("%lld",(1ll*ans*m%P-(m-1)+P)%P);
	return 0;
}