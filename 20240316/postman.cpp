#include<cstdio>
#include<random>
#include<vector>
#include<utility>
const int N = 1e3, M = 1e5;
using namespace std;
int n,m,ans;
vector<pair<int,int>> e[N + 2];
namespace graph {
	int dfn[N + 2],low[N + 2],dfc,color[N + 2],cnt,stk[N + 2],tp;
	void tarjan(int u,int fa) {
		if(dfn[u]) return ;
		dfn[u]=low[u]=++dfc;
		stk[++tp]=u;
		for(const auto& [v,w] : e[u])
			if(!dfn[v]) {
				tarjan(v,u);
				if(dfn[v]==low[v])
					ans+=w;
				low[u]=min(low[u],low[v]);
			} else if(v!=fa)
				low[u]=min(low[u],dfn[v]);
		if(low[u]==dfn[u]) {
			color[u]=++cnt;
			while(stk[tp]!=u)
				color[stk[tp--]]=cnt;
			--tp;
		}
	}
	void cutDown() {
		for(int i=1; i<=n; ++i)
			if(!dfn[i])
				tarjan(i,-1);
	}
}

int main() {
	static char infile[1<<10],outfile[1<<10];
	int t;
	scanf("%d",&t);
	sprintf(infile,"d:/code/20240316/data/postman%d.in",t);
	sprintf(outfile,"d:/code/20240316/data/postman%d.out",t);
	freopen(infile,"r",stdin);
	freopen(outfile,"a",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
		ans+=w;
	}
	graph::cutDown();
	printf("%d\n",ans);
	return 0;
}