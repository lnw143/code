#include <cstdio>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <random>
#define clock() chrono::steady_clock::now()
using namespace std;
const int N = 1e3;
const auto startTime = clock();
int n,m,p[N + 2];
vector<int> e[N + 2];
bool bz[N + 2];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
double runtime() {
	return chrono::duration<double>(clock()-startTime).count();
}
int match(int u) {
	shuffle(e[u].begin(),e[u].end(),rnd);
	bz[u]=true;
	for(auto v : e[u])
		if(!p[v])
			return p[v]=u,p[u]=v,1;
	for(auto v : e[u]) {
		int w=p[v];
		if(bz[w]) continue;
		p[u]=v,p[v]=u,p[w]=0;
		if(match(w)) return 1;
		p[v]=w,p[w]=v,p[u]=0;
	}
	return 0;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int ans=0;
	while(runtime()<0.9) {
		for(int i=1; i<=n; ++i) 
			if(!p[i]) {
				memset(bz,0,sizeof(bz));
				ans+=match(i);
			}
	}
	printf("%d\n",ans);
	for(int i=1; i<=n; ++i)
		printf("%d ",p[i]);
	return 0;
}