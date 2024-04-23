#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 5e3 + 2;
int n,i,u,em,e[N * 2],ls[N],nx[N * 2],f[N],sz[N];
bool g[N][N];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dfs(int x,int fa) {
	g[x][0]=true;
	sz[x]=1;
	f[x]=0;
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			dfs(e[i],x);
			f[x]+=f[e[i]];
			sz[x]+=sz[e[i]];
			for(int j=n-sz[e[i]]; j>=0; --j)
				if(g[x][j])
					g[x][j+sz[e[i]]]=true;
		}
	int s=0;
	for(int j=1; j<sz[x]; ++j)
		if(g[x][j])
			s=max(s,j*(sz[x]-j-1));
	f[x]+=s;
}
int main() {
	scanf("%d",&n);
	for(i=2; i<=n; ++i) {
		scanf("%d",&u);
		insert(i,u);
		insert(u,i);
	}
	dfs(1,-1);
	printf("%d",f[1]);
	return 0;
}