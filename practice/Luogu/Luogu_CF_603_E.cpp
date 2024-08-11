#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 3e5;
int n,m;
struct edge {
	int u,v,w;
} e[M + 2];
int p[M + 2],q[M + 2];
int odd(int x) {
	return x&1;
}
namespace pdsu {
	int fa[N + 2],sz[N + 2],tot;
	vector<pair<int,int>> fu,su;
	vector<int> tu;
	void init() {
		for(int i=1; i<=n; ++i) fa[i]=i,sz[i]=1;
		tot=n;
	}
	int find(int u) {
		return fa[u]==u?u:find(fa[u]);
	}
	void merge(int u,int v) {
		u=find(u),v=find(v);
		if(u==v) return ;
		if(sz[u]<sz[v]) swap(u,v);
		fu.emplace_back(v,fa[v]);
		fa[v]=u;
		su.emplace_back(u,sz[u]);
		sz[u]+=sz[v];
		tu.push_back(tot);
		if(odd(sz[v])&&!odd(sz[u])) tot-=2;
	}
	int current() {
		return fu.size();
	}
	void undo(int time) {
		while(current()>time) {
			fa[fu.back().first]=fu.back().second;
			sz[su.back().first]=su.back().second;
			tot=tu.back();
			fu.pop_back();
			su.pop_back();
			tu.pop_back();
		}
	}
}
int ans[M + 2];
void solve(int l,int r,int x,int y) {
	if(l>r||x>y) return ;
	const int point1=pdsu::current();
	int mid=(l+r)/2;
	for(int i=l; i<=mid; ++i)
		if(q[i]<x)
			pdsu::merge(e[i].u,e[i].v);
	const int point2=pdsu::current();
	for(int i=x; i<=y; ++i) {
		if(p[i]<=mid) pdsu::merge(e[p[i]].u,e[p[i]].v);
		if(pdsu::tot==0) {
			ans[mid]=i;
			break;
		}
	}
	pdsu::undo(point2);
	solve(mid+1,r,x,!ans[mid]?y:ans[mid]);
	pdsu::undo(point1);
	for(int i=x; i<ans[mid]; ++i)
		if(p[i]<l)
			pdsu::merge(e[p[i]].u,e[p[i]].v);
	if(ans[mid]) solve(l,mid-1,ans[mid],y);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w),
		p[i]=i;
	sort(p+1,p+m+1,[](int x,int y) {
		return e[x].w<e[y].w;
	});
	for(int i=1; i<=m; ++i) q[p[i]]=i;
	pdsu::init();
	solve(1,m,1,m);
	for(int i=1; i<=m; ++i) {
		if(!ans[i]) printf("-1\n");
		else printf("%d\n",e[p[ans[i]]].w);
	}
	return 0;
}