#include<cstdio>
#include<cstring>
#define forn(x) for(x=1; x<=n; ++x) 
using namespace std;
const int N = 1e3 + 2, M = 3e3 + 2;
int n,m,i,j,k,u[M],v[M],w[M],f[N][N],s[N],dis[N];
int min(int a,int b) {
	return a<b?a:b;
}
struct Graph {
	int em,*e,*nx,*cs,ls[N];
	void insert(int x,int y,int z) {
		e[++em]=y;
		cs[em]=z;
		nx[em]=ls[x];
		ls[x]=em;
	}
	Graph(int m) {
		e=new int[m];
		nx=new int[m];
		cs=new int[m];
	}
} gr(M * 2);
struct Heap {
	int x,v;
	Heap(int a=0,int b=0):x(a),v(b) {}
} 
void dij(Graph g,int s) {
	memset(dis,0x7f,sizeof(dis));
	dis[s]=0;

}
int main() {
	scanf("%d%d",&n,&m);
	forn(i)
		forn(j)
			f[i][j]=i==j?0:1e9;
	for(i=1; i<=m; ++i) {
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
		gr.insert(u[i],v[i],w[i]);
		gr.insert(u[i],v[i],w[i]);
	}
	return 0;
}
