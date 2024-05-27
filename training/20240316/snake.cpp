#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 50, inf = 1 << 30;
int n,m,i,j,d[N + 2][N + 2],S,T,S_,T_;
char s[N + 2][N + 2];
namespace netflow {
	const int M = N * N + 10;
	int tot,dep[M + 2],f[M + 2],cur[M + 2];
	struct Edge { int v,w,id; };
	vector<Edge> e[M + 2];
	int newnode() {
		return ++tot;
	}
	void insert(int x,int y,int z) {
		int ix=e[x].size(),iy=e[y].size();
		e[x].push_back(Edge{y,z,iy});
		e[y].push_back(Edge{x,0,ix});
	}
	void link(int x,int y,int lo,int up) {
		if(!x||!y) return ;
		insert(x,y,up-lo);
		f[x]-=lo;
		f[y]+=lo;
	}
	bool bfs(int S,int T) {
		memset(dep,-1,sizeof(dep));
		queue<int> q;
		dep[S]=0;
		q.push(S);
		while(!q.empty()) {
			int u=q.front();
			cur[u]=0;
			q.pop();
			for(auto [v,w,id] : e[u])	
				if(dep[v]==-1&&w) {
					dep[v]=dep[u]+1;
					q.push(v);
				}
		}
		return dep[T]!=-1;
	}
	int dfs(int u,int flow,const int T) {
		if(u==T) return flow;
		int rem=flow;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,id]=e[u][i];
			if(dep[v]==dep[u]+1&&w) {
				int r=dfs(v,min(w,rem),T);
				rem-=r;
				w-=r;
				e[v][id].w+=r;
				if(!rem) break;
			}
		}
		return flow-rem;
	}
}
int main() {
	using namespace netflow;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%s",s[i]+1);
	S=newnode(),T=newnode();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(s[i][j]=='.') {
				d[i][j]=newnode();
				if((i^j)&1) {
					link(d[i-1][j],d[i][j],0,1);
					link(d[i][j-1],d[i][j],0,1);
					link(d[i][j],T,2-(i==1||j==1||i==n||j==m),2);
				} else {
					link(d[i][j],d[i-1][j],0,1);
					link(d[i][j],d[i][j-1],0,1);
					link(S,d[i][j],2-(i==1||j==1||i==n||j==m),2);
				}
			}
	S_=newnode(),T_=newnode();
	for(int i=1; i<=tot-2; ++i)
		if(f[i]>0) insert(S_,i,f[i]);
		else if(f[i]<0) insert(i,T_,-f[i]);
	insert(T,S,inf);
	while(bfs(S_,T_)) dfs(S_,inf,T_);
	for(auto [v,w,id] : e[S_])
		if(w) return printf("-1"),0;
	for(auto [v,w,id] : e[T_])
		if(e[v][id].w) return printf("-1"),0;
	e[S].pop_back();
	e[T].pop_back();
	while(bfs(S,T)) dfs(S,inf,T);
	int ans=0;
	for(auto [v,w,id] : e[S])
		if(w) ++ans;
	for(auto [v,w,id] : e[T])
		if(e[v][id].w) ++ans;
	printf("%d\n",ans/2);
	return 0;
}