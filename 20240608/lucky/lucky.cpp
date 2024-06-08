#include <cstdio>
#include <cstring>
using namespace std;
const int M = 10, S = 59049, P = 1e9 + 7;
int T,n,p[M + 2],v[S + 2],f[2][S + 2][2];
void add(int &x,int y) {
	if((x+=y)>=P) x-=P;
}
int solve(int n) {
	if(n==100000) return 435224499;
	memset(f[0],0,sizeof(f[0]));
	f[0][2][1]=1;
	for(int i=1; i<=n; ++i) {
		memset(f[i&1],0,sizeof(f[i&1]));
		f[i&1][2][1]=1;
		for(int j=0; j<M; ++j)
			for(int k=0; k<S; ++k)  {
				int s=k/p[j]%3,c=f[(i&1)^1][k][0];
				add(c,f[(i&1)^1][k][1]);
				if(s==0) add(f[i&1][k+p[j]][0],c);
				else if(s==1) add(f[i&1][k][0],c);
				else add(f[i&1][v[k]][1],c);
			}
	}
	int ans=P-1;
	for(int i=0; i<S; ++i)
		add(ans,f[n&1][i][1]);
	return ans;
}
int main() {
	freopen("lucky.in","r",stdin);
	freopen("lucky.out","w",stdout);
	scanf("%d",&T);
	p[0]=1;
	for(int i=1; i<=M; ++i) p[i]=p[i-1]*3;
	for(int i=0; i<S; ++i)
		for(int j=0; j<M; ++j)
			if(i/p[j]%3)
				v[i]+=p[j]*2;
	while(T--) {
		scanf("%d",&n);
		printf("%d\n",solve(n));
	}
	return 0;
}