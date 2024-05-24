#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
using ll = long long;
using LL = __int128;
const int N = 1e5;
int n,fa[N + 2],q[N + 2],s[N + 2],dep[N + 2],p[N + 2];
ll a[N + 2],b[N + 2],c[N + 2];
vector<int> e[N + 2];
void dfs(int u,int p) {
	dep[u]=dep[p]+1;
	fa[u]=p;
	for(auto v : e[u])
		if(v!=p)
			dfs(v,u);
}
LL grow(int x,LL l,LL r) {
	if(c[x]>=0) return b[x]*(r-l+1)+(l+r)*(r-l+1)/2*c[x];
	else {
		LL t=(b[x]-1)/-c[x];
		if(t<l) return r-l+1;
		if(r<=t) return b[x]*(r-l+1)+(l+r)*(r-l+1)/2*c[x];
		return b[x]*(t-l+1)+(l+t)*(t-l+1)/2*c[x]+r-t;
	}
}
bool check(int x) {
	for(int i=1; i<=n; ++i) {
		int l=1,r=x,mid;
		while(l<=r) {
			mid=(l+r)/2;
			if(grow(i,mid,x)>=a[i]) l=mid+1;
			else r=mid-1;
		}
		if(l==1) return false;
		q[i]=l-1;
	}
	for(int i=n; i>1; --i)
		q[fa[p[i]]]=min(q[fa[p[i]]],q[p[i]]-1);
	for(int i=1; i<=n; ++i)
		if(q[i]<1) return false;
	for(int i=1; i<=n; ++i)
		if(q[i]<=n) ++s[q[i]];
	for(int i=1; i<n; ++i)
		s[i+1]+=s[i];
	bool ans=true;
	for(int i=1; i<=n; ++i)
		if(s[i]>i) {
			ans=false;
			break;
		}
	for(int i=1; i<=n; ++i)
		s[i]=0;
	return ans;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	for(int i=1; i<=n; ++i) p[i]=i;
	sort(p+1,p+n+1,[](int x,int y) {
		return dep[x]<dep[y];
	});
	int l=1,r=1e9,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%d",r+1);
	return 0;
}