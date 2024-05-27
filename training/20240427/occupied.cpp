#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
constexpr int N = 1e5, M = 3e5;
struct edge {
	int u,v,w;
	bool operator<(const edge& e) const {
		return w<e.w;
	}
} eg[M + 2];
int n,m,a[N + 2],b[N + 2],fa[N + 2],mx[N + 2],mn[N + 2];
ll ans,cs[N + 2],Ans;
int find(int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
void unite(int u,int v,int w) {
	u=find(u),v=find(v);
	if(u==v) return ;
	ll p=max({w,mx[u],mx[v]}),q=min(mn[u],mn[v]);
	fa[v]=u;
	mx[u]=p;
	mn[u]=q;
	ans-=cs[u]+cs[v];
	cs[u]=min(cs[u]+cs[v],p*q);
	ans+=cs[u];
	Ans=min(Ans,ans);
}
int main() {
	freopen("occupied.in","r",stdin);
	freopen("occupied.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&a[i],&b[i]),fa[i]=i,mx[i]=a[i],mn[i]=b[i],cs[i]=(ll)a[i]*b[i],ans+=cs[i];
	Ans=ans;
	for(int i=1; i<=m; ++i)
		scanf("%d%d%d",&eg[i].u,&eg[i].v,&eg[i].w);
	sort(eg+1,eg+m+1);
	for(int i=1; i<=m; ++i) {
		const auto& [u,v,w]=eg[i];
		unite(u,v,w);
	}
	printf("%lld",Ans);
	return 0;
}