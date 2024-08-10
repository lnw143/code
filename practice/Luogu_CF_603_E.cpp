#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 3e5;
int n,m;
vector<int> num;
struct edge {
	int u,v,w;
} e[M + 2];
vector<int> p[M + 2];
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
	if(l>r) return ;
	if(x>y) {
		for(int i=l; i<=r; ++i) ans[i]=num.size()+1;
		return ;
	}
	const int point1=pdsu::current();
	int mid=(l+r)/2;
	for(int i=l; i<=mid; ++i)
		if(e[i].w<x)
			pdsu::merge(e[i].u,e[i].v);
	const int point2=pdsu::current();
	ans[mid]=num.size()+1;
	for(int i=x; i<=y; ++i) {
		for(auto j : p[i]) {
			if(j>mid) break;
			pdsu::merge(e[j].u,e[j].v);
		}
		if(pdsu::tot==0) {
			ans[mid]=i;
			break;
		}
	}
	pdsu::undo(point2);
	solve(mid+1,r,x,ans[mid]);
	pdsu::undo(point1);
	if(ans[mid]<=num.size()) for(int i=x; i<ans[mid]; ++i)
		for(auto j : p[i]) {
			if(j>=l) break;
			pdsu::merge(e[j].u,e[j].v);
		}
	solve(l,mid-1,ans[mid],y);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	for(int i=1; i<=m; ++i) num.push_back(e[i].w);
	sort(num.begin(),num.end());
	for(int i=1; i<=m; ++i) e[i].w=lower_bound(num.begin(),num.end(),e[i].w)-num.begin()+1,p[e[i].w].push_back(i);
	pdsu::init();
	solve(1,m,1,num.size());
	for(int i=1; i<=m; ++i) {
		if(ans[i]>num.size()) printf("-1\n");
		else printf("%d\n",num[ans[i]-1]);
	}
	return 0;
}