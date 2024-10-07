#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e3;
int n,p[N + 2],pos[N + 2],c[N + 2][N + 2];
int f[N + 2][N + 2];
int main() {
	freopen("strong.in","r",stdin);
	freopen("strong.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]),p[i]=n-p[i]+1,pos[p[i]]=i;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			c[i][j]=c[i-1][j]+(p[i]<=j);
	memset(f,0x3f,sizeof(f));
	f[n+1][n+1]=0;
	p[n+1]=n+1;
	for(int i=n; i>=1; --i) {
		for(int j=1; j<=n+1; ++j)
			if(p[j]>i)
				f[i][j]=min(f[i][j],f[i+1][j]+c[j-1][i-1]+c[pos[i]-1][i-1]+2);
		int sum=0;
		for(int j=pos[i]+1; j<=n+1; ++j) {
			if(p[j]>i)
				f[i][pos[i]]=min(f[i][pos[i]],f[i+1][j]+sum);
			sum+=max(0,i-p[j]);
		}
	}
	printf("%d",*min_element(f[1]+1,f[1]+n+2));
	return 0;
}