#include "testlib.h"
#include <vector>
using namespace std;
const int N = 1e3, M = 1e5;
int n,m,e[N + 2][N + 2],x[M + 2],y[M + 2],w[M + 2];
int vis[M + 2];
vector<int> path;
void readInf() {
	n=inf.readInt(1,N);
	m=inf.readInt(1,M);
	for(int i=1; i<=m; ++i) {
		x[i]=inf.readInt(1,n);
		y[i]=inf.readInt(1,n);
		w[i]=inf.readInt(1,1000);
		inf.ensuref(e[x[i]][y[i]]==0,"multiple edges found");
		inf.ensuref(x[i]!=y[i],"self loop found");
		e[x[i]][y[i]]=e[y[i]][x[i]]=i;
	}
}
void readOuf() {
	while(!ouf.seekEof()) path.push_back(ouf.readInt(1,n));
}
int main(int argc, char* argv[]) {
	// usage : checker.exe <.in> <.out> <.ans>
	registerTestlibCmd(argc, argv);
	readInf();
	readOuf();
	// no Ans
	ouf.ensuref(!path.empty(),"empty output");
	ouf.ensuref(path.front()==1,"you should start from 1");
	ouf.ensuref(path.back()==1,"you should end at 1");
	int u=1;
	for(int i=1; i<path.size(); ++i) {
		int v=path[i];
		if(!e[u][v]) quitf(_wa,"there is no edges between %d and %d",u,v);
		++vis[e[u][v]];
		u=v;
	}
	long long ans=0;
	for(int i=1; i<=m; ++i)	
		if(!vis[i])
			quitf(_wa,"edge %d (%d,%d) missed",i,x[i],y[i]);
		else
			ans+=1ll*w[i]*vis[i];
	quitf(_ok,"no problem, total cost = %lld",ans);
	return 0;
}