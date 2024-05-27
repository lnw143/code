#include<cstdio>
using namespace std;
using ll = long long;
const int N = 1e5, M = 1e4, A = 1e3;
const ll inf = 1ll << 60;
int n,m,a[N + 2],b[N + 2],r[A + 2][A + 2],sz[A + 2];
ll s[A + 2];
void add(int u,int v,int f) {
	s[u]+=v/u*f;
	for(int i=0; i<v%u; ++i)
		r[u][i]+=f;
	sz[u]+=f;
}
ll cost(ll x) {
	ll sum=0;
	for(int i=1; i<=A; ++i)
		sum+=x/i*sz[i]-s[i]-r[i][x%i];
	return sum;
}
void _main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i)
		scanf("%d",&b[i]);
	for(int i=1; i<=n; ++i)
		add(a[i],b[i],1);
	for(int i=1; i<=m; ++i) {
		int op;
		scanf("%d",&op);
		if(op<=2) {
			int x,y;
			scanf("%d%d",&x,&y);
			add(a[x],b[x],-1);
			(op==1?a:b)[x]=y;
			add(a[x],b[x],1);
		} else {
			int l=0,r=1e9,mid,k;
			scanf("%d",&k);
			while(l<=r) {
				mid=l+r>>1;
				if(cost(mid)>=k) r=mid-1;
				else l=mid+1;
			}
			printf("%d\n",r+1);
		}
	}
	for(int i=1; i<=n; ++i)
		add(a[i],b[i],-1);
}
int main() {
	freopen("calculate.in","r",stdin);
	freopen("calculate.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) _main();
	return 0;
}