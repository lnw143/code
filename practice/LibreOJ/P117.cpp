#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int N = 5e4 + 10, inf = 1 << 30;
int n,m,s,t,S,T,f[N];
long long ans;
namespace netflow {
	struct Edge { int v,w,id; };
	vector<Edge> e[N];
	int dep[N],cur[N];
	void insert(int x,int y,int z) {
		int idx=e[x].size(),idy=e[y].size();
		e[x].push_back({y,z,idy});
		e[y].push_back({x,0,idx});
	}
	bool bfs(int s,int t) {
		queue<int> q;
		memset(dep,-1,sizeof(dep));
		dep[s]=0;
		q.push(s);
		while(!q.empty()) {
			int u=q.front();
			cur[u]=0;
			q.pop();
			for(const auto& [v,w,id] : e[u])
				if(dep[v]==-1&&w) {
					dep[v]=dep[u]+1;
					q.push(v);
				}
		}
		return dep[t]!=-1;
	}
	int dfs(int u,int rem,const int t) {
		if(u==t) return rem;
		int r=rem;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,id]=e[u][i];
			if(dep[v]!=dep[u]+1||!w) continue;
			int f=dfs(v,min(w,rem),t);
			w-=f;
			e[v][id].w+=f;
			r-=f;
			if(!r) break;
		}
		return rem-r;
	}
	bool check(int s,int t) {
		for(const auto& [v,w,id] : e[s])
			if(w) return false;
		for(const auto& [v,w,id] : e[t])
			if(e[v][id].w) return false;
		return true;
	}
}
int main() {
	scanf("%d%d%d%d",&n,&m,&s,&t);
	S=n+1,T=n+2;
	for(int i=1; i<=m; ++i) {
		int u,v,lo,up;
		scanf("%d%d%d%d",&u,&v,&lo,&up);
		netflow::insert(u,v,up-lo);
		f[u]-=lo;
		f[v]+=lo;
	}
	for(int i=1; i<=n; ++i)
		if(f[i]<0)
			netflow::insert(i,T,-f[i]);
		else if(f[i]>0) 
			netflow::insert(S,i,f[i]);
	netflow::insert(t,s,inf);
	while(netflow::bfs(S,T)) netflow::dfs(S,inf,T);
	if(!netflow::check(S,T)) return printf("please go home to sleep"),0;
	ans=netflow::e[s].back().w;
	netflow::e[s].pop_back();
	netflow::e[t].pop_back();
	while(netflow::bfs(t,s)) ans-=netflow::dfs(t,inf,s);
	printf("%lld",ans);
	return 0;
}