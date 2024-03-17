#include<cstdio>
using namespace std;
const int N = 2e2 + 10, M = 10200 + N * 4;
int n,m,f[N + 2],S,T;
int ls[N + 2],nx[M + 2],w[M + 2],to[M + 2],em;
void insert(int x,int y,int z) {
	to[++em]=y;
	w[em]=z;
	nx[em]=ls[x];
	ls[x]=em;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		insert(x,y,z);
		insert(y,x,0);
		f[x]-=z;
		f[y]+=z;
	}
	S=n+1,T=n+2;
	
	return 0;
}