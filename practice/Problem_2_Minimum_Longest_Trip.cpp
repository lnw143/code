#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int N = 2e5, M = 4e5;
int n,m,em,e[M + 2],ls[N + 2],nx[M + 2],lb[M + 2],deg[N + 2],dep[N + 2];
vector<int> vec[N + 2];
void insert(int x,int y,int z) {
	e[++em]=y;
	nx[em]=ls[x];
	lb[em]=z;
	ls[x]=em;
}
void bfs() {
	queue<int> q;
	for(int i=1; i<=n; ++i)
		
	while(!q.empty()) {
		int u=q.front();
		q.pop();

	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		insert(v,u,w);
		++deg[u];
	}
	
	return 0;
}