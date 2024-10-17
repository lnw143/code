#include <cstdio>
using namespace std;
const int N = 1e5, M = 1e5;
int n,m,deg[N + 2],que[N + 2];
int ls[N + 2],em,e[M + 2],nx[M + 2];
double w[M + 2],f[N + 2];
void insert(int x,int y,double z) {
	e[++em]=y;
	w[em]=z;
	nx[em]=ls[x];
	ls[x]=em;
}
int main() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int u,v;
		double w;
		scanf("%d%d%lf",&u,&v,&w);
		insert(u,v,w);
		++deg[v];
	}
	int h=1,t=0;
	for(int i=1; i<=n; ++i)
		if(deg[i]==0)
			que[++t]=i;
	f[1]=1;
	for(; h<=t; ++h) {
		int u=que[h];
		for(int i=ls[u]; i; i=nx[i]) {
			f[e[i]]+=f[u]*w[i];
			if(--deg[e[i]]==0)
				que[++t]=e[i];
		}
	}
	printf("%.2lf",f[n]);
	return 0;
}