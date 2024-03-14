#include<cstdio>
#include<vector>
using namespace std;
const int
	N = 1e6,
	M = N * 2
;
int n,m,u[N + 2],v[N + 2];
bool x[N + 2],y[N + 2];
vector<int> e[M + 2];
int dfn[M + 2],low[M + 2],dfc,scc[M + 2],cnt,stk[M + 2],tp;
bool in_stk[M + 2];
void tarjan(int u) {
	if(dfn[u]) return ;
	low[u]=dfn[u]=++dfc;
	in_stk[u]=true;
	stk[++tp]=u;
	for(auto v : e[u])
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} else if(in_stk[v])
			low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u]) {
		++cnt;
		while(stk[tp]!=u) {
			scc[stk[tp]]=cnt;
			in_stk[stk[tp]]=false;
			--tp;
		}
		scc[u]=cnt;
		in_stk[u]=false;
		--tp;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d%d%d",&u[i],&x[i],&v[i],&y[i]);
		e[u[i]+(!x[i])*n].push_back(v[i]+y[i]*n);
		e[v[i]+(!y[i])*n].push_back(u[i]+x[i]*n);
	}
	for(int i=1; i<=n*2; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=n; ++i)
		if(scc[i]==scc[i+n]) {
			printf("IMPOSSIBLE");
			return 0;
		}
	printf("POSSIBLE\n");
	for(int i=1; i<=n; ++i)
		printf("%d ",scc[i]>scc[i+n]);
	return 0;
}