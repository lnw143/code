#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(1,1e9);
int T=1,n=2e5,i;
int main() {
	freopen(".in","w",stdout);
	printf("%d\n",T);
	while(T--) {
		printf("%d\n",n);
		for(i=1; i<=2*n; ++i)
			printf("%d%c",d(rnd)," \n"[i%n==0]);
	}
	return 0;
}