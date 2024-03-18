#include<cstdio>
#include<cstring>
#include<queue>
#include<cassert>
using namespace std;
const int N = 2e2 + 10, M = 10200 + N, inf = 1 << 30;
int n,m,f[N + 2],v[M + 2],up[M + 2],S,T;
int ls[N + 2],nx[M * 2 + 2],w[M * 2 + 2],e[M * 2 + 2],em=1;
int cur[N + 2],dep[N + 2];
void insert(int x,int y,int z) {
	e[++em]=y;
	w[em]=z;
	nx[em]=ls[x];
	ls[x]=em;
}
bool bfs() {
	memset(dep,-1,sizeof(dep));
	queue<int> q;
	dep[S]=0;
	q.push(S);
	while(!q.empty()) {
		int u=q.front();
		cur[u]=ls[u];
		q.pop();
		for(int i=ls[u]; i; i=nx[i])
			if(dep[e[i]]==-1&&w[i]) {
				dep[e[i]]=dep[u]+1;
				q.push(e[i]);
			}
	}
	return dep[T]!=-1;
}
int dfs(int u,int rem) {
	if(u==T) return rem;
	int rm=rem;
	for(int i=cur[u]; i; i=nx[i])
		if(dep[e[i]]==dep[u]+1&&w[i]) {
			int r=dfs(e[i],min(rm,w[i]));
			cur[u]=i;
			if(r) {
				w[i]-=r;
				w[i^1]+=r;
				rm-=r;
				if(!rm) break;
			}
		}
	return rem-rm;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int x,y,lo;
		scanf("%d%d%d%d",&x,&y,&lo,&up[i]);
		insert(x,y,up[i]-lo);
		v[i]=em;
		insert(y,x,0);
		f[x]-=lo;
		f[y]+=lo;
	}
	S=n+1,T=n+2;
	for(int i=1; i<=n; ++i)
		if(f[i]<0) {
			insert(i,T,-f[i]);
			insert(T,i,0);
		} else if(f[i]>0) {
			insert(S,i,f[i]);
			insert(i,S,0);
		}
	while(bfs()) dfs(S,inf);
	for(int i=ls[S]; i; i=nx[i])
		if(w[i]) 
			return printf("NO"),0;
	for(int i=ls[T]; i; i=nx[i])
		if(w[i^1])
			return printf("NO"),0;
	printf("YES\n");
	for(int i=1; i<=m; ++i) {
		printf("%d\n",up[i]-w[v[i]]);
	}
	return 0;
}