#include<cstdio>
#include<cstring>
#define my f[i&1]
#define yr f[(i&1)^1]
#define pw2(x) (1<<(x))
using namespace std;
const int N = (1 << 9) + 2, K = 9 + 2;
int k,n,i,j,h,w[N][N],f[2][N],p,q,ans=1e9;
int lg2(int x) {
	int s=0,r=0;
	while(x) {
		if(x&1) r=s;
		++s;
		x>>=1;
	}
	return r;
}
int min(int a,int b) {
	return a<b?a:b;
}
int main() {
	scanf("%d",&k);
	n=pw2(k);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			scanf("%d",&w[i][j]);
	for(i=2; i<=n; ++i) {
		memset(my,0x3f,sizeof(my));
		p=lg2((i-1)^(i-2));
		for(j=1; j<=n; ++j) {
			q=((j-1)/pw2(p))^1;
			for(h=(q<<p)+1; h<=(q+1)<<p; ++h)
				my[j]=min(my[j],yr[h]+w[j][h]);
		}
	}
	for(i=1; i<=n; ++i) ans=min(ans,f[n&1][i]);
	printf("%d",ans);
	return 0;
}