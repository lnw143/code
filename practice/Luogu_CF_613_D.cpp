#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(1e5), LOG_N(16 + 2);
int n,q;
vector<int> e[N + 2];
int dfn[N + 2],dfc,anc[N + 2][LOG_N],dep[N + 2];
void dfs(int u) {
	dfn[u]=++dfc;
	rep(i,1,LOG_N-1)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(int v : e[u])
		if(v!=anc[u][0])
			anc[v][0]=u,
			dep[v]=dep[u]+1,
			dfs(v);
}
vector<int> read() {
	int k;
	scanf("%d",&k);
	vector<int> t(k);
	for(auto &i : t)
		scanf("%d",&i);
	return t;
}
int lca(int x,int y) {
	if(dep[x]>dep[y]) swap(x,y);
	per(i,0,LOG_N-1)
		if(dep[anc[y][i]]>=dep[x])
			y=anc[y][i];
	if(x==y) return x;
	per(i,0,LOG_N-1)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
const auto dfn_cmp = [](int x,int y) { return dfn[x]<dfn[y]; };
int solve(vector<int> node) {
	sort()
}
int main() {
	scanf("%d",&n);
	rep(i,1,n-1) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	anc[1][0]=1;
	dfs(1);
	scanf("%d",&q);
	rep(i,1,q)
		printf("%d\n",solve(read()));
	return 0;
}