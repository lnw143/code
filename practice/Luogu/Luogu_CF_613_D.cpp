#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(1e5), LOG_N(16 + 2), inf(1 << 30);
int n,q;
vector<int> e[N + 2],ve[N + 2];
int dfn[N + 2],dfc,anc[N + 2][LOG_N],dep[N + 2];
bool bz[N + 2];
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
int dp(int u,int &ans) {
	int r=0;
	for(int v:ve[u]) {
		if(bz[u]&&bz[v]&&anc[v][0]==u) ans=-inf;
		r+=dp(v,ans);
	}
	if(bz[u]) {
		ans+=r;
		return 1;
	}
	if(r>1) {
		++ans;
		return 0;
	}
	return r;
}
int solve(vector<int> node) {
	sort(node.begin(),node.end(),dfn_cmp);
	static int stk[N + 2],tp;
	stk[tp=1]=1;
	ve[1].clear();
	for(int u:node) if(u!=1) {
		int l=lca(stk[tp],u);
		if(l!=stk[tp]) {
			while(dfn_cmp(l,stk[tp-1])) {
				ve[stk[tp-1]].push_back(stk[tp]);
				--tp;
			}
			if(l!=stk[tp-1]) {
				ve[l].clear();
				ve[l].push_back(stk[tp]);
				stk[tp]=l;
			} else {
				ve[l].push_back(stk[tp]);
				--tp;
			}
		}
		ve[u].clear();
		stk[++tp]=u;
	}
	rep(i,1,tp-1)
		ve[stk[i]].push_back(stk[i+1]);
	for(int u:node)
		bz[u]=true;
	int ans=0;
	dp(1,ans);
	for(int u:node)
		bz[u]=false;
	return ans<0?-1:ans;
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