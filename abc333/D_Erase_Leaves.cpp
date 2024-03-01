#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 3e5 + 2;
int n,i,u,v,ans,sz[N],em,e[N * 2],ls[N],nx[N * 2];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dfs(int x,int fa) {
	sz[x]=1;
	for(int i=ls[x]; i; i=nx[i]) if(e[i]!=fa) {
			dfs(e[i],x);
			sz[x]+=sz[e[i]];
			if(x==1) ans=max(ans,sz[e[i]]);
		}
}
int main() {
	scanf("%d",&n);
	for(i=1; i<n; ++i) {
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	dfs(1,-1);
	printf("%d",n-ans);
	return 0;
}