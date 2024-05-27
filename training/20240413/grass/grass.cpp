#include<cstdio>
#include<utility>
#include<algorithm>
#include<functional>
using namespace std;
using ll = long long;
const int N = 3e5;
const ll inf = 1ll << 60;
int n,m,t,ans1,p[N + 2],q[N + 2],g[N + 2],h[N + 2];
ll f[N + 2],s[N + 2];
#define l(x) a[x].first
#define r(x) a[x].second
pair<int,int> a[N + 2];
ll cost(int l,int r,int x) {
	ll sz=q[r]-q[l-1],sum=s[r]-s[l-1];
	if(l==x) return sum-x*sz;
	return x*sz-sum;
}
int main() {
	freopen("grass.in","r",stdin);
	freopen("grass.out","w",stdout);
	scanf("%d%d",&n,&t);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&l(i),&r(i)),m=max(m,r(i));
	sort(a+1,a+n+1,greater<pair<int,int>>());
	for(int i=1; i<=m; ++i) f[i]=inf;
	for(int i=1; i<=n; ++i) {
		int pos=l(i)+r(i)>>1;
		++p[pos];
	}
	for(int i=1; i<=m; ++i)
		q[i]=q[i-1]+p[i],s[i]=s[i-1]+(ll)p[i]*i;
	for(int i=1; i<=n; ++i) g[r(i)+1]=max(g[r(i)+1],l(i));
	for(int i=1; i<=m+1; ++i) g[i]=max(g[i],g[i-1]),h[i]=1e9;
	for(int i=1; i<=m; ++i)
		for(int j=g[i]; j<i; ++j) {
			if(h[j]>=h[i]) continue;
			int mid=j+i>>1;
			if(h[i]==h[j]+1) f[i]=min(f[i],f[j]+cost(j,mid,j)+cost(mid+1,i,i));
			else {
				h[i]=h[j]+1;
				f[i]=f[j]+cost(j,mid,j)+cost(mid+1,i,i);
			}
		}
	int ans1=1e9;
	for(int i=g[m+1]; i<=m; ++i) ans1=min(ans1,h[i]);
	ll ans2=inf;
	for(int i=g[m+1]; i<=m; ++i) if(h[i]==ans1) ans2=min(ans2,f[i]+cost(i,m,i));
	printf("%d",ans1);
	if(t) printf("\n%lld",ans2*2);
	return 0;
}