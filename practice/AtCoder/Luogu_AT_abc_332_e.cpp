#include<cstdio>
#include<algorithm>
#include<cstring>
#define pw2(x) (1<<((x)-1))
using namespace std;
using db = double;
const int N(15), S(1 << N);
int n,m,w[N + 2];
db ave,f[S + 2][N + 2];
db sqr(db x) {
	return x*x;
}
int sum(int s) {
	int sum=0;
	for(int i=1; i<=n; ++i)
		if(s&pw2(i))
			sum+=w[i];
	return sum;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&w[i]),ave+=w[i];
	ave/=m;
	memset(f,0xff,sizeof(f));
	for(int i=0; i<(1<<n); ++i) {
		f[i][1]=sqr(sum(i)-ave);
		for(int j=2; j<=m; ++j) {
			f[i][j]=f[i][j-1]+f[0][1];
			for(int k=i; k; k=(k-1)&i)
				f[i][j]=min(f[i][j],f[i^k][j-1]+f[k][1]);
		}
	}
	printf("%.15lf",f[(1<<n)-1][m]/m);
	return 0;
}