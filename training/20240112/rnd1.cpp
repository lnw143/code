#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
int n=12,m=n*n,i,j;
int main() {
	freopen("treasure.in","w",stdout);
	printf("%d %d\n",n,m);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			printf("%d %d %d\n",i,j,rnd()%500000+1);
	return 0;
}