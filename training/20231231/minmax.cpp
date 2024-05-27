#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5 + 2, M = 1e2 + 2;
int n,m=100,a[M],b[M],i;
int ans() {
	int maxn(0);
	int i=1,j=m,x=0,y=0;
#define ii (a[i]-x)
#define jj (b[j]-y)
	while(i<=m&&j>=1) {
		if(ii&&jj)
			maxn=max(maxn,i+j);
		if(ii>jj) {
			x+=jj;
			--j,y=0;
		} else if(ii==jj) {
			x=y=0;
			++i,--j;
		} else {
			y+=ii;
			++i,x=0;
		}
	}
#undef ii
#undef jj
	return maxn;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",a,b);
		++a[*a];
		++b[*b];
		printf("%d\n",ans());
	}
	return 0;
}