#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5 + 2;
using ll = long long;
int n,m,i,t[N + 2],v[N + 2],vis[N + 2],dfc,a[N + 2];
ll ans;
struct Node {
	int x,y;
	bool operator<(const Node t) const {
		return x-y>t.x-t.y;
	}
} b[N];
int dfs(int x) {
	if(x==0) return -1;
	vis[x]=dfc;
	if(vis[t[x]]) {
		if(vis[t[x]]==dfc) {
			a[++*a]=v[x];
			return t[x]==x?-1:t[x];
		}
		return -1;
	}
	int r=dfs(t[x]);
	if(~r) {
		a[++*a]=v[x];
		return r==x?-1:r;
	}
	return -1;
}
void wk() {
	if(*a==0) return ;
	stable_sort(a+1,a+*a+1);
	if(*a%2==1) ans-=a[*a/2+1];
	else {
		b[++m].x=a[*a/2+1];
		b[m].y=a[*a/2];
	}
	*a=0;
}
int main() {
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&t[i]);
	for(i=1; i<=n; ++i)
		scanf("%d",&v[i]),ans+=v[i];
	for(i=1; i<=n; ++i)
		if(!vis[i]) {
			++dfc;
			dfs(i);
			wk();
		}
	stable_sort(b+1,b+m+1);
	for(i=1; i<=m; ++i)
		ans-=(i&1)?b[i].x:b[i].y;
	printf("%lld",ans);
	return 0;
}