#include<cstdio>
#include<utility>
#include<cstring>
#include<queue>
using namespace std;
using ll = long long;
using pli = pair<ll,int>;
#define val first
#define pos second
const int N = 3e5, M = 3 * N;
int n,m,p,q,i,j,em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2];
ll ans=1e18,dis[N + 2];
char s[N + 2];
int pos(int x,int y) {
	return (x-1)*m+y;
}
void insert(int x,int y,int z) {
	e[++em]=y;
	nx[em]=ls[x];
	cs[em]=z;
	ls[x]=em;
}
void insert(int x,int y,int u,int v,int cost) {
	if(x<1||n<x||y<1||m<y||u<1||n<u||v<1||m<v) return ;
	insert(pos(x,y),pos(u,v),cost);
}
priority_queue<pli,vector<pli>,greater<pli>> hp;
void dij() {
	for(int i=1; i<=n*m&&!hp.empty(); ++i) {
		pli u=hp.top();
		hp.pop();
		while(!hp.empty()&&dis[u.pos]!=u.val) {
			u=hp.top();
			hp.pop();
		}
		if(dis[u.pos]!=u.val) return ;
		for(int i=ls[u.pos]; i; i=nx[i])
			if(u.val+cs[i]<dis[e[i]]) {
				dis[e[i]]=u.val+cs[i];
				hp.push(pli(dis[e[i]],e[i]));
			}
	}
}
int main() {
	scanf("%d%d%d%d",&n,&m,&p,&q);
	memset(dis,0x3f,sizeof(dis));
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j) {
			scanf(" %c",&s[pos(i,j)]);
			switch(s[pos(i,j)]) {
				case 'L': {
					insert(i-1,j+1,i,j,p);
					insert(i+1,j+1,i,j,p);
					insert(i,j+2,i,j,q);
					break;
				}
				case 'R': {
					insert(i-1,j-1,i,j,p);
					insert(i+1,j-1,i,j,p);
					insert(i,j-2,i,j,q);
					break;
				}
				case 'U': {
					insert(i+1,j+1,i,j,p);
					insert(i+1,j-1,i,j,p);
					insert(i+2,j,i,j,q);
					break;
				}
				case 'D': {
					insert(i-1,j+1,i,j,p);
					insert(i-1,j-1,i,j,p);
					insert(i-2,j,i,j,q);
					break;
				}
				case '.': {
					dis[pos(i,j)]=0;
					hp.push(pli(0,pos(i,j)));
					break;
				}
			}
		}
	dij();
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j) {
			if(i<n) ans=min(ans,dis[pos(i,j)]+dis[pos(i+1,j)]);
			if(j<m) ans=min(ans,dis[pos(i,j)]+dis[pos(i,j+1)]);
		}
	printf("%lld",ans==1e18?-1:ans);
	return 0;
}