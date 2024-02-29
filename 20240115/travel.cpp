#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 5e3, M = N * 2;
int n,m,i,j,em,e[M + 2],ls[N + 2],nx[M + 2],a[N + 2],ans[N + 2];
bool bz[M + 2],vis[N + 2];
struct Edge {
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
		if(x>y) x^=y^=x^=y;
	}
	bool operator<(const Edge t) const {
		return x==t.x?y<t.y:x<t.x;
	}
} eg[N + 2];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dfs(int x) {
	if(vis[x]) return ;
	a[++*a]=x;
	vis[x]=true;
	for(int i=ls[x]; i; i=nx[i])
		if(!bz[i])
			dfs(e[i]);
}
void upd_ans() {
	int i;
	for(i=1; i<=n; ++i) {
		if(a[i]>ans[i]) return ;
		if(a[i]<ans[i]) break;
	}
	for(; i<=n; ++i)
		ans[i]=a[i];
}
int main() {
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i)
		eg[i].read();
	stable_sort(eg+1,eg+m+1);
	for(i=m; i>=1; --i) {
		insert(eg[i].x,eg[i].y);
		insert(eg[i].y,eg[i].x);
	}
	if(m==n-1) {
		dfs(1);
		for(i=1; i<=n; ++i)
			printf("%d ",a[i]);
		return 0;
	}
	ans[1]=n+1;
	for(i=1; i<=m; ++i) {
		bz[i*2]=bz[i*2-1]=true;
		memset(vis,0,sizeof(vis));
		*a=0;
		dfs(1);
		bz[i*2]=bz[i*2-1]=false;
		if(*a==n)
			upd_ans();
	}
	for(i=1; i<=n; ++i)
		printf("%d ",ans[i]);
	return 0;
}