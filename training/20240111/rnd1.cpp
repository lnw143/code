#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
int T=5,n=18,i;
uniform_real_distribution<double> d(0.01,9.99);
double r=0.5;
int main() {
	freopen("angrybirds.in","w",stdout);
	printf("%d\n",T);
	while(T--) {
		printf("%d %d\n",n,0);
		for(i=1; i<=n; ++i)
			// printf("%.2lf %.2lf\n",d(rnd),d(rnd));
			printf("%.2lf %.2lf\n",i*r,-i*r*i*r+i*r);
	}
	return 0;
}