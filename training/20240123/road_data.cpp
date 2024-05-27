#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(1,1e9);
int n=100,m=(n+1)*n/2,i,j;
int main() {
	freopen(".in","w",stdout);
	printf("%d %d\n",n,m);
	for(i=1; i<=n; ++i)
		for(j=i; j<=n; ++j)
			printf("%d %d %d\n",i,j,d(rnd));
	printf("%d %d\n",1,n);
	return 0;
}