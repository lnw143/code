#include<cstdio>
using namespace std;
const int N = 14 + 2;
int n,m,i,j,s,u,v,w,e[N][N],f[1<<N];
int judge(int s,int x) {
	int ret=0;
	for(int i=0; i<n; ++i)
		if(s&(1<<i))
			ret+=e[i][x];
	return ret;
}
int max(int a,int b) {
	return a<b?b:a;
}
int main() {
	freopen("order.in","r",stdin);
	freopen("order.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]+=w;
	}
	s=(1<<n)-1;
	for(i=0; i<s; ++i)
		for(j=0; j<n; ++j)
			if((i&(1<<j))==0)
				f[i|(1<<j)]=max(f[i|(1<<j)],f[i]+judge(i,j));
	printf("%d",f[s]);
	return 0;
}