#include<cstdio>
#include<random>
using namespace std;
random_device rd;
mt19937 rnd(rd());
uniform_int_distribution<int> d(1,2147483647);
int n=1e3,i;
int main() {
	printf("%d\n",n);
	for(i=1; i<=n; ++i)
		printf("%d\n",d(rnd));
	return 0;
}