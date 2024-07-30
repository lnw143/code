#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e5;
int n,p[N + 2];
vector<int> e[N + 2];
void discrete(int n,int *a) {
	vector<int> vt;
	for(int i=1; i<=n; ++i) vt.push_back(a[i]);
	sort(vt.begin(),vt.end());
	for(int i=1; i<=n; ++i) a[i]=lower_bound(vt.begin(),vt.end(),a[i])-vt.begin()+1;
}
int dfn[N + 2],low[N + 2],dfc;
namespace psegtree {
	const int S = N << 6;
	int tot,s[S],ls[S],rs[S],rt[N + 2];
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		s[u]=0;
		if(l<r) {
			ls[u]=build(l,mid);
			rs[u]=build(mid+1,r);
		}
		return u;
	}
	int modify(int u,int l,int r,int x) {
		int v=++tot;
		s[v]=s[u];
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			++s[v];
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x);
		else rs[v]=modify(rs[v],mid+1,r,x);
		s[v]=s[ls[v]]+s[rs[v]];
		return v;
	}
	int query(int u,int v,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return s[v]-s[u];
		return query(ls[u],ls[v],l,mid,x,y)+query(rs[u],rs[v],mid+1,r,x,y);
	}
}
void dfs(int u) {
	dfn[u]=++dfc;
	{
		using namespace psegtree;
		rt[dfc]=modify(rt[dfc-1],1,n,p[u]);
	}
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
}
int main() {
 	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	discrete(n,p);
	for(int i=2; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		e[x].push_back(i);
	}
	{
		using namespace psegtree;
		rt[0]=build(1,n);
	}
	dfs(1);
	for(int i=1; i<=n; ++i) {
		using namespace psegtree;
		printf("%d\n",query(rt[dfn[i]],rt[low[i]],1,n,p[i]+1,n));
	}
	return 0;
}