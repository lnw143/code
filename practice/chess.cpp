#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e2, M = N * N, E = M * 4;
int n,t,i,j,k,ans,em,e[E + 2],ls[M + 2],nx[E + 2],match[M + 2];
bool bz[M + 2],vis[M + 2];
int pos(int x,int y) {
	return (x-1)*n+y;
}
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
bool dfs(int x) {
	if(vis[x]) return false;
	vis[x]=true;
	for(int i=ls[x]; i; i=nx[i])
		if(!match[e[i]]||dfs(match[e[i]])) {
			match[e[i]]=x;
			return true;
		}
	return false;
}
int main() {
	scanf("%d%d",&n,&t);
	for(i=1; i<=t; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		bz[pos(x,y)]=true;
	}
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j) if(!bz[pos(i,j)]) {
				if((i&1)==(j&1)) {
					if(j<n&&!bz[pos(i,j)+1])
						insert(pos(i,j),pos(i,j)+1);
					if(i<n&&!bz[pos(i,j)+n])
						insert(pos(i,j),pos(i,j)+n);
				} else {
					if(j<n&&!bz[pos(i,j)+1])
						insert(pos(i,j)+1,pos(i,j));
					if(i<n&&!bz[pos(i,j)+n])
						insert(pos(i,j)+n,pos(i,j));
				}
			}
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if((i&1)==(j&1)&&!bz[pos(i,j)]) {
				memset(vis,0,sizeof(vis));
				if(dfs(pos(i,j))) ++ans;
			}
	printf("%d",ans);
	return 0;
}