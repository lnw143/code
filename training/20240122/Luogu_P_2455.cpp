#include<cstdio>
#include<algorithm>
using namespace std;
using db = double;
const int N = 50;
const db eps = 1e-12;
int n,i,j;
db a[N + 2][N + 2];
bool f;
void ad(int x,int y,db z) {
	for(int i=0; i<=n; ++i)
		a[x][i]+=a[y][i]*z;
}
bool equa(db x,db y) {
	return abs(x-y)<eps;
}
int Gauss() {
	int cnt=0;
	for(int i=1; i<=n; ++i) {
		int y=0;
		for(int j=cnt+1; j<=n; ++j)
			if(!equa(a[j][i],0)) {
				y=j;
				break;
			}
		if(!y) continue;
		++cnt;
		for(int j=0; j<=n; ++j)
			swap(a[cnt][j],a[y][j]);
		db r=a[cnt][i];
		for(int j=0; j<=n; ++j)
			a[cnt][j]/=r;
		for(int j=1; j<=n; ++j)
			if(cnt!=j&&!equa(a[j][i],0))
				ad(j,cnt,-a[j][i]);
	}
	return cnt;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		for(j=1; j<=n; ++j)
			scanf("%lf",&a[i][j]);
		scanf("%lf",&a[i][0]);
	}
	int cnt=Gauss();
	if(cnt==n) {
		for(i=1; i<=n; ++i)
			printf("x%d=%.2lf\n",i,a[i][0]);
	} else {
		for(i=cnt+1; i<=n; ++i)
			if(!equa(a[i][0],0)) {
				printf("-1");
				return 0;
			}
		printf("0");
	}
	return 0;
}