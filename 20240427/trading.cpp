#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
constexpr int N = 5e3;
constexpr ll inf = 1ll << 60;
int n,m,sz[N + 2];
ll f[N + 2][N + 2],g[N + 2];
struct edge {
	int v,w;
	edge(int v,int w):v(v),w(w) {}
};
vector<edge> e[N + 2];
void dfs(int u,int p) {
	sz[u]=1;
	for(auto [v,w] : e[u]) 
		if(v!=p) {
			dfs(v,u);
			sz[u]+=sz[v];
		}
	int siz=1;
	for(auto [v,w] : e[u]) 
		if(v!=p) {
			for(int i=min(m,siz); i>=0; --i)
				for(int j=0; j<=min(sz[v],m-i); ++j)
					g[i+j]=max(g[i+j],f[u][i]+f[v][j]+ll(j*(m-j)+(sz[v]-j)*(n-sz[v]-(m-j)))*w);
			siz+=sz[v];
			for(int i=0; i<=m; ++i)
				f[u][i]=max(f[u][i],g[i]),g[i]=0;
		}
}
inline char gc() {
	static char buf[1<<16],*l=buf,*r=buf;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?EOF:*l++;
}
void read(int &x) {
	x=0;
	char c=gc();
	while(!isdigit(c)) c=gc();
	do x=(x<<1)+(x<<3)+(c^48); while(isdigit(c=gc()));
}
template<typename ...Args> void read(int &x,Args &...args) {
	read(x);
	read(args...);
}
int main() {
	freopen("trading.in","r",stdin);
	freopen("trading.out","w",stdout);
	read(n,m);
	for(int i=1; i<n; ++i) {
		int u,v,w;
		read(u,v,w);
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
	}
	dfs(1,1);
	printf("%lld",f[1][m]);
	return 0;
}