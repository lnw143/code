#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100, M = N * (N + 1) / 2;
int n,m,i,j,s,t,fa[N + 2],ans=1<<30;
struct Edge {
	int u,v,w;
	bool operator<(const Edge e) const {
		return w<e.w;
	}
} e[M + 2];
int fd(int x) {
	return fa[x]==x?x:fa[x]=fd(fa[x]);
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	scanf("%d%d",&s,&t);
	stable_sort(e+1,e+m+1);
	for(i=1; i<=m; ++i) {
		for(j=1; j<=n; ++j)
			fa[j]=j;
		for(j=i; j<=m; ++j) {
			if(e[j].w-e[i].w>=ans) break;
			fa[fd(e[j].u)]=fd(e[j].v);
			if(fd(s)==fd(t)) {
				ans=e[j].w-e[i].w;
				break;
			}
		}
	}
	printf("%d",ans==(1<<30)?-1:ans);
	return 0;
}