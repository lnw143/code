#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(0,100),d2(0,300);
int n=50,i,j;
int main() {
	printf("%d\n",n);
	for(i=1; i<=n; ++i) {
		for(j=1; j<=n; ++j)
			printf("%d ",d(rnd));
		printf("%d\n",d2(rnd));
	}
	return 0;
}