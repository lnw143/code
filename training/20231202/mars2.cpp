#include<cstdio>
#include<cstring>
using namespace std;
int e[10],w[520][520],f[520][520];
int main() {
	int n,i,j,k;
	e[0]=1;
	for(i=1; i<=9; i++) e[i]=e[i-1]*2;
	scanf("%d",&n);
	for(i=0; i<e[n]; i++)
		for(j=0; j<e[n]; j++) scanf("%d",&w[i][j]);

	for(i=0; i<e[n]; i++) f[0][i]=0;

	for(i=1; i<e[n]; i++)
		for(j=0; j<e[n]; j++) {
			f[i][j]=2147483647;
			int l,r;

			for(k=n; k>=0; k--) {
				if(i/e[k]!=(i-1)/e[k]) {
					int x=j/e[k];
					x^=1;
					l=x*e[k];
					r=l+e[k]-1;
					break;
				}
			}

			for(k=l; k<=r; k++) if(f[i-1][k]+w[j][k]<f[i][j]) f[i][j]=f[i-1][k]+w[j][k];
			printf("%d %d %d\n",i+1,j+1,f[i][j]);
		}

	int ans=2147483647;
	for(i=0; i<e[n]; i++) if(f[e[n]-1][i]<ans) ans=f[e[n]-1][i];

	printf("%d",ans);
	return 0;
}
