#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e2;
int n,m,P,a[N + 2][N + 2];
int det() {
	int sgn=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j) {
			while(a[i][i]) {
				int d=a[j][i]/a[i][i];
				for(int k=i; k<=n; ++k)
					a[j][k]=(a[j][k]-1ll*a[i][k]*d%P)%P;
				swap(a[i],a[j]);
				sgn^=1;
			}
			swap(a[i],a[j]);
			sgn^=1;
		}
	int res=sgn?-1:1;
	for(int i=1; i<=n; ++i) res=1ll*res*a[i][i]%P;
	return (res+P)%P;
}
int main() {
	freopen("garakuta.in","r",stdin);
	freopen("garakuta.out","w",stdout);
	scanf("%d%d%d",&n,&m,&P);
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		++a[x][y];
		++a[x][x];
	}
	printf("%d",det());
	return 0;
}