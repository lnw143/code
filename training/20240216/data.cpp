#include<cstdio>
using namespace std;
int T=2,n=13,i,j;
int main() {
	freopen(".in","w",stdout);
	printf("%d\n",T);
	while(T--) {
		printf("%d %d\n",n,n*(n-1)/2);
		for(i=1; i<=n; ++i)
			printf("%d ",100);
		putchar('\n');
		for(i=1; i<=n; ++i)
			for(j=i+1; j<=n; ++j)
				printf("%d %d\n",i,j);
	}
	return 0;
}