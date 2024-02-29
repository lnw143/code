#include<cstdio>
using namespace std;
const int N = 1e5;
using ll = long long;
int n,m,i,em,e[N * 2 + 2],ls[N + 2],nx[N * 2 + 2],p[N + 2]
ll f[N + 2][2];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dp(int x,int fa) {
	f[x][1]=p[x];
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			dp(e[i],x);
			f[x][1]+=min(f[e[i]][1],f[e[i]][0]);
			f[x][0]+=f[e[i]][1];
		}
}
int main() {
	scanf("%d%d %*s",&n,&m);
	for(i=1; i<=n; ++i)
		scanf("%d",&p[i]);
	for(i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	dp(1,-1);
	return 0;
}