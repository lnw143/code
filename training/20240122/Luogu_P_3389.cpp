#include<cstdio>
#include<algorithm>
using namespace std;
using db = double;
const int N = 1e2;
int n,i,j;
db a[N + 2][N + 2];
bool f;
void ad(int x,int y,db z) {
	for(int i=0; i<=n; ++i)
		a[x][i]+=a[y][i]*z;
}
bool Gauss() {
	for(int i=1; i<=n; ++i) {
		int y=0;
		for(int j=i; j<=n; ++j)
			if(a[j][i]!=0) {
				y=j;
				break;
			}
		if(!y) return false;
		for(int j=0; j<=n; ++j)
			swap(a[i][j],a[y][j]);
		for(int j=i+1; j<=n; ++j)
			ad(j,i,-a[j][i]/a[i][i]);
	}
	for(int i=n; i>=1; --i) {
		a[i][0]/=a[i][i];
		a[i][i]=1;
		for(int j=i-1; j>=1; --j) {
			a[j][0]-=a[j][i]*a[i][0];
			a[j][i]=0;
		}
	}
	return true;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		for(j=1; j<=n; ++j)
			scanf("%lf",&a[i][j]);
		scanf("%lf",&a[i][0]);
	}
	if(Gauss())
		for(i=1; i<=n; ++i)
			printf("x%d=%.2lf\n",i,a[i][0]);
	else
		printf("No Solution");
	return 0;
}