#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e5, M = 2e5, K = 50;
int T,n,m,k,p,i,f[N + 2][K + 2];
bool vis[N + 2][K + 2];
struct Node {
	int x,d;
	bool operator<(const Node t) const {
		return d<t.d;
	}
};
template<typename T>
struct Heap {
	T hp[M + 2];
	int hs;
	void push(T x) {
		int k=++hs;
		hp[k]=x;
		while(k>1&&hp[k]<hp[k/2]) {
			swap(hp[k],hp[k/2]);
			k/=2;
		}
	}
	T pop() {
		T top=hp[1];
		hp[1]=hp[hs--];
		int k=1;
		while((k*2<=hs&&hp[k*2]<hp[k])||(k*2+1<=hs&&hp[k*2+1]<hp[k])) {
			int kk=k*2;
			if(kk+1<=hs&&hp[kk+1]<hp[kk]) ++kk;
			swap(hp[kk],hp[k]);
			k=kk;
		}
		return top;
	}
} ;
struct Graph {
	int em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2],dis[N + 2];
	void insert(int x,int y,int z) {
		e[++em]=y;
		nx[em]=ls[x];
		cs[em]=z;
		ls[x]=em;
	}
	void dij(int s) {
		Heap<Node> q;
		q.hs=0;
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		q.push({s,0});
		for(int i=1; i<n&&q.hs>0; ++i) {
			Node u=q.pop();
			while(q.hs>0&&dis[u.x]!=u.d) u=q.pop();
			if(dis[u.x]!=u.d) break;
			for(int j=ls[u.x]; j; j=nx[j])
				if(u.d+cs[j]<dis[e[j]]) {
					dis[e[j]]=u.d+cs[j];
					q.push({e[j],dis[e[j]]});
				}
		}
	}
} G,G_;
int *e=G_.e,*ls=G_.ls,*nx=G_.nx,*cs=G_.cs,*dis=G.dis;
#define ad(x,y) (x+=y)%=p
int dfs(int x,int y) {
	if(y<0||y>k) return 0;
	if(vis[x][y]) return -1;
	if(~f[x][y]) return f[x][y];
	vis[x][y]=true;
	f[x][y]=x==1;
	for(int i=ls[x]; i; i=nx[i]) {
		int r=dfs(e[i],y+dis[e[i]]+cs[i]-dis[x]);
		if(r==-1) return -1;
		ad(f[x][y],r);
	}
	vis[x][y]=false;
	return f[x][y];
}
int main() {
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%d",&n,&m,&k,&p);
		memset(f,-1,sizeof(f));
		memset(vis,0,sizeof(vis));
		memset(G.ls,0,sizeof(G.ls));
		memset(G_.ls,0,sizeof(G_.ls));
		G.em=G_.em=0;
		for(i=1; i<=m; ++i) {
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			G.insert(u,v,w);
			G_.insert(v,u,w);
		}
		G.dij(1);
		printf("%d\n",dfs(n,0));
	}
	return 0;
}