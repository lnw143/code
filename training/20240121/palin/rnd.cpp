#include<cstdio>
#include<random>
#include<algorithm>
using namespace std;
mt19937 rnd(random_device{}());
const int N = 5e5;
int T=1,n=5e5,i,a[N * 2 + 2];
int main() {
	freopen("palin3.in","w",stdout);
	printf("%d\n",T);
	while(T--) {
		printf("%d\n",n);
		for(i=1; i<=n; ++i)
			a[i*2-1]=a[i*2]=i;
		shuffle(a+1,a+2*n+1,rnd);
		for(i=1; i<=n*2; ++i)
			printf("%d ",a[i]);
	}
	return 0;
}